#ifndef CONVEXHULLALGORITHM_H
#define CONVEXHULLALGORITHM_H

#include <vector>
#include "Utils.h"
#include "Point.h"
#include "HullPoint.h"
#include <thread>
#include <atomic>


class ConvexHullAlgorithm
{

public:
    static std::atomic<int> maxThreads;

    std::vector<Point*> InputPoints;
    std::vector<Point*> OutputPoints;
    HullPoint *omega;
    int l, r;

    ConvexHullAlgorithm(std::vector<Point*>, int, int);

    std::vector<Point*> start();

private:

    double getCrossProductZ(HullPoint , HullPoint , HullPoint );

    /**
     * Gets the minimum/maximum out of all elements in the HullPoints linked list
     * @param  A           Doubly linked HullPoint list
     * @param  orientation 1 maximum / -1 minimum
     * @return             Pointer the the min/max element in A
     */
    HullPoint* getMinMax(HullPoint *A, int orientation);

    /**
     * Checks to see if (ab) is a tangent to the ConvexHull described by the linked list U
     * @param  a           Point in the other ConvexHull
     * @param  b           Point in this
     * @param  U           This Convex Hull
     * @param  orientation Clockwise(1) / Counterclockwise(-1) for the cross product of vectors (ab)x(ac)
     * @return             Whether (ab) is a tangent to U
     */
    bool isTangent(HullPoint *a, HullPoint *b, HullPoint* U, int orientation);

    /**
     * Goes through all points in the Convex Hull U untill a tanget (ab) is found.
     * @param  a           Point in the other Convex Hull
     * @param  b           Start point for the walk on all points in U
     * @param  U           This Convex Hull
     * @param  direction   Clockwise(1) / Counterclockwise(-1) for the walk.
     * @param  orientation Clockwise(1) / Counterclockwise(-1) for computing the cross product in isTangent
     * @return             A point b for which (ab) is a tanget to U
     */
    HullPoint* findTangent(HullPoint *a, HullPoint *b, HullPoint* U, int direction, int orientation);


    /**
     * Combines two non-intersecting Convex Hulls into one
     * @param  A First Convex Hull
     * @param  B Second Convex Hull
     * @return   Combinex Convex Hull
     */
    HullPoint* combine(HullPoint* A, HullPoint* B);

    /**
     * Divide and conquire method the finding the Convex Hull of all Points in U.
     * Base Case 1 : The Convex Hull of 1 point is that point.
     * Base Case 2 : The Convex Hull of 2 points is the 2 points.
     * @param  l Left index of current subset of points.
     * @param  r Right index of current subset of points.
     * @return A HullPoints* that's any element in the Convex Hull Doubly Linked List.
     */
    HullPoint* computeConvexHull(int l, int r);
};

#endif // CONVEXHULLALGORITHM_H
