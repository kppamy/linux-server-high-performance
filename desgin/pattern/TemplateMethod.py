from abc import ABCMeta,abstractclassmethod
class TemplateMethod(metaclass=ABCMeta):
    def method_skeleton(self):
        self.primitive_oper1()
        self.primitive_oper2()

    @abstractclassmethod
    def primitive_oper1(self):
        print("primitive_oper1  in father")

    @abstractclassmethod
    def primitive_oper2(self):
        print("primitive_oper2  in father")


class TMChildA(TemplateMethod):
    def primitive_oper1(self):
        print("primitive_oper1  from A")

    def primitive_oper2(self):
        print("primitive_oper2  from A")


def skeleton(func1, func2):
    func1()
    func2()

if __name__ == "__main__":
    tm = TMChildA()
    tm.method_skeleton()
    skeleton(tm.primitive_oper2, tm.primitive_oper1)