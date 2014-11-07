#include "Utils.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>

std::vector<HullPoint> Utils::generateHullPoints(int max, int n)
{
    std::vector<HullPoint> v;

    srand(time(0));
    while (n > 0)
    {
        float x = static_cast<double>((rand() / (RAND_MAX * 1.0)) * max);
        float y = static_cast<double>((rand() / (RAND_MAX * 1.0)) * max);

        v.push_back(HullPoint(x, y, n));

        n--;
    }
    return v;
}

void Utils::printVector(std::vector<HullPoint> V)
{
    for ( std::vector<HullPoint>::iterator i=V.begin() ; i!=V.end() ; i++)
    {
        HullPoint current = *i;

        std::cout << "(" << std::setw(8) << current.x << " , " << std::setw(8) << current.y << " , " << std::setw(3) << current.index << ")\n";
    }

}

