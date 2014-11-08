#include "ConvexHullAlgorithm.h"

std::atomic<int> ConvexHullAlgorithm::maxThreads{0};

ConvexHullAlgorithm::ConvexHullAlgorithm(std::vector<Point*> InputPoints,int l, int r)
{
    this->InputPoints = InputPoints;
    this->l=l;
    this->r=r;
}

std::vector<Point*> ConvexHullAlgorithm::start()
{
    int min = ( l + r ) / 2;

    this->omega = this->computeConvexHull(l, r);


    HullPoint *z = this->omega;

    std::vector<Point*> temp;

    do
    {
        temp.push_back(this->InputPoints[z->index]);
        z = z->next;
    } while ( z!=this->omega );

    this->OutputPoints = temp;

    return temp;
}


double ConvexHullAlgorithm::getCrossProductZ(HullPoint a, HullPoint b, HullPoint c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}


HullPoint* ConvexHullAlgorithm::getMinMax(HullPoint *A, int orientation)
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

bool ConvexHullAlgorithm::isTangent(HullPoint *a, HullPoint *b, HullPoint* U, int orientation)
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

HullPoint* ConvexHullAlgorithm::findTangent(HullPoint *a, HullPoint *b, HullPoint* U, int direction, int orientation)
{
    while(!isTangent(a,b,U,orientation))
    {
        b = orientation == 1 ? b->next : b->prev;
    }

    return b;
}


HullPoint* ConvexHullAlgorithm::combine(HullPoint* A, HullPoint* B)
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

// std::atomic<int> usedThreads(0);

HullPoint* ConvexHullAlgorithm::computeConvexHull(int l, int r)
{
    if ( l == r )
    {
        HullPoint *a = new HullPoint(this->InputPoints[l]->x, this->InputPoints[l]->y, l);
        a->next = a; a->prev = a;
        return a;
    }

    if ( l + 1 == r)
    {
        HullPoint *a, *b;
        a = new HullPoint(this->InputPoints[l]->x, this->InputPoints[l]->y, l);
        b = new HullPoint(this->InputPoints[r]->x, this->InputPoints[r]->y, r);

        a->next = b; a->prev = b;
        b->next = a; b->prev = a;

        return a;
    }

    int mid = (l + r) / 2;

    HullPoint *A;
    HullPoint *B;

    if ( ConvexHullAlgorithm::maxThreads >= 2 )
    {
        A = computeConvexHull(l, mid);
        B = computeConvexHull(mid+1, r);

    }
    else
    {
        ConvexHullAlgorithm c(InputPoints, l, mid);
        std::thread t(&ConvexHullAlgorithm::start, &c); ConvexHullAlgorithm::maxThreads++;
        B = computeConvexHull(mid+1, r);

        t.join();

        ConvexHullAlgorithm::maxThreads--;
        A = c.omega;
    }



    return combine(A,B);
}
