#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include "HullPoint.h"

class Utils
{
public:
    static std::vector<HullPoint> generateHullPoints(int, int);
    static void printVector(std::vector<HullPoint>);
};

#endif // UTILS_H
