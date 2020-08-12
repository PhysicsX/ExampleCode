#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * 
 * Trie is an efficient information retrieval data structure. 
 * If keys are stored in binary search tree, a well balanced BST
 * will need time proportional to M * log N, where M is maximum string
 * length and N is number of keys in tree. Using Trie, we can search the key
 * O(M) time. However the penalty is on Trie storage requirements.
 * 
 * */

const int ALPHABET_SIZE = 26;

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
};

TrieNode *getNode(void)
{
    struct TrieNode *pNode = new TrieNode;
    pNode->isEndOfWord = false;
    
    for(int i=0; i < ALPHABET_SIZE; i++)
    {
        pNode->children[i] = NULL;
    }
    
    return pNode;
}

void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
    
    for(int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if(!pCrawl->children[index])
            pCrawl->children[index] = getNode();
            
        pCrawl = pCrawl->children[index];
    }
    
    pCrawl->isEndOfWord = true;
}


void display(struct TrieNode* root, char str[], int level)
{
    if(root->isEndOfWord != false)
    {
        str[level] = '\0';
        cout<<str<<endl;
    }
    
    for(int i=0; i < ALPHABET_SIZE; i++)    
    {
        
        if(root->children[i])
        {
            str[level] = i + 'a';
            display(root->children[i], str, level + 1);
        }
    }
    
}

bool search(struct TrieNode *root, string key)
{
        struct TrieNode *pCrawl = root;
        
        for(int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';
            if(!pCrawl->children[index])
                return false;
                
            pCrawl = pCrawl->children[index];
        }
        
        return (pCrawl != NULL && pCrawl->isEndOfWord);
}

int main()
{
    
    string keys[] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    
    int n = sizeof(keys)/sizeof(keys[0]);
    struct TrieNode *root = getNode();
    
    
    for(int i=0; i < n; i++)
        insert(root, keys[i]);
    
    
    search(root, "the") ? cout<<"Yes\n" : cout<<"No\n";
    search(root, "there") ? cout<<"Yes\n" : cout<<"No\n";
    search(root, "these") ? cout<<"Yes\n" : cout<<"No\n";
    char str[20];
    display(root, str, 0);
    
    return 0;
}