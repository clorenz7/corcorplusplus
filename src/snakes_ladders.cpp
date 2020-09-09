/*
On an N x N board, the numbers from 1 to N*N are written boustrophedonically 
starting from the bottom left of the board, and alternating direction each row.  
For example, for a 6 x 6 board, the numbers are written as follows:


You start on square 1 of the board (which is always in the last row and 
first column). Each move, starting from square x, consists of the following:

    You choose a destination square S with number x+1, x+2, x+3, x+4, x+5, or x+6,
    provided this number is <= N*N.
    (This choice simulates the result of a standard 6-sided die roll: ie., 
    there are always at most 6 destinations, regardless of the size of the board.)
    If S has a snake or ladder, you move to the destination of that snake or ladder.  
    Otherwise, you move to S.

A board square on row r and column c has a "snake or ladder" if board[r][c] != -1.  
The destination of that snake or ladder is board[r][c].

Note that you only take a snake or ladder at most once per move: if the 
destination to a snake or ladder is the start of another snake or ladder, you do not continue moving.  (For example, if the board is `[[4,-1],[-1,3]]`, and on the first move your destination square is `2`, then you finish your first move at `3`, because you do not continue moving to `4`.)

Return the least number of moves required to reach square N*N.  
If it is not possible, return -1.

Example 1:

Input: [
[-1,-1,-1,-1,-1,-1],
[-1,-1,-1,-1,-1,-1],
[-1,-1,-1,-1,-1,-1],
[-1,35,-1,-1,13,-1],
[-1,-1,-1,-1,-1,-1],
[-1,15,-1,-1,-1,-1]]
Output: 4
Explanation: 
At the beginning, you start at square 1 [at row 5, column 0].
You decide to move to square 2, and must take the ladder to square 15.
You then decide to move to square 17 (row 3, column 5), 
and must take the snake to square 13.
You then decide to move to square 14, and must take the ladder to square 35.
You then decide to move to square 36, ending the game.
It can be shown that you need at least 4 moves to reach the N*N-th square, 
so the answer is 4.

Notes:
    2 <= board.length = board[0].length <= 20
    board[i][j] is between 1 and N*N or is equal to -1.
    The board square with number 1 has no snake or ladder.
    The board square with number N*N has no snake or ladder.

*/
#include<iostream>

#include<vector>
#include<queue>
#include<utility>

using namespace std;


void board_index_to_coords(int index, int N, int& i, int& j) {
	i = (N-1 - (index-1)/N);
	j = (index-1) % N;
	if ( (N % 2) == 0 ) {
		if ( (i % 2 ) == 0 ) 
			j = N-1 - j;
	} else {
		if ( (i % 2 ) == 1 ) 
			j = N-1 - j;
	}
}


class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int N = board.size();
        int n_sq = N*N;
        int i,j, idx, to_idx;
        int steps = 0;
        pair<int, int>* square;

        vector<bool> visited(n_sq, false);

        queue<pair<int, int>> q;
        q.push(pair<int, int>(0, 1));
        while (!q.empty() ) {

		    square = &(q.front());
	        steps = square->first;
	        idx = square->second;
	        q.pop();

	        board_index_to_coords(idx, N, i, j);
	        to_idx = board[i][j];

		    visited[idx-1] = true;

	        if ( idx == n_sq ) 
	        	return steps;

	        if ( to_idx == -1 ) 
		   		to_idx = idx;
		   	else if ( to_idx == n_sq) 
	   			return steps;
		   		
		   	for (int t_idx=to_idx+1; t_idx <= min(to_idx + 6, n_sq); ++t_idx) {
	        	if ( !visited[t_idx-1] ) 
	        		q.push(pair<int, int>(steps+1, t_idx));	
		    }
        }
        return -1;
    }
};


