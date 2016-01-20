#include <iostream>
#include <cstdlib>
#pragma GCC diagnostic ignored "-Wwrite-strings"

using namespace std;

#define NUMBER_OF_ALPHABET 26

class TrieNode
{
    public:
        TrieNode();
        bool IsEnd;
        TrieNode* children[NUMBER_OF_ALPHABET];
};

TrieNode::TrieNode()
{
    IsEnd = false;
    for (int i=0; i<NUMBER_OF_ALPHABET; ++i)
    {
        children[i] = NULL;
    }
}

class Trie
{
    public:
        Trie();
        void Insert(string line);
        bool IsMember(string line);
        void Output();
    private:
        TrieNode* head;
        void Output(TrieNode*, int);
};

Trie::Trie()
{
    head = new TrieNode();
}

void Trie::Insert(string line)
{
    TrieNode* current = head;

    for (int i=0; i<line.size(); ++i)
    {
        if (current->children[line[i]-'a'] == NULL)
        {
            current->children[line[i]-'a'] = new TrieNode();
        }

        current = current->children[line[i]-'a'];
    }

    current->IsEnd = true;
}

bool Trie::IsMember(string line)
{
    TrieNode* current = head;

    for (int i=0; i<line.size(); ++i)
    {
        if (current->children[line[i]-'a'] == NULL)
        {
            return false;
        }

        current = current->children[line[i]-'a'];
    }

    return current->IsEnd;
}

void Trie::Output()
{
    // Special case of emty string
    cout << ": " << ((head->IsEnd) ? '1' : '0') << endl;

    Output(head, 1);
}

void Trie::Output(TrieNode* node, int depth)
{
    for (int i=0; i< NUMBER_OF_ALPHABET; ++i)
    {
        if (node->children[i])
        {
            for (int j=0; j<depth; ++j)
            {
                cout << "      ";
            }

            cout << ((char) (i + 'a')) << ": ";
            cout << ((node->children[i]->IsEnd) ? '1' : '0') << endl;

            Output(node->children[i], depth + 1);
        }
    }
}

void CheckMemberAndDisplayResult(Trie* myTrie, char* str);

int main()
{
    Trie* myTrie = new Trie();

    myTrie->Insert("hello");
    myTrie->Insert("help");
    myTrie->Insert("helps");
    myTrie->Insert("hel");
    myTrie->Insert("");

    CheckMemberAndDisplayResult(myTrie, "hello");
    CheckMemberAndDisplayResult(myTrie, "ello");
    CheckMemberAndDisplayResult(myTrie, "");

    cout << endl << "Output of Trie Tree" << endl << endl;

    myTrie->Output();
}

void CheckMemberAndDisplayResult(Trie* myTrie, char* str)
{
    bool isMember = myTrie->IsMember(str);

    cout << '\'' << str << '\'' << " is"
         << (isMember ? "" : " NOT")
         << " a member." << endl; 
}

