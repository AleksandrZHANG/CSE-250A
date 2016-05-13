/**
 *  CSE 100 PA3
 *  Authors: Yihong Zhang, Hao Gai
 *  Date: 5.11.2016 
*/

#include "util.hpp"
#include "DictionaryTrie.hpp"

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie() {
  root = new TSTNode('0');
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  // if the input is empty, return flase
  if( word.empty() ) return false;
  // insert word
  TSTNode* cur = root;
  for( int i = 0; i <(int) word.size(); i++ ) {
    if(freq>cur->maxfreq)
      cur->maxfreq=freq;
    cur = cur->insert(word[i]);
  }
  if( cur->isword ) return false;
  cur->isword=true;
  cur->freq=freq;
  return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  // if the input is empty, return false
  if( word.empty() ) return false;
  // find the word
  TSTNode* cur = root;
  for( int i = 0; i <(int) word.size(); i++ ) {
    if( (cur=cur->findnext(word[i])) == 0 )
        return false;
  }
  return cur->isword;
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
void DFS(std::priority_queue<std::pair<std::string,unsigned int>,std::vector<std::pair<std::string,unsigned int> >,PairComp> &ret,TSTNode* root,std::string cur,unsigned int & num_completions){
    if(root==0)
      return ;
    if(root->isword&&ret.size()<num_completions){
        ret.push(make_pair(cur+root->key,root->freq));
    }
    else if(root->isword&&root->freq>ret.top().second){
        ret.push(make_pair(cur+root->key,root->freq));
        ret.pop();
    }
    
    if( root->lchild!=0 )
        DFS(ret,root->lchild,cur,num_completions);
    if(root->rchild!=0)
        DFS(ret,root->rchild,cur,num_completions);
    if(root->echild!=0){
	if(ret.size()<num_completions||root->maxfreq>ret.top().second)
            DFS(ret,root->echild,cur+root->key,num_completions);
    }
}
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
    std::vector<std::string> words;
    std::priority_queue<std::pair<std::string,unsigned int>,std::vector<std::pair<std::string,unsigned int> >,PairComp>ret;
    if(prefix.empty()||num_completions<=0)
        return words;
    TSTNode* cur=root;
    for(int i=0;i<(int)prefix.size();i++){
        cur=cur->findnext(prefix[i]);
        if(cur==0)
            return words;
    }
    if(cur->isword){
      ret.push(make_pair(prefix,cur->freq));
    }
    cur=cur->echild;
   
    DFS(ret,cur,prefix,num_completions);
    
    int sz=ret.size();
    words.resize(sz);
    for(int i=0;i<sz;i++){
        words[sz-1-i]=ret.top().first;
        ret.pop();
    }
    
    return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){
    delete root;
}
