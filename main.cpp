#include <iostream>
#include <vector>
#include <algorithm>
#include "include/HullPoint.h"
#include "include/Utils.h"
#include "include/ConvexHullAlgorithm.h"
#include <fstream>
#include <thread>

using namespace std;


int main()
{
    int numPoints = 1000;
    int maxCoordinates = 32000;
    ConvexHullAlgorithm::maxThreads = std::thread::hardware_concurrency();

    clock_t timer;

    bool writeToFile = false;
    ofstream myFile, ymFile;
    std::string outputFile = "/home/peter/convex/output.txt";
    std::string inputFile = "/home/peter/convex/input.txt";

    if ( writeToFile ) {
        myFile.open(outputFile);
        ymFile.open(inputFile);
    }

    // Step 1 : Generating random points.
    timer = clock();

    vector<Point*> V = Utils::generatePoints(maxCoordinates, numPoints);

    cout << "Time for generating : " << ((float)clock() - timer)/CLOCKS_PER_SEC<<endl;
    if ( writeToFile ) myFile << "Time for generating : " << ((float)clock() - timer)/CLOCKS_PER_SEC<<endl;



    // Step 2 : sorting by x coordinate
    timer = clock();

    sort(V.begin(), V.end(), [](Point *a, Point *b){ return a->x < b->x;});

    cout << "Time for sorting : " << ((float)clock() - timer)/CLOCKS_PER_SEC<<endl;
    if ( writeToFile ) myFile << "Time for sorting : " << ((float)clock() - timer)/CLOCKS_PER_SEC<<endl;


    // Step 3 : run the Convex Hull Algorithm
    timer = clock();
    ConvexHullAlgorithm charlie(V,0,V.size()-1);
    thread t(&ConvexHullAlgorithm::Start, &charlie);
    t.join();

    cout<< "Time for convexing : " << ((float)clock() - timer)/CLOCKS_PER_SEC<<endl;
    if ( writeToFile ) myFile<< "Time for convexing : " << ((float)clock() - timer)/CLOCKS_PER_SEC<<endl;

    if ( charlie.sanityCheck())
        cout<<"Everthing is calculated perfectly!";


    for(Point *i : V)
    {
        ymFile << "( " << i->x << " , " << i->y <<" ) "<<endl;

    }

    std::vector<Point*> U = charlie.OutputPoints;
    for (Point *i : U)
    {
        myFile << "( " << i->x << " , " << i->y <<" ) "<<endl;
    }

    myFile.close();
    ymFile.close();

    return 0;
}
