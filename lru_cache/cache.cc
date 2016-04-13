// Implement LRU cache
// Runtime O(1)

#include <iostream>
#include <unordered_map>

#define CACHE_SIZE 10

using namespace std;

template<class K, class V>
struct Node
{
    K key;
    V value;
    Node<K,V>* left;
    Node<K,V>* right;
    Node(K k, V v) : key(k), value(v) {}
};

template<class K, class V>
class Cache
{
    public:
        void Put(K key, V value);
        V Get(K key);
    private:
        Node<K,V>* left;
        Node<K,V>* right;
        unordered_map<K, Node<K,V>*> positions;

        void UpdatePriority(K key);
        void Eject();
        void Add(K key, V value);
};

template<class K, class V>
void Cache<K,V>::Eject()
{
    if (CACHE_SIZE == 1)
    {
        K toDelete = left->key;
        positions.erase(positions.find(toDelete));

        delete left;

        left = right = NULL;

        return;
    }

    Node<K,V>* toDelete = right;

    right = right->left;

    positions.erase(positions.find(toDelete->key));

    delete toDelete;
}

template<class K, class V>
void Cache<K,V>::Add(K key, V value)
{
    Node<K,V>* newNode = new Node<K,V>(key,value);

    newNode->left = newNode->right = NULL;

    if (positions.size() == 0)
    {
        left = right = newNode;

        positions[key] = newNode;

        return;
    }

    newNode->right = left;
    left->left = newNode;
    left = newNode;

    positions[key] = newNode;
}

template<class K, class V>
void Cache<K,V>::UpdatePriority(K key)
{
    Node<K,V>* highestPriority = positions[key];

    if (positions.size() == 1 || highestPriority == left)
    {
        return;
    }

    if (highestPriority == right)
    {
        right->left->right = NULL;
        right = right->left;

        left->right->left = highestPriority;

        highestPriority->right = left;
        highestPriority->left = NULL;

        left = highestPriority;

        return;
    }

    // Remove highestPriority from middle
    highestPriority->left->right = highestPriority->right;
    highestPriority->right->left = highestPriority->left;

    left->right->left = highestPriority;

    highestPriority->right = left;
    highestPriority->left = NULL;

    left = highestPriority;

}

template<class K, class V>
void Cache<K,V>::Put(K key, V value)
{
    // Update, Add, Add and Eject
    if (positions.count(key) > 0)
    {
        UpdatePriority(key);
        positions[key]->value = value;

        return;
    }

    if (positions.size() >= CACHE_SIZE)
    {
        Eject();
    }

    Add(key, value);
}

template<class K, class V>
V Cache<K,V>::Get(K key)
{
    if (positions.count(key) == 0)
    {
        throw;
    }

    UpdatePriority(key);

    return positions.at(key)->value;
}

int main()
{
    Cache<int,int> cache;

    for (int i=1; i<=15; ++i)
    {
        cache.Put(i,i);
    }

    cache.Get(7);
    cache.Put(16,16);

    return 0;
}

