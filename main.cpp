#include <iostream>
#include <vector>
#include <algorithm>
#include "include/HullPoint.h"
#include "include/Utils.h"
#include <fstream>

using namespace std;



bool isTangent(HullPoint *a, HullPoint *b, HullPoint* U, int orientation)
{
    HullPoint *x = U;

    do
    {
        if ( Utils::getCrossProductZ(*a, *b, *x) * orientation > 0){
            return false;
        }

        x = x->next;
    } while ( x!= U);

    return true;

}


HullPoint* findTangent(HullPoint *a, HullPoint *b, HullPoint* U, int direction, int orientation)
{
    while(!isTangent(a,b,U,orientation))
    {
        b = orientation == 1 ? b->next : b->prev;
    }

    return b;
}


HullPoint* getMinMax(HullPoint *A, int orientation)
{
    HullPoint* x = A;
    HullPoint* z = x;

    do
    {
        if ( z->x * orientation > x->x * orientation ) {
            z = x;
        }
        x = x->next;
    } while(x!=A);
}



HullPoint* combine(HullPoint* A, HullPoint* B)
{
    //HullPoint *rightA = *max_element(A.begin( ), A.end( ), []( HullPoint *a, HullPoint *b){ return a->x < b->x;});
    //HullPoint *leftB = *min_element(B.begin( ), B.end( ), []( HullPoint *a, HullPoint *b){ return a->x < b->x;});


    HullPoint *rightA = getMinMax(A, 1);
    HullPoint *leftB = getMinMax(B, -1);


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

    return lowerA;

}



HullPoint* computeConvexHull(vector<Point*> U, int l, int r)
{
    if ( r - l + 1 == 1 )
    {
        HullPoint *a = new HullPoint(U[l]->x, U[l]->y, l+1);
        a->next = a; a->prev = a;
        return a;
    }

    if ( r - l + 1 == 2)
    {
        HullPoint *a, *b;
        a = new HullPoint(U[l]->x, U[l]->y, l+1);
        b = new HullPoint(U[r]->x, U[r]->y, r+1);

        a->next = b; a->prev = b;
        b->next = a; b->prev = a;

        return a;
    }

    int mid = (l + r) / 2;

    HullPoint* A = computeConvexHull(U,l, mid);
    HullPoint* B = computeConvexHull(U,mid+1, r);

    return combine(A,B);

}


void blq ()
{

    vector<Point*> A;
    vector<Point*> B;

    A.push_back(new Point(1.2, 5.0, 1));
    A.push_back(new Point(1.9, 7.0, 2));
    A.push_back(new Point(2.8, 1.8, 3));
    A.push_back(new Point(3.8, 3.0, 4));
    A.push_back(new Point(4.2, 9.0, 5));
    A.push_back(new Point(4.8, 6.0, 6));

    B.push_back(new Point(6.1, 4.1, 7));
    B.push_back(new Point(6.9, 7.0, 8));
    B.push_back(new Point(7.0, 1.0, 9));
    B.push_back(new Point(7.6, 8.1, 10));
    B.push_back(new Point(8.5, 7.5, 11));
    B.push_back(new Point(9.2, 2.0, 12));


    for(Point *i : B)
    {
        A.push_back(i);
    }


    HullPoint* U = computeConvexHull(A,0,A.size()-1);

    cout<<endl<<endl;

    HullPoint *x = U;

    do
    {
        cout<<x->index<<" ";
        x = x->next;
    } while ( x!= U);

}


int main()
{
    int numPoints = 10000;
    int maxCoordinates = 32000;

    int test = 1;

    if ( test == 1)
    {
        clock_t s1;
        clock_t s2;




        ofstream myFile, ymFile;
        myFile.open("/home/peter/convex/output.txt");
        ymFile.open("/home/peter/convex/input.txt");

        s1 = clock();
        vector<Point*> V = Utils::generatePoints(maxCoordinates, numPoints);
        myFile << "Time for generating : " << ((float)clock() - s1)/CLOCKS_PER_SEC<<endl;
        cout<<"Generated ... "<<endl;

        //A.begin( ), A.end( ), []( HullPoint *a, HullPoint *b){ return a->x < b->x;});

        s1 = clock();
        sort(V.begin(), V.end(), [](Point *a, Point *b){ return a->x < b->x;});
        myFile << "Time for sorting : " << ((float)clock() - s1)/CLOCKS_PER_SEC<<endl;
        cout<<"Sorted ..."<<endl;

        s1 = clock();
        HullPoint* U = computeConvexHull(V,0,V.size()-1);
        myFile << "Time for convexing : " << ((float)clock() - s1)/CLOCKS_PER_SEC<<endl;

        for(Point *i : V)
        {
            ymFile << "( " << i->x << " , " << i->y <<" ) "<<endl;

        }


        HullPoint *x = U;

        do
        {
            //cout<<x->index<<" ";
            myFile << "( " << x->x << " , " << x->y <<" ) "<<endl;
            x = x->next;
        } while ( x!= U);

        myFile.close();
        ymFile.close();

    }

    else
        blq();













    cout << "Hello world!" << endl;
    return 0;
}
