#include <atomic>
#include <thread>

class spinlock_t
{
	std::atomic_flag lock_flag;

public:
	spinlock_t() { lock_flag.clear(); }
	bool try_lock() { return !lock_flag.test_and_set(std::memory_order_acquire); }
	void lock()
	{
		for (size_t i = 0; !try_lock(); ++i)
			if (i % 100 == 0)
				std::this_thread::yield();
	}
	void unlock() { lock_flag.clear(std::memory_order_release); }
};

#include <cassert>
class recursive_spinlock_t
{
	std::atomic_flag lock_flag;
	int64_t recursive_counter;

	typedef std::thread::id thread_id_t;
	std::atomic<std::thread::id> owner_thread_id;
	std::thread::id get_fast_this_thread_id() { return std::this_thread::get_id(); }

public:
	recursive_spinlock_t() : recursive_counter(0), owner_thread_id(thread_id_t()) { lock_flag.clear(); }

	bool try_lock()
	{
		if (!lock_flag.test_and_set(std::memory_order_acquire))
		{
			owner_thread_id.store(get_fast_this_thread_id(), std::memory_order_release);
		}
		else
		{
			if (owner_thread_id.load(std::memory_order_acquire) != get_fast_this_thread_id())
				return false;
		}
		++recursive_counter;
		return true;
	}

	void lock()
	{
		for (volatile size_t i = 0; !try_lock(); ++i)
			if (i % 100000 == 0)
				std::this_thread::yield();
	}

	void unlock()
	{
		assert(owner_thread_id.load(std::memory_order_acquire) == get_fast_this_thread_id());
		assert(recursive_counter > 0);

		if (--recursive_counter == 0)
		{
			owner_thread_id.store(thread_id_t(), std::memory_order_release);
			lock_flag.clear(std::memory_order_release);
		}
	}
};

class SpinLockTAS
{
private:
	std::atomic_flag flag;

private:
	SpinLockTAS(const SpinLockTAS&)=delete;
	SpinLockTAS& operator=(const SpinLockTAS&)=delete;
public:
	SpinLockTAS(/* args */) { flag.clear(); };
	~SpinLockTAS() { unlock(); };
	void lock()
	{
		int i = 0;
		while (flag.test_and_set(std::memory_order_acquire))
		{
			i++;
			if (i % 100 == 0)
				std::this_thread::yield();
		};
	}
	bool trylock() { return !flag.test_and_set(std::memory_order_acquire); };
	void unlock()
	{
		flag.clear(std::memory_order_release);
	}
};

// why doesn't work?
class SpinLockCAS
{
private:
	std::atomic_bool locked{false};

public:
	SpinLockCAS(/* args */){};
	~SpinLockCAS() { unlock(); };
	void lock()
	{
		bool expected{false};
		for (int i = 0; locked.compare_exchange_strong(expected, true, std::memory_order_acquire); i++)
		{
			if (i % 100 == 0)
				std::this_thread::yield();
		}
	};
	void unlock()
	{
		locked.store(false, std::memory_order_release);
	}
};

class ReadWriteLock
{
private:
	std::atomic<int> readers{0};
	std::atomic<int> writer{0};
	std::condition_variable cv;
	std::mutex mtx;	
private:
	ReadWriteLock(const ReadWriteLock&)=delete;
	ReadWriteLock& operator=(const ReadWriteLock&)=delete;
public:
	ReadWriteLock(){};
	~ReadWriteLock(){};
	void lockRead()
	{
		std::unique_lock<std::mutex> lck(mtx);
		cv.wait(lck, [&]() {
			return writer.load(std::memory_order_acquire) == 0;
		});
		readers.fetch_add(1, std::memory_order_release);
	}
	void unlockRead()
	{
		readers.fetch_sub(1, std::memory_order_release);
		cv.notify_all();
	}
	void lockWrite()
	{
		std::unique_lock<std::mutex> lck(mtx);
		cv.wait(lck, [&]() {
			return readers.load(std::memory_order_acquire) == 0 && writer.load(std::memory_order_acquire) == 0;
		});
		writer.fetch_add(1, std::memory_order_release);
	}
	void unlockWrite()
	{
		writer.fetch_sub(1, std::memory_order_release);
		cv.notify_all();
	}
};

class Log
{
private:
	static SpinLockTAS lck;
public:
	Log(){};
	~Log(){};
	static void print()
	{
		std::cout << std::endl;
	}
	template <typename T, typename... Args>
	static void print(const T &msg, Args... args)
	{
		std::cout << msg << " ";
		print(args...);
	}
	template <typename T, typename... Args>
	static void info(const T &msg, Args... args)
	{
		std::lock_guard<SpinLockTAS> guard(lck);
		print(msg, args...);
	}
};
SpinLockTAS Log::lck;
