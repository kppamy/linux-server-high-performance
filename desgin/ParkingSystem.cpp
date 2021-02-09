#include "../common.h"
#include <array>
using namespace std;

// 1656. Design an Ordered Stream
// 116 ms, faster than 75.03%
// 83.7 MB, less than 72.86%
class OrderedStream
{
public:
    OrderedStream(int n) : size(n)
    {
        // ordered.resize(n + 1, "A"); change from "AAAAA" to "A" will be slower, aligned?
        ordered.resize(n + 1, "AAAAA");
    }

    vector<string> insert(int id, string value)
    {
        ordered[id] = value;
        vector<string> out;
        while (ptr < size) //change size -1 to size, improve from 72.86% to 85.78%
        {
            string val = ordered[ptr + 1];
            // if (val != "AAAAA")
            if (val[0] != 'A') // compare one byte instead of 5 bytes, improved from 85.78% faster than 90.12%
            {
                ptr++;
                out.push_back(val);
            }
            else
                break;
        }
        return move(out);
    }

private:
    vector<string> ordered;
    int size{0};
    int ptr = 0;
};

// 1603. Design Parking System
// 48 ms, faster than 96.98%
// 33.1 MB, less than 65.81%
class ParkingSystem
{
public:
    ParkingSystem(int big, int medium, int small)
    {
        slots[1] = big;
        slots[2] = medium;
        slots[3] = small;
    }

    bool addCar(int carType)
    {
        if (slots[carType] > 0)
        {
            slots[carType]--;
            return true;
        }
        else
            return false;
    }

private:
    array<int, 4> slots;
    // array<int, 3> slots; // will be slower as substraction included
};
