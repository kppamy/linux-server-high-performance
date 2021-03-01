
from collections import deque

# 1670. Design Front Middle Back Queue
# 72 ms, faster than 73.74% vs c++ 32 ms
# 15.1 MB, less than 6.82%
class FrontMiddleBackQueue:
    def __init__(self):
        self.queue1 = deque()
        self.queue2 = deque()

    def pushFront(self, val: int) -> None:
        self.queue1.appendleft(val)
        if len(self.queue1) > len(self.queue2)+1 :
            self.queue2.appendleft(self.queue1.pop())

    def pushMiddle(self, val: int) -> None:
        if len(self.queue1) > len(self.queue2):
            self.queue2.appendleft(self.queue1.pop())
        self.queue1.append(val)

    def pushBack(self, val: int) -> None:
        self.queue2.append(val)
        if len(self.queue2) > len(self.queue1):
            self.queue1.append(self.queue2.popleft())

    def popFront(self) -> int:
        val = -1
        if len(self.queue1) > 0 :
            val = self.queue1.popleft()
        if len(self.queue1) < len(self.queue2):
            self.queue1.append(self.queue2.popleft())
        return val

    def popMiddle(self) -> int:
        val = -1
        if len(self.queue1) > 0:
            val = self.queue1.pop()
        if len(self.queue1) < len(self.queue2):
            self.queue1.append(self.queue2.popleft())
        return val

    def popBack(self) -> int:
        val = -1
        if len(self.queue2) > 0:
            val = self.queue2.pop()
        elif len(self.queue1) > 0:
            val =self.queue1.pop()
        if len(self.queue1) > len(self.queue2)+1:
            self.queue2.appendleft(self.queue1.pop())
        return val