/*
Write a program to find the nth super ugly number.

Super ugly numbers are positive numbers whose all prime factors are in the
given prime list primes of size k.

Example:
Input: n = 12, primes = [2,7,13,19]
Output: 32
Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12
             super ugly numbers given primes = [2,7,13,19] of size 4.


Strategy:
(1) start with 1 and the list of primes
(2) index starts at first non-one prime.
(3) insert prime multiples at the end and heapify
(4) Increment index
(5) Quit when the index == n.
*/

#include<vector>
#include<iterator>
#include<iostream>
#include<cmath>
#include<queue>
#define ll long long int

using namespace std;


void print(vector<int>& heap) {
    for (int q=0; q < min((int)heap.size(), 1000); q++) {
        cout << heap[q] << " ";
    }
    cout << endl;
}


void sift_up(vector<int>& heap, int index) {
    int p_index = (index-1)/2;

    if ( p_index < 0 ) {
        return;
    }

    int p_val = heap[p_index];

    if (heap[index] < p_val) {
        heap[p_index] = heap[index];
        heap[index] = p_val;

        sift_up(heap, p_index);
    }
}

void heap_insert(vector<int>& heap, int value) {
    heap.push_back(value);
    sift_up(heap, heap.size()-1);
}


void sift_down(vector<int>& heap, int index) {
    int l_idx = index*2+1;
    int r_idx = l_idx+1;
    int small_idx = index;
    int p_value = heap[index];

    if (l_idx < heap.size()) {
        small_idx = l_idx;
    }
    if (r_idx < heap.size() && heap[r_idx] < heap[small_idx]) {
        small_idx = r_idx;
    }

    if ( p_value > heap[small_idx] ) {
        heap[index] = heap[small_idx];
        heap[small_idx] = p_value;

        sift_down(heap, small_idx);
    }
}

int heap_pop(vector<int>& heap) {
    int value = heap[0];
    heap[0] = heap[heap.size()-1];

    heap.erase(heap.end()-1);

    sift_down(heap, 0);

    return value;
}




class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {

        vector<int> heap = vector<int>();
        int output = 1;
        int i = 1;
        float value;
        int h_size;
        int nextVal;
        int checkVal;
        float limitVal = min(2147483647., pow(primes[0], n-1.));
        priority_queue<ll, vector<ll>, greater<ll>> pq={};


        // Insert the initial primes
        for (int j = 0; j < primes.size(); j++) {
            heap.push_back(primes[j]);
            // pq.push(primes[j]);
        }

        while (i < n) {
            nextVal = heap_pop(heap);
            // nextVal = pq.top();

            while ( heap.size() > 0 && nextVal == heap[0] ) {
                checkVal = heap_pop(heap);
            }
            // while (!pq.empty() && pq.top() == nextVal) {
            //     pq.pop();
            // }

            for (int j = 0; j < primes.size(); j++) {
                value = float(nextVal)*primes[j];

                if ( value <= limitVal ) {
                    heap_insert(heap, nextVal*primes[j]);
                    // pq.push(nextVal*primes[j]);
                }
            }

            if (nextVal != output) {
                i++;
                output = nextVal;
            }
        }

        print(heap);

        return output;
    }
};

int main() {

    Solution s = Solution();

    vector<int> primes = {2,7,13,19};

    int num = s.nthSuperUglyNumber(12, primes);

    cout << "Expected 32, got: " << num << endl;

    primes = {2};

    num = s.nthSuperUglyNumber(2, primes);

    cout << "Expected 2, got: " << num << endl;


    primes = {
        7,19,29,37,41,47,53,59,61,79,83,89,101,
        103,109,127,131,137,139,157,167,179,181,
        199,211,229,233,239,241,251
    };
    num = s.nthSuperUglyNumber(100000, primes);

    cout << "Expected 1092889481, got: " << num << endl;

    return 0;
}