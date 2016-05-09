#include "util.hpp"
#include "DictionaryTrie.hpp"

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie():root(nullptr) {}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
    bool flag = false;
    if (word.empty()) {
        return flag;
    }
    if (root == nullptr) {
        root = new TSTNode(word[0]);
    }
    TSTNode* curr = root;
    int l = word.length();
    int i = 0;
    while(i < l) {
        if (word[i] == curr->letter) {
            if (i == (l-1)) {
                curr->freq = freq;
            	if (curr->middle != 0) {
		    curr->freq = freq;
                    flag = true;
                }
		return flag;
            }
            if (curr->middle == 0) {
                curr->middle = new TSTNode(word[i+1]);
                flag = true;
            }
            curr = curr->middle;
            i++;
        }
        if (word[i] < curr->letter) {
            if (curr->left == 0) {
                curr->left = new TSTNode(word[i]);
                flag = true;
            }
            curr = curr->left;
        }
        if (word[i] > curr->letter) {
            if (curr->right == 0) {
                curr->right = new TSTNode(word[i]);
                flag = true;
            }
            curr = curr->right;
        }
    }
    return flag;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
    TSTNode* curr = root;
    for (int i = 0; i < word.length(); i++) {
        while (curr->letter != word[i]) {
            if (word[i] < curr->letter) {
                curr = curr->left;
            }
            if (word[i] > curr->letter) {
                curr = curr->right;
            }
            if (curr == 0) {
                return false;
            }
        }
        curr = curr->middle;
    }
    return true;
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){}
