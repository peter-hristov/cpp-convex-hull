#include <iostream>
#include <vector>
#include <algorithm>
#include "include/HullPoint.h"
#include "include/Utils.h"

using namespace std;




vector<HullPoint> combine(vector<HullPoint> A, vector<HullPoint> B)
{
    return A;
}

vector<HullPoint> computeConvexHull(vector<HullPoint> U, int l, int r)
{


    if ( r - l + 1 == 1 )
    {
        vector<HullPoint> C;
        C.push_back(U[l]);
        C[0].next = &C[0];
        C[0].prev = &C[0];
        return C;
    }

    if ( r - l + 1 == 2)
    {
        vector<HullPoint> C;
        C.push_back(U[l]); C.push_back(U[r]);

        C[0].next = &C[1]; C[0].prev = &C[1];
        C[1].next = &C[0]; C[1].prev = &C[0];

        return C;
    }

    int mid = (l + r) / 2;

    vector<HullPoint> A = computeConvexHull(A,l, mid);
    vector<HullPoint> B = computeConvexHull(B,mid+1, r);

    return combine(A,B);
}



int main()
{
    int numPoints = 10;
    int maxCoordinates = 100;

    vector<HullPoint> V = Utils::generateHullPoints(maxCoordinates, numPoints);


    Utils::printVector(V);
    cout<<endl;
    sort(V.begin( ), V.end( ), []( const HullPoint& a, const HullPoint& b){ return a.x < b.x;});

    Utils::printVector(V);

    computeConvexHull(V,0,numPoints-1);

    cout << "Hello world!" << endl;
    return 0;
}
