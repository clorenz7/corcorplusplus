/*
Your country has an infinite number of lakes. Initially, all the lakes are empty, but when it rains over the nth lake, the nth lake becomes full of water. If it rains over a lake which is full of water, there will be a flood. Your goal is to avoid the flood in any lake.

Given an integer array rains where:

    rains[i] > 0 means there will be rains over the rains[i] lake.
    rains[i] == 0 means there are no rains this day and you can choose one lake this day and dry it.

Return an array ans where:

    ans.length == rains.length
    ans[i] == -1 if rains[i] > 0.
    ans[i] is the lake you choose to dry in the ith day if rains[i] == 0.

If there are multiple valid answers return any of them. If it is impossible to avoid flood return an empty array.

Notice that if you chose to dry a full lake, it becomes empty, but if you chose to dry an empty lake, nothing changes. (see example 4)

 

Example 1:

Input: rains = [1,2,3,4]
Output: [-1,-1,-1,-1]
Explanation: After the first day full lakes are [1]
After the second day full lakes are [1,2]
After the third day full lakes are [1,2,3]
After the fourth day full lakes are [1,2,3,4]
There's no day to dry any lake and there is no flood in any lake.

Example 2:

Input: rains = [1,2,0,0,2,1]
Output: [-1,-1,2,1,-1,-1]
Explanation: After the first day full lakes are [1]
After the second day full lakes are [1,2]
After the third day, we dry lake 2. Full lakes are [1]
After the fourth day, we dry lake 1. There is no full lakes.
After the fifth day, full lakes are [2].
After the sixth day, full lakes are [1,2].
It is easy that this scenario is flood-free. [-1,-1,1,2,-1,-1] is another acceptable scenario.

Example 3:

Input: rains = [1,2,0,1,2]
Output: []
Explanation: After the second day, full lakes are  [1,2]. We have to dry one lake in the third day.
After that, it will rain over lakes [1,2]. It's easy to prove that no matter which lake you choose to dry in the 3rd day, the other one will flood.

Example 4:

Input: rains = [69,0,0,0,69]
Output: [-1,69,1,1,-1]
Explanation: Any solution on one of the forms [-1,69,x,y,-1], [-1,x,69,y,-1] or [-1,x,y,69,-1] is acceptable where 1 <= x,y <= 10^9

Example 5:

Input: rains = [10,20,20]
Output: []
Explanation: It will rain over lake 20 two consecutive days. There is no chance to dry any lake.

*/
/* 
strategy:

(1) Maintain a set of full lakes. 
(2) Maintain a queue of unused no rain days
(3) For each rain day, we check if it is in the set. 
    If it is in the set already, we leave it in the set, pop off the queue, and fill in the output
        If nothing in queue, we return invalid output
    If not in set, we add it. 

(4) At end, dry lake 1 if queue not empty

Issue: You have to make sure you are not drying too early. 
So you need to search an ordered set of dryDays

*/


#include<iostream>
#include<set>
#include<unordered_map>
#include<vector>

using namespace std;

class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        vector<int> INVALID = {};
        vector<int> output(rains.size(), -1);

        unordered_map<int,int> wetLakes; // lake# : day got wet
        set<int> dryDays;
        int dryDay, rainDay, lake;

        for (int d = 0; d < rains.size(); ++d) {
            lake = rains[d];
            if ( lake == 0 ) { // dry day
                dryDays.insert(d);
            } else {
                // Determine the lake is alreay full
                auto it = wetLakes.find(lake);
                if ( it == wetLakes.end() ) { // It is empty
                    // The lake is now wet
                    wetLakes.insert(pair<int, int>(lake, d));
                } else {
                    // We need to look for a dry day after the day it filled 
                    rainDay = it->second;
                    if ( dryDays.empty() ) {
                        return INVALID;
                    } else {
                        // Loop over dry days to see if one works
                        auto dit=dryDays.begin();
                        for (dit; dit != dryDays.end(); ++dit) {
                            dryDay = *dit;
                            if ( rainDay < dryDay ) { // found one
                                output[dryDay] = lake;
                                // remove from list of dry days
                                dryDays.erase(dryDay); 
                                // Update the day the lake got wet
                                wetLakes[lake] = d; 
                                break;
                            }
                        }
                        // If we have reached the end, we were unable to find a day
                        if ( dit == dryDays.end() )
                            return INVALID;
                    }
                }
            }
        }

        // Fill all of the remaining dry days with the first lake. 
        for (auto dit=dryDays.begin(); dit != dryDays.end(); ++dit) 
            output[*dit] = 1;
        
        return output;
    }
};


// Unit Tests
int main() {

    Solution s = Solution();
    vector<int> rains, out;


    rains = {1,2,0,0,2,1};
    out = s.avoidFlood(rains);
    for (auto it=out.begin(); it != out.end(); ++it) 
        cout << *it << " ";
    cout << endl;

    rains = {1,2,0,1,2};
    out = s.avoidFlood(rains);
    for (auto it=out.begin(); it != out.end(); ++it) 
        cout << *it << " ";
    cout << endl;

    rains = {69,0,0,0,69};
    out = s.avoidFlood(rains);
    for (auto it=out.begin(); it != out.end(); ++it) 
        cout << *it << " ";
    cout << endl;

    rains = {2,3,0,0,3,1,0,1,0,2,2};
    out = s.avoidFlood(rains);
    for (auto it=out.begin(); it != out.end(); ++it) 
        cout << *it << " ";
    cout << endl;

    return 0;
}