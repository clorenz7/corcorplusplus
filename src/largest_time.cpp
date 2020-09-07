/*
Given an array of 4 digits, return the largest 24 hour time that can be made.

The smallest 24 hour time is 00:00, and the largest is 23:59.  Starting from 00:00, a time is larger if more time has elapsed since midnight.

Return the answer as a string of length 5.  If no valid time can be made, return an empty string.



Example 1:

Input: A = [1,2,3,4]
Output: "23:41"
Example 2:

Input: A = [5,5,5,5]
Output: ""
Example 3:

Input: A = [0,0,0,0]
Output: "00:00"
Example 4:

Input: A = [0,0,1,0]
Output: "10:00"
*/

#include<vector>
#include<string>
#include<iostream>
using namespace std;

class Solution {
public:
    string largestTimeFromDigits(vector<int>& A) {

        sort(A.begin(), A.end());

        for (int f = 3; f >=0; f--) {
            if (A[f] > 2)
                continue;

            for (int s=3; s>=0; s--) {
                if (s == f)
                    continue;

                if (A[s] + A[f]*10 > 23)
                    continue;

                for (int t=3; t >=0; t--) {
                    if (A[t] >= 6)
                        continue;
                    if (t == s || t == f)
                        continue;

                    for (int l=0; l < 4; l++) {
                        if (l == s || l == t || l == f)
                            continue;
                        return to_string(A[f]) + to_string(A[s]) + string(":") + to_string(A[t]) + to_string(A[l]);
                    }
                }
            }

        }
        return string("");
    }
};


int main () {

    Solution s = Solution();

    string large_time;

    vector<int> in_dig({1,2,3,4});

    large_time = s.largestTimeFromDigits(in_dig);

    cout << "Expected 23:41, got " << large_time << endl;

    vector<int> in_dig2({5,5,5,5});

    large_time = s.largestTimeFromDigits(in_dig2);

    cout << "Expected , got " << large_time << endl;

    return 0;
}

