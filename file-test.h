#include <unistd.h>
#include <pthread/pthread.h>
class FileTest{
  public:
    inline
    FileTest(){};
    ~FileTest(){};
    static void testMmap();
    static void testMmapFamily();
    static void testSocket(int argc, const char* argv[]);
    static void testDup(int argc, const char* argv[]);
    static void testSyncC10K(int argc, const char* argv[]);
    static void testAsyncC10K(int argc, const char* argv[]);
    static void testSelect(int argc, const char* argv[]);
    static void testPipe();
    static void testSockPair();
    static void testSem();
    static void testProducerConsumer();
    void testThread();

  private:
    static struct sockaddr_in transSockAddr(const char* ip, const int port);
    static int getListenFd(struct sockaddr_in address, int num);
    static int getConnectFd(struct sockaddr_in *address,int sock);
    static void runProducer(const int semid, int shmid, const int bufsize);
    static void runConsumer(const int semid, int shmid);
    static int  PV(int semid, int idx, int op);
  private:

};