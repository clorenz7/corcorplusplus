/*
You are playing the following Bulls and Cows game with your friend: You write down a number and ask your friend to guess what the number is. Each time your friend makes a guess, you provide a hint that indicates how many digits in said guess match your secret number exactly in both digit and position (called "bulls") and how many digits match the secret number but locate in the wrong position (called "cows"). Your friend will use successive guesses and hints to eventually derive the secret number.

Write a function to return a hint according to the secret number and friend's guess, use A to indicate the bulls and B to indicate the cows.

Please note that both secret number and friend's guess may contain duplicate digits.

Example 1:

Input: secret = "1807", guess = "7810"

Output: "1A3B"

Explanation: 1 bull and 3 cows. The bull is 8, the cows are 0, 1 and 7.
Example 2:

Input: secret = "1123", guess = "0111"

Output: "1A1B"

Explanation: The 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is a cow.
Note: You may assume that the secret number and your friend's guess only contain digits, and their lengths are always equal.
*/
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    string getHint(string secret, string guess) {
        int bulls = 0;
        int cows = 0;
        unordered_map<int, int> secret_map(10);
        unordered_map<int, int> guess_map(10);
        int value,incr,skey,gkey;

        for (int i=0; i < guess.size(); i++) {
            if (secret[i] == guess[i]) {
                bulls++;
            } else {
                skey = int(secret[i]);
                gkey = int(guess[i]);
                auto search = secret_map.find(skey);
                if ( search == secret_map.end() ) {
                    secret_map.insert({skey, 1});
                } else {
                    search->second++;
                }

                search = guess_map.find(gkey);
                if ( search == guess_map.end() ) {
                    guess_map.insert({gkey, 1});
                } else {
                    search->second++;
                }

            }
        }

        for (auto it = secret_map.begin(); it != secret_map.end(); ++it) {
            auto search = guess_map.find(it->first);
            if ( search != guess_map.end() ) {
                incr = min(it->second, search->second);
                cows += incr;
            }
        }

        return to_string(bulls) + "A" + to_string(cows) + "B";
    }
};


// #include <iostream>
// #include <string>
// #include <unordered_map>
// using namespace std;

// class Solution {
// public:
//     string getHint(string secret, string guess) {
//         int bulls = 0;
//         int cows = 0;
//         unordered_map<int, int> char_map;
//         int key = 0;


//         for (int i=0; i < guess.size(); i++) {
//             if (secret[i] == guess[i]) {
//                 bulls++;
//             } else {
//                 key = int(guess[i]);
//                 auto search = char_map.find(key);
//                 if ( search == char_map.end() ) {
//                     char_map.insert({key, 1});
//                 } else {
//                     search->second++;
//                 }
//             }
//         }

//         for (int i=0; i < guess.size(); i++) {
//             if (secret[i] != guess[i]) {
//                 key = int(secret[i]);
//                 auto search = char_map.find(key);
//                 if ( search != char_map.end() ) {
//                     if (search->second != 0) {
//                         cows++;
//                         search->second--;
//                     }
//                 }
//             }
//         }

//         return to_string(bulls) + "A" + to_string(cows) + "B";
//     }
// };



int main () {

    Solution s = Solution();

    string result = s.getHint("1807", "7810");
    cout << "expect: '1A3B', got:" <<  result << endl;

    result = s.getHint("1123", "0111");
    cout << "expect: '1A1B', got:" <<  result << endl;

    return 0;
}