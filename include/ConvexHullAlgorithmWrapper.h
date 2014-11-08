#ifndef CONVEXHULLALGORITHMWRAPPER_H
#define CONVEXHULLALGORITHMWRAPPER_H


#include <vector>
#include "Utils.h"
#include "Point.h"
#include "HullPoint.h"
#include "ConvexHullAlgorithm.h"


class ConvexHullAlgorithmWrapper
{
    public:

        ConvexHullAlgorithmWrapper(std::vector<Point*>);

        virtual ~ConvexHullAlgorithmWrapper();

        std::vector<Point*> InputPoints;
        std::vector<Point*> OutputPoints;

        std::vector<Point*> startComputing();
        std::vector<Point*> getResult(HullPoint*);

    protected:
    private:
};

#endif // CONVEXHULLALGORITHMWRAPPER_H
