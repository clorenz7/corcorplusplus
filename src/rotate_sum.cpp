/* Given an array of integers A and let n to be its length.

Assume Bk to be an array obtained by rotating the array A k positions clock-wise, we define a "rotation function" F on A as follow:

F(k) = 0 * Bk[0] + 1 * Bk[1] + ... + (n-1) * Bk[n-1].

Calculate the maximum value of F(0), F(1), ..., F(n-1).

Note:
n is guaranteed to be less than 105.

Example:

A = [4, 3, 2, 6]

F(0) = (0 * 4) + (1 * 3) + (2 * 2) + (3 * 6) = 0 + 3 + 4 + 18 = 25
F(1) = (0 * 6) + (1 * 4) + (2 * 3) + (3 * 2) = 0 + 4 + 6 + 6 = 16
F(2) = (0 * 2) + (1 * 6) + (2 * 4) + (3 * 3) = 0 + 6 + 8 + 9 = 23
F(3) = (0 * 3) + (1 * 2) + (2 * 6) + (3 * 4) = 0 + 2 + 12 + 12 = 26

So the maximum value of F(0), F(1), F(2), F(3) is F(3) = 26.
*/
#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int maxRotateFunction(vector<int>& A) {
        
        // Needed to do all this weird long long stuff for 32-bit validator. 
        long long int arraySum = 0;
        int N = A.size();
        long long int maxVal = 0;
        long long int newSum, lastSum;

        // Calculate the sum of the numbers
        for (int i = 0; i < N; ++i) {
            arraySum += A[i];
            maxVal += i*A[i];
        }
        lastSum = maxVal;

        for (int i = 1; i < N; ++i) {
            newSum = lastSum + arraySum - N*(long long)A[N-i];
            if ( newSum > maxVal ) {
                maxVal = newSum;
            }
            lastSum = newSum;
        }      

        return int(maxVal);
    }
};

int main() {

    Solution s = Solution();
    int out;

    vector<int> A = {4, 3, 2, 6};
    out = s.maxRotateFunction(A);
    cout << "Expected 26, got: " << out << endl;    

    A = {2147483647, 2147483647};
    out = s.maxRotateFunction(A);
    cout << "Expected x, got: " << out << endl;   

    return 0;
}