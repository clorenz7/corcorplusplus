/* 
You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'. Each move consists of turning one wheel one slot.

The lock initially starts at '0000', a string representing the state of the 4 wheels.

You are given a list of deadends dead ends, meaning if the lock displays any of these codes, the wheels of the lock will stop turning and you will be unable to open it.

Given a target representing the value of the wheels that will unlock the lock, return the minimum total number of turns required to open the lock, or -1 if it is impossible.

 

Example 1:

Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
Output: 6
Explanation:
A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
because the wheels of the lock become stuck after the display becomes the dead end "0102".

Example 2:

Input: deadends = ["8888"], target = "0009"
Output: 1
Explanation:
We can turn the last wheel in reverse to move from "0000" -> "0009".

Example 3:

Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
Output: -1
Explanation:
We can't reach the target without getting stuck.

Example 4:

Input: deadends = ["0000"], target = "8888"
Output: -1
*/

/* 
Thoughts:
(1) BFS
(2) Keep a binary array keyed on integer rep (faster than a set of strings)
(3) Keep a queue of which nodes to visit
(4) Next available is easy, +-1, 10, 100, 1000 (8 possible)
(5) Probably want to keep state as 4 int array for easy modular operations. 
(5) Quit when queue is empty
*/

#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<unordered_set>

using namespace std;

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {

        int targ = stoi(target);
        int lockState[4] = {0};
        int n_spins = 0;
        int lockInt;
        int origDial;
        int factor; 
        int visited[10000] = {0};
        unordered_set<int> deadSet;
        queue<int> Q;
        Q.push(0);

        // Convert deadends to a set of ints
        for (auto it=deadends.begin(); it != deadends.end(); ++it) {
            // deadSet.emplace(stoi(*it));
            visited[stoi(*it)] = -1;
        }
        if ( visited[0] == -1 )
            return -1;
        if ( target == "0000" ) {
            return 0;
        }

        while ( !Q.empty() ) {
            lockInt = Q.front();
            Q.pop();

            n_spins = visited[lockInt];

            lockState[3] = lockInt % 10;
            lockState[2] = (lockInt % 100)/10;
            lockState[1] = (lockInt % 1000)/100;
            lockState[0] = lockInt /1000;

            for (int i = 0; i < 4; ++i) {
                origDial = lockState[i];

                for (int j = -1; j <=1; j+=2) {
                    lockState[i] = ((origDial + j+10) % 10);

                    // cout << "Lock State: ";
                    // for (int k = 0; k < 4; ++k) { 
                    //     cout << lockState[k];
                    // }
                    // cout << endl;

                    // This can be cleaned up by doing deltas rather than re summing each time. 
                    lockInt = 1000*lockState[0] + 100*lockState[1] + 10*lockState[2] + lockState[3];

                    // cout << "Lock Int: " << lockInt << endl;

                    if ( visited[lockInt] == 0 ) {
                        if ( lockInt == targ ) {
                            return n_spins+1;
                        }
                        visited[lockInt] = (n_spins+1);
                        // cout << "Pushing " << lockInt << endl; 
                        Q.push(lockInt);
                    }
                }
                lockState[i] = origDial;
            }
        }

        return -1;
    }
};


int main() {
    
    Solution s = Solution();
    vector<string> deadends;
    int out; 

    deadends = {"0201","0101","0102","1212","2002"};
    out = s.openLock(deadends, "0202");
    cout <<"Expected 6, got: " << out << endl;

    deadends = {"8887","8889","8878","8898","8788","8988","7888","9888"}; 
    out = s.openLock(deadends, "8888");
    cout <<"Expected -1, got: " << out << endl;

    out = s.openLock(deadends, "0009");
    cout <<"Expected 1, got: " << out << endl;

    deadends = {"0000"};
    out = s.openLock(deadends, "8888");
    cout <<"Expected -1, got: " << out << endl;

    return 0;
}