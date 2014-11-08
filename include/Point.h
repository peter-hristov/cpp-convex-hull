#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        Point(double, double, int);
        double x, y;
        int index;
        virtual ~Point();
    protected:
    private:
};

#endif // POINT_H
