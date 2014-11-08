#ifndef CONVEXHULLALGORITHM_H
#define CONVEXHULLALGORITHM_H

#include <vector>
#include "Utils.h"
#include "Point.h"
#include "HullPoint.h"


namespace ConvexHullAlgorithm
{
    double getCrossProductZ(HullPoint, HullPoint, HullPoint);

    HullPoint* combine(HullPoint*, HullPoint*);

    HullPoint* computeConvexHull(std::vector<Point*>, int, int);

    HullPoint* getMinMax(HullPoint*, int );

    bool isTangent(HullPoint*, HullPoint*, HullPoint*, int );

    HullPoint* findTangent(HullPoint*, HullPoint*, HullPoint*, int, int);
};

#endif // CONVEXHULLALGORITHM_H
