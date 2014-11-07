#include "HullPoint.h"
#include <cmath>

HullPoint::HullPoint(double _x, double _y, int _index) : x(_x), y(_y), index(_index), next(this), prev(this)
{

}

double HullPoint::Distance(HullPoint a, HullPoint b)
{
    return sqrt( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) );
}

HullPoint::~HullPoint()
{
    //delete this->next;
    //delete this->prev;
}
