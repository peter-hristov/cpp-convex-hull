#ifndef UTILS_H
#define UTILS_H

#include <vector>

#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>

#include "HullPoint.h"
#include "Point.h"

class Utils
{
public:

    static std::vector<Point*> generatePoints(int, int);
    static double getCrossProductZ(HullPoint, HullPoint, HullPoint);
};

#endif // UTILS_H
