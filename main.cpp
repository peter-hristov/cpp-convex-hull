#include <iostream>
#include <vector>
#include <algorithm>
#include "include/HullPoint.h"
#include "include/Utils.h"
#include "include/ConvexHullAlgorithmWrapper.h"
#include "include/ConvexHullAlgorithm.h"
#include <fstream>

using namespace std;


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

    ConvexHullAlgorithmWrapper c(A);

    HullPoint* U;//c.computeConvexHull(A,0,A.size()-1);

    cout<<endl<<endl;

    HullPoint *x = U;

    do
    {
        cout<<x->index<<" ";
        x = x->next;
    } while ( x!= U);

}

class test
{

};


int main()
{
    int numPoints = 10;
    int maxCoordinates = 32000;

    int test = 1;

    if ( test == 1)
    {
        clock_t s1;

        ofstream myFile, ymFile;
        myFile.open("/home/peter/convex/output.txt");
        ymFile.open("/home/peter/convex/input.txt");

        s1 = clock();
        vector<Point*> V = Utils::generatePoints(maxCoordinates, numPoints);
        cout << "Time for generating : " << ((float)clock() - s1)/CLOCKS_PER_SEC<<endl;
        //cout<<"Generated ... "<<endl;

        //A.begin( ), A.end( ), []( HullPoint *a, HullPoint *b){ return a->x < b->x;});

        s1 = clock();
        sort(V.begin(), V.end(), [](Point *a, Point *b){ return a->x < b->x;});
        cout << "Time for sorting : " << ((float)clock() - s1)/CLOCKS_PER_SEC<<endl;
        //cout<<"Sorted ..."<<endl;

        s1 = clock();
        ConvexHullAlgorithmWrapper c(V);
        //HullPoint* U = c.computeConvexHull(V,0,V.size()-1);
        vector<Point*> U = c.startComputing();
        cout<< "Time for convexing : " << ((float)clock() - s1)/CLOCKS_PER_SEC<<endl;

        for(Point *i : V)
        {
            ymFile << "( " << i->x << " , " << i->y <<" ) "<<endl;

        }


        for (Point *i : U)
        {
            myFile << "( " << i->x << " , " << i->y <<" ) "<<endl;
        }

        myFile.close();
        ymFile.close();

    }

    if ( test == 2 )

        blq();

    else
    {

    }



    cout << "Hello world!" << endl;
    return 0;
}
