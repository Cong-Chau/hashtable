#include <iostream>
using namespace std;

#define M 10

struct Node {
    int key;
    Node* next;
};

typedef Node* HashTable[M];

void InitHashtable(HashTable& HT) {
    for (int i = 0; i < M; i++)
        HT[i] = NULL;
}

int Hash(int k) {
    return k % M;
}

void AddTail(Node*& l, int k) {
    Node* newNode = new Node{ k, NULL };
    if (l == NULL) {
        l = newNode;
    }
    else {
        Node* p = l;
        while (p != NULL && p->next != NULL)
            p = p->next;
        p->next = newNode;
    }
}

void InsertNode(HashTable& HT, int k) {
    int i = Hash(k);
    AddTail(HT[i], k);
}

void DeleteHead(Node*& l) {
    if (l != NULL) {
        Node* p = l;
        l = l->next;
        delete p;
    }
}

void DeleteAfter(Node*& q) {
    Node* p = q->next;
    if (p != NULL) {
        q->next = p->next;
        delete p;
    }
}

void DeleteNode(HashTable& HT, int k) {
    int i = Hash(k);
    Node* p = HT[i];
    Node* q = p;
    while (p != NULL && p->key != k) {
        q = p;
        p = p->next;
    }
    if (p == NULL)
        cout << k << " not found!" << endl;
    else if (p == HT[i])
        DeleteHead(HT[i]);
    else
        DeleteAfter(q);
}

Node* SearchNode(HashTable HT, int k) {
    int i = Hash(k);
    Node* p = HT[i];
    while (p != NULL && p->key != k)
        p = p->next;
    if (p == NULL)
        return NULL;
    return p;
}

void Traverse(Node* p) {
    while (p != NULL) {
        cout << p->key << ' ';
        p = p->next;
    }
    cout << endl;
}

void TraverseHashTable(HashTable HT) {
    for (int i = 0; i < M; i++) {
        cout << "Bucket " << i << ": ";
        Traverse(HT[i]);
    }
}

int main(){
    HashTable mHashTable;
    Node* hashtable[M];
//    InitHashTable(mHashTable);
    for (int i = 0; i < M; i++)
        mHashTable[i] = NULL;

    int a[] = {1,5,6,78,4,3,7,45,13,14,18,11,98,56,34,48};

    for (int i = 0; i < (sizeof(a) / sizeof(a[0])); i++) {
        InsertNode(mHashTable, a[i]);
    }
    cout << "HashTable:n";
    TraverseHashTable(mHashTable);

    /*DeleteNode(mHashTable, 3);
    DeleteNode(mHashTable, 13);
    DeleteNode(mHashTable, 9);*/
//    cout << "HashTable after Delete:n";
//    TraverseHashTable(mHashTable);

    Node* result = SearchNode(mHashTable, 10);
    if (result == NULL)
        cout << "Not found!";
    else
        cout << "Found!";

    std::cout << std::endl;
    system("pause");
    return 0;
}