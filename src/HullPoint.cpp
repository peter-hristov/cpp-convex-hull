#include "HullPoint.h"
#include <cmath>

HullPoint::HullPoint(double _x, double _y, int _index) : x(_x), y(_y), index(_index), next(this), prev(this)
{

}

HullPoint::HullPoint(double _x, double _y, int _index, HullPoint *_next, HullPoint *_prev) : x(_x), y(_y), index(_index), next(_next), prev(_prev)
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
