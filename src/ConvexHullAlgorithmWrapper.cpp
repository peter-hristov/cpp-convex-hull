#include "ConvexHullAlgorithmWrapper.h"

ConvexHullAlgorithmWrapper::ConvexHullAlgorithmWrapper(std::vector<Point*> a)
{
    this->InputPoints = a;
}

ConvexHullAlgorithmWrapper::~ConvexHullAlgorithmWrapper()
{
    //dtor
}


std::vector<Point*> ConvexHullAlgorithmWrapper::getResult(HullPoint* x)
{
    HullPoint *z = x;

    std::vector<Point*> temp;

    do
    {
        temp.push_back(this->InputPoints[z->index]);
        z = z->next;
    } while ( z!=x );

    return temp;
}

std::vector<Point*> ConvexHullAlgorithmWrapper::startComputing()
{
    HullPoint *x = ConvexHullAlgorithm::computeConvexHull(this->InputPoints, 0, this->InputPoints.size()-1);


    this->OutputPoints = getResult(x);

    return this->OutputPoints;
}

