// Trie
// C++
#include <iostream>
#include <string>
using namespace std;
const int ALPHABET_SIZE = 26;

// trie node
struct TrieNode {
    TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
};
// Returns new trie node (initialized to NULLs)
TrieNode *getNode() {
    TrieNode *pNode = new TrieNode;
    pNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;
    return pNode;
}
// Inserts key into trie
void insert(TrieNode *root, const string& key) {
    TrieNode *pCrawl = root;
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
        pCrawl = pCrawl->children[index];
    }
    pCrawl->isEndOfWord = true;
}
// Returns true if key is present in trie, else false
bool search(TrieNode *root, const string& key) {
    TrieNode *pCrawl = root;
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;
        pCrawl = pCrawl->children[index];
    }
    return pCrawl != nullptr && pCrawl->isEndOfWord;
}



// Driver program
int main() {
    // example:
    // string keys[] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    // int n = sizeof(keys) / sizeof(keys[0]);
    // TrieNode *root = getNode();
    // for (int i = 0; i < n; i++)
    //     insert(root, keys[i]);
    // cout << "the" << " --- " << (search(root, "the") ? "Present in trie" : "Not present in trie") << endl;
    // cout << "these" << " --- " << (search(root, "these") ? "Present in trie" : "Not present in trie") << endl;
    // cout << "their" << " --- " << (search(root, "their") ? "Present in trie" : "Not present in trie") << endl;
    // cout << "thaw" << " --- " << (search(root, "thaw") ? "Present in trie" : "Not present in trie") << endl;
    return 0;
}
