#ifndef CONVEXHULLALGORITHM_H
#define CONVEXHULLALGORITHM_H

#include <vector>
#include "Utils.h"
#include "Point.h"
#include "HullPoint.h"

template<class HullPoint>
class ConvexHullAlgorithm
{

    public:

        static double getCrossProductZ(HullPoint, HullPoint, HullPoint);

        static HullPoint* combine(HullPoint*, HullPoint*);

        static HullPoint* computeConvexHull(std::vector<Point*>, int, int);

        static HullPoint* getMinMax(HullPoint*, int );

        static bool isTangent(HullPoint*, HullPoint*, HullPoint*, int );

        static HullPoint* findTangent(HullPoint*, HullPoint*, HullPoint*, int, int);
};

#endif // CONVEXHULLALGORITHM_H
