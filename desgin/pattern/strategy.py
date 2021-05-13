import types


class Strategy:
    def __init__(self, func=None):
        self.name = 'stub'
        if func is not None:
            self.execute = types.MethodType(func, self)

    def execute(self):
        print(self.name)


def callcoco(self):
    print(self.name + "coco")


def callcay(self):
    print(self.name + "cay")


if __name__ == '__main__':
    s = Strategy()
    s.execute()
    cay = Strategy(callcay)
    cay.name = 'cay'
    cay.execute()
    coco = Strategy(callcoco)
    coco.name = 'coco'
    coco.execute()