int main() {
	
	// Test the coordinate function
	int i,j, out;
	
	board_index_to_coords(1, 6, i, j);
	cout << i << " " << j << endl;

	board_index_to_coords(7, 6, i, j);
	cout << i << " " << j << endl;

	board_index_to_coords(30, 6, i, j);
	cout << i << " " << j << endl;
	board_index_to_coords(35, 6, i, j);
	cout << i << " " << j << endl;

	board_index_to_coords(36, 6, i, j);
	cout << i << " " << j << endl;


	// Test the main program
	auto s = Solution();

	vector<vector<int>> board = {
		{-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1},
		{-1,35,-1,-1,13,-1},
		{-1,-1,-1,-1,-1,-1},
		{-1,15,-1,-1,-1,-1}
	};
	out = s.snakesAndLadders(board);
	cout << "Expected 4, got: " << out << endl;

	vector<vector<int>> board1 = {
		{-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1},
		{-1,36,-1,-1,28,-1},
		{-1,-1,-1,-1,-1,-1},
		{-1,13,-1,-1,-1,-1}
	};
	out = s.snakesAndLadders(board1);
	cout << "Expected 2, got: " << out << endl;


	vector<vector<int>> board2 = {
		{-1, 2, 3, 4, 5, 6},
		{ 7, 8,9, 9, 8,  7},
		{-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1},
		{-1,15,-1,-1,-1,-1}
	};
	out = s.snakesAndLadders(board2);
	cout << "Expected -1, got: " << out << endl;

	vector<vector<int>> board3 = {
		{-1,-1,-1},
		{-1,9,8},
		{-1,8,9}
	};
	out = s.snakesAndLadders(board3);
	cout << "Expected 1, got: " << out << endl;

	vector<vector<int>> board4 = {
		{-1,1,2,-1},
		{2,13,15,-1},
		{-1,10,-1,-1},
		{-1,6,2,8}
	};
	out = s.snakesAndLadders(board4);
	cout << "Expected 2, got: " << out << endl;

	vector<vector<int>> board5 = {{-1,4,-1},{6,2,6},{-1,3,-1}};
	out = s.snakesAndLadders(board5);
	cout << "Expected 2, got: " << out << endl;

	vector<vector<int>> board6 ={
		{-1,11,6,-1 },
		{-1,15,16,-1},
		{-1,7,-1,8  },
		{-1,-1,-1,8 }
	};
	out = s.snakesAndLadders(board6);
	cout << "Expected 2, got: " << out << endl;

	vector<vector<int>> board7 = {
		{-1,-1,30,14,15,-1},
		{23,9,-1,-1,-1,9  },
		{12,5,7,24,-1,30  },
		{10,-1,-1,-1,25,17},
		{32,-1,28,-1,-1,32},
		{-1,-1,23,-1,13,19}
	};
	out = s.snakesAndLadders(board7);
	cout << "Expected 2, got: " << out << endl;

	vector<vector<int>> board8 = {
		{-1,-1,-1,30,-1,144,124,135,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,167,93,-1,-1,-1,-1,-1  },
		{-1,-1,-1,-1,-1,-1,-1,77,-1,-1,90,-1,-1   },
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1   },
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,122,-1  } ,
		{-1,-1,-1,23,-1,-1,-1,-1,-1,155,-1,-1,-1  },
		{-1,-1,140,29,-1,-1,-1,-1,-1,-1,-1,-1,-1  },
		{-1,-1,-1,-1,-1,115,-1,-1,-1,109,-1,-1,5  },
		{-1,57,-1,99,121,-1,-1,132,-1,-1,-1,-1,-1 },
		{-1,48,-1,-1,-1,68,-1,-1,-1,-1,31,-1,-1   },
		{-1,163,147,-1,77,-1,-1,114,-1,-1,80,-1,-1},
		{-1,-1,-1,-1,-1,57,28,-1,-1,129,-1,-1,-1  },
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,87,-1,-1,-1   }
	};
	out = s.snakesAndLadders(board8);
	cout << "Expected 6, got: " << out << endl;

	return 0;
}
