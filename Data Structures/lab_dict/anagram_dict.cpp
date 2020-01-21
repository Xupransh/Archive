/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;


/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    vector<string> words;
    if (wordsFile.is_open()) {
        while (getline(wordsFile, word)) {
            words.push_back(word);
        }
    }
    AnagramDictHelper(words);
}

void AnagramDict::AnagramDictHelper(const vector<string>& words) {
    for(auto & s : words) {
        string sorted(s);
        stable_sort(sorted.begin(), sorted.end());
        auto it = dict.find(sorted);
        if (it == dict.end()) {
            vector<string> vec;
            vec.push_back(s);
            dict[sorted] = vec;
        } else {
            it->second.push_back(s);
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    AnagramDictHelper(words);
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string sorted(word);
    stable_sort(sorted.begin(), sorted.end());
    auto word_it = dict.find(sorted);
    if (word_it != dict.end()) {
        return word_it->second;
    }
    return vector<string> ();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector< vector<string> > result;
    vector<string> temp;
    for (auto & it : dict) {
        if (it.second.size() > 1) {
            result.push_back(it.second);
        }
    }
    return result;
}
