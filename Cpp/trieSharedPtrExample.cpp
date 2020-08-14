#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

#define Size 26

class TrieNode
{
    public:
        shared_ptr<TrieNode> children[Size];
        
        bool isEndOfWord;
        
        TrieNode()
        {

            isEndOfWord = false;
        }
};

class Trie {
    
        shared_ptr<TrieNode> root;
        
        public:
            Trie()
            {
                root = make_shared<TrieNode>();
            }
            ~Trie()
            {}
            
            shared_ptr<TrieNode> getRoot()
            {
                return root;
            }
            
            int i2c(char c)
            {
                return static_cast<int>(c-'a');
            }
            
            void insertWord(string& trieString)
            {
                shared_ptr<TrieNode> current = root;
                
                for(int i = 0; i < trieString.size(); i++)
                {
                    if(current->children[i2c(trieString[i])] == shared_ptr<TrieNode>(nullptr))
                    {
                        current->children[i2c(trieString[i])] = make_shared<TrieNode>();
                    }
                    
                    current = current->children[i2c(trieString[i])];
                }
                
                current->isEndOfWord = true;
            }
            
            bool searchWord(string& trieString)
            {
                    shared_ptr<TrieNode> current = root;
                    
                    for(int i=0; i<trieString.size(); i++)
                    {
                        if(current->children[i2c(trieString[i])] == shared_ptr<TrieNode>(nullptr))
                            return false;
                        current = current->children[i2c(trieString[i])];
                    }
                    
                    if(current->isEndOfWord == true)
                        return true;
                    
                return false;
            }
        
            bool Partdelete(string& trieString, shared_ptr<TrieNode>& checkout)
            {
                    if(checkout == nullptr)
                        return false;
                        
                        
                    if (trieString.size() == 0) { 
                        if (checkout->isEndOfWord == true) { 
                            checkout->isEndOfWord = false; 
                            return true; 
                        } 
                        return false; 
                    }                        
                     
                    string part = trieString.substr(1);
                    if(Partdelete(part, checkout->children[i2c(trieString[0])]))
                    {
                        if(isEmptyNode(checkout->children[i2c(trieString[0])]))
                        {
                            checkout->children[i2c(trieString[0])].reset();
                            checkout->children[i2c(trieString[0])] == nullptr;
                            
                            return true;
                        }
                        else 
                            return true;
                    }
                    else
                        return false;
                        
                    return false;
            }
        
        
            bool deleteWord(string& trieString)
            {
                if(Partdelete(trieString, root))
                    return true;
                    
                return false;
            }
        
            bool isEmptyNode(shared_ptr<TrieNode> check) const
            {
                for(int i = 0; i < Size; i++)
                {
                    if(check->children[i] != nullptr || check->isEndOfWord == true)
                        return false;
                }
                
                return true;
            }
            
            void display(shared_ptr<TrieNode> node, string str, int level, vector<string>& vec)
            {
                
                if(node->isEndOfWord)
                {
                    string tmp = str;
                    tmp.erase(remove_if(tmp.begin(),tmp.end(),[](char c){
                        return isspace(c);
                    }),tmp.end());
                    //std::cout<<tmp.size();
                    vec.push_back(tmp);
                }
                
                for(int i=0; i< Size; i++)
                {
                    if(node->children[i])
                    {    
                        str[level] = i + 'a';
                        display(node->children[i], str, level + 1, vec);
                    }
                }
            
            }
        
};



        
int main()
{
    
    shared_ptr<Trie> myTrie(new Trie()); 
  
    string word1 = "ulas"; 
    string word2 = "ulasdikme"; 
    string word3 = "daledondale"; 
  
    myTrie->insertWord(word1); 
  
  
    if (myTrie->searchWord(word1)) 
        cout << word1 << ": Is Present" << endl; 
    else
        cout << word1 << ": Not Present" << endl; 
  
    if (myTrie->searchWord(word3)) 
        cout << word3 << ": Is Present" << endl; 
    else
        cout << word3 << ": Not Present" << endl; 
  
    myTrie->insertWord(word2); 
  
    if (myTrie->deleteWord(word2)) 
        cout << word2 << ": Successfully deleted" << endl; 
    else
        cout << word2 << ": Not Present" << endl; 
  
    if (myTrie->searchWord(word2)) 
        cout << word2 << ": Is Present" << endl; 
    else
        cout << word2 << ": Not Present" << endl; 
    
    myTrie->insertWord(word2);
    word2 = "a";
    myTrie->insertWord(word2);
    word2 = "b";
    myTrie->insertWord(word2);
    word2 = "c";
    myTrie->insertWord(word2);
    
    string str(20, ' ');
    vector<string> vec;
    //    char str[20];
    //myTrie->display(myTrie->getRoot(), str, 0, vec);
    myTrie->display(myTrie->getRoot(), str, 0, vec);
    for(auto s : vec)
        cout<<s<<endl;

    
    
    return 0;
}
        
       