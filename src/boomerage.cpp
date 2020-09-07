/*
A boomerang is a set of 3 points that are all distinct and not in a straight line.

Given a list of three points in the plane, return whether these points are a boomerang.



Example 1:

Input: [[1,1],[2,3],[3,2]]
Output: true
Example 2:

Input: [[1,1],[2,2],[3,3]]
Output: false
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isBoomerang(vector<vector<int>>& points) {
        // If points are in a straight line, the ratio of the difference between the
        // second an the first  is equal to the diff of the third and the second

        int deltaX1 = points[1][0] - points[0][0];
        int deltaY1 = points[1][1] - points[0][1];

        int deltaX2 = points[2][0] - points[1][0];
        int deltaY2 = points[2][1] - points[1][1];


        // Check for repeated point
        if (deltaX1 == 0 && deltaY1 == 0)
            return false;
        if (deltaX2 == 0 && deltaY2 == 0)
            return false;

        // Check for zeros in denominator
        if (deltaX1 == 0 && deltaX2 == 0)
            return false;
        if (deltaY1 == 0 && deltaY2 == 0)
            return false;

        if (deltaX2 == 0 || deltaX1 == 0) {
            // example [0,1], [0,2], [1,2]
            if (deltaY2 == 0 || deltaY1 == 0) {
                return true;
            }

            cout << "X/Y" << (deltaX2/deltaY2) << (deltaX1/deltaY1) << endl;
            return ((float)deltaX2/deltaY2) != ((float)deltaX1/deltaY1);
        } else {
            cout << "Y/X" << deltaY2 << deltaX2 << deltaY1 <<deltaX1 << endl;
            return ((float)deltaY2/deltaX2) != ((float)deltaY1/deltaX1);
        }

    }
};


int main () {

    Solution s = Solution();

    // vector<vector<int>> pts{ {1,1},{2,3}, {3,2}};
    // cout << "expect: true, got:" <<  s.isBoomerang(pts) << endl;

    // vector<vector<int>> pts2{ {1,1},{2,2}, {3,3}};
    // cout << "expect: false, got:" <<  s.isBoomerang(pts2) << endl;

    // vector<vector<int>> pts3{ {0,0},{2,2}, {2,2}};
    // cout << "expect: false, got:" <<  s.isBoomerang(pts3) << endl;

    // vector<vector<int>> pts4{{0,1}, {2,1}, {0,0}};
    // bool result = s.isBoomerang(pts4);
    // cout << "expect: true, got:" <<  result << endl;

    vector<vector<int>> pts5{{0,1}, {1,1}, {2,1}};
    bool result = s.isBoomerang(pts5);
    cout << "expect: false, got:" <<  result << endl;


    return 0;
}
