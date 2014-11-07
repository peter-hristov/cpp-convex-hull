#include <iostream>
#include <vector>
#include <algorithm>
#include "include/HullPoint.h"
#include "include/Utils.h"

using namespace std;

int main()
{
    vector<HullPoint> V = Utils::generateHullPoints(100,10);



    sort(V.begin( ), V.end( ), []( const HullPoint& a, const HullPoint& b){ return a.x < b.y;});

    Utils::printVector(V);

    cout << "Hello world!" << endl;
    return 0;
}
