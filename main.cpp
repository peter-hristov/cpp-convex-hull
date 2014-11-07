#include <iostream>
#include <vector>
#include <algorithm>
#include "include/HullPoint.h"
#include "include/Utils.h"

using namespace std;




vector<HullPoint> combine2(vector<HullPoint> A, vector<HullPoint> B)
{
    return A;
}


bool isTangent(HullPoint *a, HullPoint *b, vector<HullPoint> *U, int orientation)
{
    for(HullPoint current : *U) {
        if ( Utils::getCrossProductZ(*a, *b, current) * orientation > 0){
            return false;
        }
    }
    return true;
}


HullPoint* findTangent(HullPoint *a, HullPoint *b, vector<HullPoint> *U, int direction, int orientation)
{
    while(!isTangent(a,b,U,orientation))
    {
        b = orientation == 1 ? b->next : b->prev;
    }

    return b;
}



vector<HullPoint>* combine(vector<HullPoint> *A, vector<HullPoint> *B)
{
    HullPoint *rightA = &*max_element(A->begin( ), A->end( ), []( const HullPoint& a, const HullPoint& b){ return a.x < b.x;});
    HullPoint *leftB = &*min_element(B->begin( ), B->end( ), []( const HullPoint& a, const HullPoint& b){ return a.x < b.x;});

    HullPoint *a = rightA;
    HullPoint *b = leftB;


    while(true)
    {
        // Clockwise, Case 1
        b = findTangent(a, b, B, 1, 1);

        // Case 4
        if (isTangent(b, a, A, -1)) break;

        // Counterclockwise, Case 4
        a = findTangent(b, a, A, -1, -1);

        // Case 1
        if (isTangent(a, b, B, 1)) break;
    }

    HullPoint *upperA = a;
    HullPoint *upperB = b;

    a = rightA;
    b = leftB;

    while (true)
    {
        // Counterclockwise, Case 2
        b = findTangent(a, b, B, -1, -1);

        // Case 3
        if (isTangent(b, a, A, 1)) break;

        // Clockwise, Case 3
        a = findTangent(b, a, A, 1, 1);

        // Case 2
        if (isTangent(a, b, B, -1)) break;
    }

    HullPoint *lowerA = a;
    HullPoint *lowerB = b;

    cout << "Upper tangent is : " << upperA->index <<" , " <<upperB->index<<endl;
    cout << "Upper tangent is : " << lowerA->index <<" , " <<lowerB->index<<endl;


    upperA->next = upperB; upperB->prev = upperA;
    lowerA->prev = lowerB; lowerB->next = lowerA;

    HullPoint *x = lowerA;
    vector<HullPoint*> *z = new vector<HullPoint*>();

    cout<<endl<<"The round is : " << endl;
    do
    {
        z->push_back(x);
        cout<<x->index<<" "<<x<<endl;
        x = x->next;
    }while(x!=lowerA);


    cout<<endl<<endl;

    for(int i=0; i<8 ;i++)
    {
        cout<<z->at(i)->index << " "<<(z->at(i)) << endl;

    }
    //cout<< a->index <<" " <<b->index<<endl;


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

    vector<HullPoint> A = computeConvexHull(U,l, mid);
    vector<HullPoint> B = computeConvexHull(U,mid+1, r);

    return combine2(A,B);
}


void blq ()
{
    vector<HullPoint> *A = new vector<HullPoint>();
    vector<HullPoint> *B = new vector<HullPoint>();

    A->push_back(HullPoint(1.2, 5.0, 1));
    A->push_back(HullPoint(1.9, 7.0, 2));
    A->push_back(HullPoint(2.8, 1.8, 3));
    A->push_back(HullPoint(3.8, 3.0, 4));
    A->push_back(HullPoint(4.2, 9.0, 5));
    A->push_back(HullPoint(4.8, 6.0, 6));

    A->at(0).next = &(A->at(1));
    A->at(0).prev = &(A->at(2));

    A->at(1).next = &(A->at(4));
    A->at(1).prev = &(A->at(0));

    A->at(2).next = &(A->at(0));
    A->at(2).prev = &(A->at(3));

    A->at(3).next = &(A->at(2));
    A->at(3).prev = &(A->at(5));

    A->at(4).next = &(A->at(5));
    A->at(4).prev = &(A->at(1));

    A->at(5).next = &(A->at(3));
    A->at(5).prev = &(A->at(4));

    B->push_back(HullPoint(6.1, 4.1, 7));
    B->push_back(HullPoint(6.9, 7.0, 8));
    B->push_back(HullPoint(7.0, 1.0, 9));
    B->push_back(HullPoint(7.6, 8.1, 10));
    B->push_back(HullPoint(8.5, 7.5, 11));
    B->push_back(HullPoint(9.2, 2.0, 12));

    B->at(0).next = &(B->at(1));
    B->at(0).prev = &(B->at(2));

    B->at(1).next = &(B->at(3));
    B->at(1).prev = &(B->at(0));

    B->at(2).next = &(B->at(0));
    B->at(2).prev = &(B->at(5));

    B->at(3).next = &(B->at(4));
    B->at(3).prev = &(B->at(1));

    B->at(4).next = &(B->at(5));
    B->at(4).prev = &(B->at(3));

    B->at(5).next = &(B->at(2));
    B->at(5).prev = &(B->at(4));


    vector<HullPoint> *U = combine(A,B);

}


int main()
{
    int numPoints = 10000;
    int maxCoordinates = 1000;

    vector<HullPoint> V = Utils::generateHullPoints(maxCoordinates, numPoints);


    //Utils::printVector(V);
    cout<<endl;
    //sort(V.begin( ), V.end( ), []( const HullPoint& a, const HullPoint& b){ return a.x < b.x;});

   // Utils::printVector(V);
    //computeConvexHull(V,0,numPoints-1);

    blq();

    cout << "Hello world!" << endl;
    return 0;
}
