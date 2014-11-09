#ifndef HULLPOINT_H
#define HULLPOINT_H

#include "Point.h"

class HullPoint
{
    public:
        Point point;

        HullPoint *next;
        HullPoint *prev;

        HullPoint(Point);

        static double Distance(HullPoint, HullPoint);

        virtual ~HullPoint();
    protected:
    private:
};

#endif // HULLPOINT_H
