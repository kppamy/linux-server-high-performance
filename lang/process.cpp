class Aclass{
private:
    static int cstaticv;
    const static int csconstv=4444;
    const int constVariableInClass=8888;
public:
    void func(){}
};

int Aclass::cstaticv=6666;
int global_varible=9999;
static int gstatic_variable=7777;

#include<thread>
int main(int argc, char const *argv[])
{
    Aclass ac;
    std::thread t(&Aclass::func,&ac);
    t.join();
    getchar();
    return 0;
}
