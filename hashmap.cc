#include <vector>
#include <iostream>
#include <map>
using namespace std;

// 412. Fizz Buzz
vector<string> fizzBuzz(int n)
{
    vector<string> out;
    vector<string>&& dc = {"Fizz", "Buzz", "FizzBuzz"};
    int counter = 1;
    while (counter <= n)
    {
        if (counter % 15 == 0)
        {
            out.push_back(dc[2]);
        }
        else if (counter % 3 == 0)
        {
            out.push_back(dc[0]);
        }
        else if (counter % 5 == 0)
        {
            out.push_back(dc[1]);
        }
        else
        {
            out.push_back(to_string(counter));
        }
        counter++;
    }
    return out;
}

int main(int argc, char const *argv[])
{
    vector<string> fb = fizzBuzz(32);
    for (auto &&val : fb)
    {
        cout << val << ", ";
    }
    return 0;
}
