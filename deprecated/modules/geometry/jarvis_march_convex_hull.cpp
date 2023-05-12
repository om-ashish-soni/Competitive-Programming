// A C++ program to find convex hull of a set of points. Refer
// https://www.geeksforgeeks.org/orientation-3-ordered-points/
// for explanation of orientation()
#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int x, y;
};

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (r.x-p.x) * (q.y-p.y) -
            (q.x - p.x) * (r.y - p.y);

    if (val == 0) return 0; // collinear
    // if (val == 0) return 0; // collinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

// Prints convex hull of a set of n points.
void convexHull(Point points[], int n)
{
    // There must be at least 3 points
    if (n < 3) return;

    // Initialize Result
    vector<Point> hull;

    // Find the leftmost point
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;

    // Start from leftmost point, keep moving counterclockwise
    // until reach the start point again. This loop runs O(h)
    // times where h is number of points in result or output.
    int p = l, q;
    do
    {
        // Add current point to result
        hull.push_back(points[p]);

        // Search for a point 'q' such that orientation(p, q,
        // x) is counterclockwise for all points 'x'. The idea
        // is to keep track of last visited most counterclock-
        // wise point in q. If any point 'i' is more counterclock-
        // wise than q, then update q.
        q = (p+1)%n;
        for (int i = 0; i < n; i++)
        {
        // If i is more counterclockwise than current q, then
        // update q
            // cout<<p<<" "<<q<<" "<<i<<endl;
            int orient=orientation(points[p], points[i], points[q]);
            if (orient == 2)
                q = i;
            else if(p!=i && q!=i && p!=q && orient==0){
                pair<int,int> pi,qi,ri;
                pi={points[p].x,points[p].y};
                qi={points[q].x,points[q].y};
                ri={points[i].x,points[i].y};
                vector<pair<int,int>> v={pi,qi,ri};
                sort(v.begin(),v.end());
                if(pi==v[0] && ri==v[2]) q=i;
                else if(pi==v[2] && ri==v[0]) q=i;
            }
            // cout<<"q : "<<q<<endl;
        }   
        // Now q is the most counterclockwise with respect to p
        // Set p as q for next iteration, so that q is added to
        // result 'hull'
        p = q;

    } while (p != l); // While we don't come to first point

    // Print Result
    for (int i = 0; i < hull.size(); i++)
        cout << "(" << hull[i].x << ", "
            << hull[i].y << ")\n";
}

// Driver program to test above functions
int main()
{
    Point points[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1},
                    {3, 0}, {0, 0},{1,0}, {3, 3}};
    int n = sizeof(points)/sizeof(points[0]);
    convexHull(points, n);
    return 0;
}
