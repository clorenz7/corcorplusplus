/*
You are given a map in form of a two-dimensional integer grid
where 1 represents land and 0 represents water.

Grid cells are connected horizontally/vertically (not diagonally).
The grid is completely surrounded by water, and there is exactly one island
(i.e., one or more connected land cells).

The island doesn't have "lakes" (water inside that isn't connected to
the water around the island). One cell is a square with side length 1.
The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.



Example:

Input:
[[0,1,0,0],
 [1,1,1,0],
 [0,1,0,0],
 [1,1,0,0]]

Output: 16

Explanation: The perimeter is the 16 yellow stripes in the image below:
*/

/* Strategy
(1) Can loop over every element in array. Check each of four directions,
and each that is 1 you subtract from 4 to get the perimeter contribution from that element.
(2) Could potentially avoid rechecking by storing a negative in the array, and then never checking up or left

*/

#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int perimeter = 0;
        int p_delta;

        int n_rows = grid.size();
        int n_cols = grid[0].size();


        for (int i = 0; i < n_rows; i++) {
            for (int j=0; j < n_cols; j++) {
                if (grid[i][j] != 0) {
                    p_delta = 4;

                    if (i > 0) {
                        if (grid[i-1][j] != 0) {
                            p_delta--;
                        }
                    }

                    if (j > 0) {
                        if (grid[i][j-1] != 0) {
                            p_delta--;
                        }
                    }

                    if ( i != (n_rows-1) ) {
                        if (grid[i+1][j] != 0) {
                            p_delta--;
                        }
                    }

                    if ( j != (n_cols-1) ) {
                        if (grid[i][j+1] != 0) {
                            p_delta--;
                        }

                    }

                    perimeter += p_delta;

                }
            }
        }

        return perimeter;
    }
};


int main() {
    Solution s = Solution();

    vector<vector<int>> grid =  {
        {0,1,0,0},
        {1,1,1,0},
        {0,1,0,0},
        {1,1,0,0}
    };

    int ret_val = s.islandPerimeter(grid);

    cout << ret_val << endl;

    return 0;
}
