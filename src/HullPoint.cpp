#include "HullPoint.h"
#include <cmath>

HullPoint::HullPoint(Point _point) : point(_point), next(this), prev(this)
{

}

HullPoint::~HullPoint()
{
    //delete this->next;
    //delete this->prev;
}
