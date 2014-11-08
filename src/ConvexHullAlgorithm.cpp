#include "ConvexHullAlgorithm.h"

template<class HullPoint>
double ConvexHullAlgorithm<HullPoint>::getCrossProductZ(HullPoint a, HullPoint b, HullPoint c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

/**
 * Gets the minimum/maximum out of all elements in the HullPoints linked list
 * @param  A           Doubly linked HullPoint list
 * @param  orientation 1 maximum / -1 minimum
 * @return             Pointer the the min/max element in A
 */
template<class HullPoint>
HullPoint* ConvexHullAlgorithm<HullPoint>::getMinMax(HullPoint *A, int orientation)
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

/**
 * Checks to see if (ab) is a tangent to the ConvexHull described by the linked list U
 * @param  a           Point in the other ConvexHull
 * @param  b           Point in this
 * @param  U           This Convex Hull
 * @param  orientation Clockwise(1) / Counterclockwise(-1) for the cross product of vectors (ab)x(ac)
 * @return             Whether (ab) is a tangent to U
 */
template<class HullPoint>
bool ConvexHullAlgorithm<HullPoint>::isTangent(HullPoint *a, HullPoint *b, HullPoint* U, int orientation)
{
    HullPoint *x = U;
    do
    {
        if ( getCrossProductZ(*a, *b, *x) * orientation > 0){
            return false;
        }

        x = x->next;
    } while ( x!= U);

    return true;
}

/**
 * Goes through all points in the Convex Hull U untill a tanget (ab) is found.
 * @param  a           Point in the other Convex Hull
 * @param  b           Start point for the walk on all points in U
 * @param  U           This Convex Hull
 * @param  direction   Clockwise(1) / Counterclockwise(-1) for the walk.
 * @param  orientation Clockwise(1) / Counterclockwise(-1) for computing the cross product in isTangent
 * @return             A point b for which (ab) is a tanget to U
 */
template<class HullPoint>
HullPoint* ConvexHullAlgorithm<HullPoint>::findTangent(HullPoint *a, HullPoint *b, HullPoint* U, int direction, int orientation)
{
    while(!isTangent(a,b,U,orientation))
    {
        b = orientation == 1 ? b->next : b->prev;
    }

    return b;
}


/**
 * Combines two non-intersecting Convex Hulls into one
 * @param  A First Convex Hull
 * @param  B Second Convex Hull
 * @return   Combinex Convex Hull
 */
template<class HullPoint>
HullPoint* ConvexHullAlgorithm<HullPoint>::combine(HullPoint* A, HullPoint* B)
{
    HullPoint *rightA = getMinMax(A, 1);
    HullPoint *leftB = getMinMax(B, -1);

    HullPoint *a = rightA;
    HullPoint *b = leftB;

    while(true)
    {
        // Case 1
        b = findTangent(a, b, B, 1, 1);
        // Case 4
        if (isTangent(b, a, A, -1)) break;
        // Case 4
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
        // Case 2
        b = findTangent(a, b, B, -1, -1);
        // Case 3
        if (isTangent(b, a, A, 1)) break;
        // Case 3
        a = findTangent(b, a, A, 1, 1);
        // Case 2
        if (isTangent(a, b, B, -1)) break;
    }

    HullPoint *lowerA = a;
    HullPoint *lowerB = b;

    upperA->next = upperB;
    upperB->prev = upperA;

    lowerA->prev = lowerB;
    lowerB->next = lowerA;

    //cout << "Upper tangent is : " << upperA->index <<" , " <<upperB->index<<endl;
    //cout << "Lower tangent is : " << lowerA->index <<" , " <<lowerB->index<<endl;

    return upperA;
}


/**
 * Divide and conquire method the finding the Convex Hull of all Points in U.
 * Base Case 1 : The Convex Hull of 1 point is that point.
 * Base Case 2 : The Convex Hull of 2 points is the 2 points.
 * @param  U All points for which to find the convex hull.
 * @param  l Left index of current subset of points.
 * @param  r Right index of current subset of points.
 * @return A HullPoints* that's any element in the Convex Hull Doubly Linked List.
 */
template<class HullPoint>
HullPoint* ConvexHullAlgorithm<HullPoint>::computeConvexHull(std::vector<Point*> U, int l, int r)
{
    if ( l == r )
    {
        HullPoint *a = new HullPoint(U[l]->x, U[l]->y, l);
        a->next = a; a->prev = a;
        return a;
    }

    if ( l + 1 == r)
    {
        HullPoint *a, *b;
        a = new HullPoint(U[l]->x, U[l]->y, l);
        b = new HullPoint(U[r]->x, U[r]->y, r);

        a->next = b; a->prev = b;
        b->next = a; b->prev = a;

        return a;
    }

    int mid = (l + r) / 2;

    HullPoint* A = computeConvexHull(U,l, mid);
    HullPoint* B = computeConvexHull(U,mid+1, r);

    return combine(A,B);
}
