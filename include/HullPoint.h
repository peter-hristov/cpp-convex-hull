#ifndef HULLPOINT_H
#define HULLPOINT_H


class HullPoint
{
    public:

        double x, y;
        int index;

        HullPoint *next;
        HullPoint *prev;

        HullPoint(double, double, int);
        HullPoint(double, double, int, HullPoint*, HullPoint*);

        static double Distance(HullPoint, HullPoint);

        virtual ~HullPoint();
    protected:
    private:
};

#endif // HULLPOINT_H
