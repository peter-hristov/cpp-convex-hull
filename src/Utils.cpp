#include "Utils.h"

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
