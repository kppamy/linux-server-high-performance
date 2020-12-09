from abc import ABCMeta, abstractclassmethod

class Observer:
    @abstractclassmethod
    def update(self, subject):
        pass


class ObserverA(Observer):
    def update(self, subject):
        print("A noticed "+str(subject.state))


class ObserverB(Observer):
    def update(self, subject):
        print("B noticed "+str(subject.state))


class Subject:
    def __init__(self):
        self.observers = []

    def subsrible(self, obs):
        self.observers = self.observers+[obs]

    def push(self):
        for obs in self.observers:
            obs.update(self)


class ConcreteSubject(Subject):
    def __init__(self, state=0):
        self.__state = state
        super().__init__()

    @property
    def state(self):
        print("call property function state")
        return self.__state

    @state.setter
    def state(self, state):
        if state != self.__state:
            self.__state = state
            self.push()
        else:
            print("sate not changed")


if __name__ == "__main__":
    s = ConcreteSubject()
    s.subsrible(ObserverA())
    s.subsrible(ObserverB())
    s.state = 0
    s.state = 1
