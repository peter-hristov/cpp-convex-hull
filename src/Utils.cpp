#include "Utils.h"

std::vector<HullPoint*> Utils::generateHullPoints(int max, int n)
{
    std::vector<HullPoint*> v;

    srand(time(0));
    while (n > 0)
    {
        double x = static_cast<double>((rand() / (RAND_MAX * 1.0)) * max);
        double y = static_cast<double>((rand() / (RAND_MAX * 1.0)) * max);

        v.push_back(new HullPoint(x, y, n));

        n--;
    }
    return v;
}

std::vector<Point*> Utils::generatePoints(int max, int n)
{
    std::vector<Point*> v;

    srand(time(0));
    while (n > 0)
    {
        double x = static_cast<double>((rand() / (RAND_MAX * 1.0)) * max);
        double y = static_cast<double>((rand() / (RAND_MAX * 1.0)) * max);

        v.push_back(new Point(x, y, n));

        n--;
    }
    return v;
}

void Utils::printVector(std::vector<HullPoint> V)
{
    for ( std::vector<HullPoint>::iterator i=V.begin() ; i!=V.end() ; i++)
    {
        HullPoint current = *i;

        std::cout << "(" << std::setw(8) << current.x << " , " << std::setw(8) << current.y << " , " << std::setw(3) << current.index << ")\n";
    }

}


 double Utils::getCrossProductZ(HullPoint a, HullPoint b, HullPoint c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
