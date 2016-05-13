/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <vector>
#include <string>
#include<queue>
/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class TSTNode { // Ternary Search Trie Node
public:
  char key;
  bool isword;
  unsigned int freq;
  unsigned int maxfreq;
  TSTNode* lchild; // the char is smaller than this char
  TSTNode* rchild; // the char is equal to this char
  TSTNode* echild; // the char is bigger than this char
  
  TSTNode(char key, bool isword=false, unsigned int freq=0,unsigned int maxfreq=0):isword(isword),freq(freq),maxfreq(maxfreq) {
    this->key = key;
    lchild = 0;
    rchild = 0;
    echild = 0;
  }

  TSTNode* insert(char c) {
    TSTNode* ret = 0;
    TSTNode* p = 0;
    // put char c under the previous char in the string
    if( this->echild == 0 ) {
      this->echild = new TSTNode(c);
      return this->echild;
    }
    // find and insert all the chars of the string in the tree
    ret = this->echild;
    while( ret != 0 ) {
      // three different results of comparison
      if( ret->key == c ) return ret;
      else if( ret->key < c ) {
        p = ret;
        ret = ret->rchild;
        if( ret == 0 ) {
          p->rchild = new TSTNode(c);
          return p->rchild;
        }
      }
      else {
        p = ret;
        ret = ret->lchild;
        if( ret == 0 ) {
          p->lchild = new TSTNode(c);
          return p->lchild;
        }
      }
    }
    return ret;
  }

  TSTNode* findnext(char c) {
    TSTNode* next = 0;
    // if the following char is 0, then the search ends
    if( this->echild == 0 ) return this->echild;
    // find the char c in tree
    next = this->echild;
    while( next != 0 ) {
      if( next->key == c ) return next;
      else if( next->key < c ) next = next->rchild;
      else next = next->lchild;
    }

    return next;
  } 

  ~TSTNode() {
      delete lchild;
      delete rchild;
      delete echild;
  }

};

class PairComp {
public:
  bool operator()(std::pair<std::string, unsigned int>& p1,
                           std::pair<std::string, unsigned int>& p2) const {
    if( p1.second > p2.second ) return true;
    else if( p1.second < p2.second ) return false;
    else return p1.first < p2.first;
  }
};

class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

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
  std::vector<std::string>  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

private:
  // Add your own data members and methods here
  TSTNode* root;
};

#endif // DICTIONARY_TRIE_HPP
