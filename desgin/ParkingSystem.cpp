#include "../common.h"
#include <array>
using namespace std;
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
