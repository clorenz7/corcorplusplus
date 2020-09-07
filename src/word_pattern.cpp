/*
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in
pattern and a non-empty word in str.

Example 1:

Input: pattern = "abba", str = "dog cat cat dog"
Output: true
Example 2:

Input:pattern = "abba", str = "dog cat cat fish"
Output: false
Example 3:

Input: pattern = "aaaa", str = "dog cat cat dog"
Output: false
Example 4:

Input: pattern = "abba", str = "dog dog dog dog"
Output: false
Notes:
You may assume pattern contains only lowercase letters, and str
contains lowercase letters that may be separated by a single space.
*/

#include<iostream>
#include<map>
#include<sstream>
#include<unordered_set>

using namespace std;

class Solution {
public:
    bool wordPattern(string pattern, string str) {

        int n_chars = pattern.size();
        int char_idx = 0;

        string word;
        stringstream str_stream(str);
        char key;

        unordered_set<string> words = unordered_set<string>();
        map<char, string> char_to_str = map<char, string>();

        while ( getline(str_stream, word, ' ') ) {

            // See if we have exceeded the size of str
            if ( char_idx >= n_chars )
                return false;

            key = pattern[char_idx];

            auto it = char_to_str.find(key);

            if ( it == char_to_str.end() ) {
                char_to_str[key] = word;  // Was not in the map
                // If this word is already in the set of words, return false
                if ( words.count(word) > 0 ) {
                    return false;
                }
                words.insert(word);
            } else if ( it->second != word ) {
                return false;
            }

            char_idx++;
        }

        // Return true if # of chars and words match
        return char_idx == n_chars ;
    }
};

int main() {

    string pattern = "abba";
    string str = "dog cat cat dog";
    bool output;

    Solution s = Solution();
    output = s.wordPattern(pattern, str);
    cout << "Expect 1, got: " << output << endl;

    pattern = "abba";
    str = "dog cat cat fish";
    output = s.wordPattern(pattern, str);
    cout << "Expect 0, got: " << output << endl;


    pattern = "aaaa";
    str = "dog cat cat dog";
    output = s.wordPattern(pattern, str);
    cout << "Expect 0, got: " << output << endl;

    pattern = "abba";
    str = "dog dog dog dog";
    output = s.wordPattern(pattern, str);
    cout << "Expect 0, got: " << output << endl;

    return 0;
}
