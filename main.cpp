#include <iostream>
#include <vector>
#include <algorithm>
#include "include/HullPoint.h"
#include "include/Utils.h"
#include <fstream>

using namespace std;

vector<HullPoint> combine2(vector<HullPoint> A, vector<HullPoint> B)
{
    return A;
}

bool isTangent(HullPoint *a, HullPoint *b, vector<HullPoint*> U, int orientation)
{
    for(HullPoint *current : U) {
        if ( Utils::getCrossProductZ(*a, *b, *current) * orientation > 0){
            return false;
        }
    }
    return true;
}


HullPoint* findTangent(HullPoint *a, HullPoint *b, vector<HullPoint*> U, int direction, int orientation)
{
    while(!isTangent(a,b,U,orientation))
    {
        b = orientation == 1 ? b->next : b->prev;
    }

    return b;
}



vector<HullPoint*> combine(vector<HullPoint*> A, vector<HullPoint*> B)
{
    HullPoint *rightA = *max_element(A.begin( ), A.end( ), []( HullPoint *a, HullPoint *b){ return a->x < b->x;});
    HullPoint *leftB = *min_element(B.begin( ), B.end( ), []( HullPoint *a, HullPoint *b){ return a->x < b->x;});

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

    //cout << "Upper tangent is : " << upperA->index <<" , " <<upperB->index<<endl;
    //cout << "Lower tangent is : " << lowerA->index <<" , " <<lowerB->index<<endl;


    upperA->next = upperB; upperB->prev = upperA;
    lowerA->prev = lowerB; lowerB->next = lowerA;

    HullPoint *x = lowerA;
    vector<HullPoint*> z;

    //cout<<endl<<"The round is : " << endl;
    do
    {
        z.push_back(x);
        //cout<<x->index<<" "<<x<<endl;
        x = x->next;
    }while(x!=lowerA);

    return z;
}



vector<HullPoint*> computeConvexHull(vector<HullPoint*> U, int l, int r)
{
    if ( r - l + 1 == 1 )
    {
        vector<HullPoint*> C;
        C.push_back(U[l]);
        C[0]->next = C[0];
        C[0]->prev = C[0];
        return C;
    }

    if ( r - l + 1 == 2)
    {
        vector<HullPoint*> C;
        C.push_back(U[l]); C.push_back(U[r]);

        C[0]->next = C[1]; C[0]->prev = C[1];
        C[1]->next = C[0]; C[1]->prev = C[0];

        return C;
    }

    int mid = (l + r) / 2;

    vector<HullPoint*> A = computeConvexHull(U,l, mid);
    vector<HullPoint*> B = computeConvexHull(U,mid+1, r);

    return combine(A,B);

}


void blq ()
{

    vector<HullPoint*> A;
    vector<HullPoint*> B;

    A.push_back(new HullPoint(1.2, 5.0, 1));
    A.push_back(new HullPoint(1.9, 7.0, 2));
    A.push_back(new HullPoint(2.8, 1.8, 3));
    A.push_back(new HullPoint(3.8, 3.0, 4));
    A.push_back(new HullPoint(4.2, 9.0, 5));
    A.push_back(new HullPoint(4.8, 6.0, 6));

    A[0]->next = A[1];
    A[0]->prev = A[2];

    A[1]->next = A[4];
    A[1]->prev = A[0];

    A[2]->next = A[0];
    A[2]->prev = A[3];

    A[3]->next = A[2];
    A[3]->prev = A[5];

    A[4]->next = A[5];
    A[4]->prev = A[1];

    A[5]->next = A[3];
    A[5]->prev = A[4];

    B.push_back(new HullPoint(6.1, 4.1, 7));
    B.push_back(new HullPoint(6.9, 7.0, 8));
    B.push_back(new HullPoint(7.0, 1.0, 9));
    B.push_back(new HullPoint(7.6, 8.1, 10));
    B.push_back(new HullPoint(8.5, 7.5, 11));
    B.push_back(new HullPoint(9.2, 2.0, 12));

    B[0]->next = B[1];

    B[0]->prev = B[2];

    B[1]->next = B[3];
    B[1]->prev = B[0];

    B[2]->next = B[0];
    B[2]->prev = B[5];

    B[3]->next = B[4];
    B[3]->prev = B[1];

    B[4]->next = B[5];
    B[4]->prev = B[3];

    B[5]->next = B[2];
    B[5]->prev = B[4];


    for(HullPoint *i : B)
    {
        A.push_back(i);
    }

    //vector<HullPoint*> *U = combine(A,B);
    //vector<HullPoint*> Z = combine(A,B);
    vector<HullPoint*> U = computeConvexHull(A,0,A.size()-1);

    cout<<endl<<endl;
    for(HullPoint *i : U)
    {

        cout<<i->index<< " ";
    }

}


int main()
{
    int numPoints = 1000;
    int maxCoordinates = 32000;

    int test = 1;

    if ( test == 1)
    {
        ofstream myFile, ymFile;
        myFile.open("/home/peter/convex/output.txt");
        ymFile.open("/home/peter/convex/input.txt");

        vector<HullPoint*> V = Utils::generateHullPoints(maxCoordinates, numPoints);

        //A.begin( ), A.end( ), []( HullPoint *a, HullPoint *b){ return a->x < b->x;});
        sort(V.begin(), V.end(), [](HullPoint *a, HullPoint *b){ return a->x < b->x;});

        vector<HullPoint*> U = computeConvexHull(V,0,V.size()-1);

        for(HullPoint *i : V)
        {
            ymFile << "( " << i->x << " , " << i->y <<" ) "<<endl;

        }

        for( HullPoint *i : U )
        {
            myFile << "( " << i->x << " , " << i->y <<" ) "<<endl;
        }

        myFile.close();
        ymFile.close();

    }

    else
        blq();













    cout << "Hello world!" << endl;
    return 0;
}
