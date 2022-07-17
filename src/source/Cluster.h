#ifndef CLUSTERLIST_CLUSTER_H
#define CLUSTERLIST_CLUSTER_H

#include "Settings.h"

template<class T>
class Cluster {
private:
    class Node {
    private:
        static clt::type_clAmount m_clNum;
        T *border  = nullptr;
        Node *prev = nullptr;
        Node *next = nullptr;
    public:
        Node() = default;
        Node(T* border, Node* prev = nullptr, Node* next = nullptr)
                : border(border),
                  prev(prev),
                  next(next)
        {}

        clt::type_elemAmount length() const;
        T getValue(clt::type_elemAmount) const;
        void lshift(clt::type_elemAmount = 1);
        void rshift(clt::type_elemAmount = 1);
        void remove();
        T* operator& () const; // to get value of this border;

        friend class Cluster;
    };
private:
    Node* head = nullptr;
    Node* tail = nullptr;
private:
    Node* getFirstGreaterCluster(const T*) const;
    Node* getNode(clt::type_clAmount) const;
    bool isUniqueBorder(const T*) const;
public:
    Cluster() = default;
    Cluster(T*, T*);
    Cluster(const Cluster&);
    Cluster(const Cluster&, Cluster) = delete;
    ~Cluster();

    void clear(); // delete all borders except head and tail
    void insert(clt::type_elemAmount);
    clt::type_clAmount getClusterAmount() const;
    clt::type_elemAmount length() const;
    bool isEmpty() const;

    Node& operator[] (clt::type_clAmount nodeIndex) const;
    Cluster* operator &();
};
template<class T>
typename clt::type_clAmount Cluster<T>::Node::m_clNum = 1;

//----------[PUBLIC]
template<class T>
Cluster<T>::Cluster(T* pBegin, T* pEnd) {
    head = new Node(pBegin, nullptr, nullptr);
    tail = new Node(pEnd, head, nullptr);
    head->next = tail;
}

template<class T>
Cluster<T>::Cluster(const Cluster& other) {
    head = new Node(other.head->border, nullptr, nullptr);
    tail = new Node(other.tail->border, head, nullptr);
    head->next = tail;

    for(Node* temp = other.head->next; temp; temp = temp->next)
        insert((clt::type_elemAmount)(temp->border - head->border));
}

template<class T>
Cluster<T>::~Cluster() {
    clear();
    delete tail;
    delete head;
}

template<class T>
void Cluster<T>::clear() {
    for(Node* temp = head->next; temp->next;) {
        Node* a = temp->next;
        temp->remove();
        temp = a;
    }
}

template<class T>
void Cluster<T>::insert(clt::type_elemAmount border) {
    T* checkBorder = (T*)(head->border + border);
    if(head->border < checkBorder && checkBorder < tail->border) {
        if(!isUniqueBorder(checkBorder))
            return;

        Node::m_clNum++;

        // insertAfter <-> body <-> insertBehind
        Node *insertBehind = getFirstGreaterCluster(checkBorder);
        Node *insertAfter = insertBehind->prev;
        Node *body = new Node(checkBorder, insertAfter, insertBehind);

        insertAfter->next = body;
        insertBehind->prev = body;
    }
}

template<class T>
clt::type_clAmount Cluster<T>::getClusterAmount() const {
    return Node::m_clNum;
}

template<class T>
clt::type_elemAmount Cluster<T>::length() const {
    return tail->border - head->border;
}

template<class T>
bool Cluster<T>::isEmpty() const {
    return !head;
}
//----------[PRIVATE]
template<class T>
typename Cluster<T>::Node* Cluster<T>::getFirstGreaterCluster(const T* border) const {
    Node* output;
    for(output = head; output->border < border; output = output->next);
    return output;
}

template<class T>
typename Cluster<T>::Node* Cluster<T>::getNode(clt::type_clAmount nodeIndex) const {
    Node* output;
    clt::type_clAmount i = 0;
    for(output = head; i < nodeIndex; output = output->next, i++);
    return output;
}

template<class T>
bool Cluster<T>::isUniqueBorder(const T* border) const {
    for(Node* temp = tail->prev; temp; temp = temp->prev)
        if(temp->border == border)
            return false;
    return true;
}

template<class T>
typename Cluster<T>::Node &Cluster<T>::operator[](clt::type_clAmount nodeIndex) const {
    if(nodeIndex >= 0 && nodeIndex < Node::m_clNum)
        return *getNode(nodeIndex);
}

template<class T>
Cluster<T>* Cluster<T>::operator&() {
    return this;
}
//----------[PRIVATE->NODE_DECLARE]
template<class T>
clt::type_elemAmount Cluster<T>::Node::length() const {
    if(next)
        return next->border - border;
    return 0;
}

template<class T>
T Cluster<T>::Node::getValue(clt::type_elemAmount index) const {
    if(index >= 0 && index < length())
        return border[index];
    // return -1;
}

template<class T>
void Cluster<T>::Node::remove() {
    Node* nextNode = next;
    Node* prevNode = prev;
    if(prevNode && nextNode) {
        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        delete this;
        m_clNum--;
    }
}

template<class T>
void Cluster<T>::Node::lshift(clt::type_elemAmount shift) {
    if((shift >= 0 && shift < prev->length()) && prev)
        border -= shift;
}

template<class T>
void Cluster<T>::Node::rshift(clt::type_elemAmount shift) {
    if((shift >= 0 && shift < length()) && next && prev)
        border += shift;
}

template<class T>
T *Cluster<T>::Node::operator&() const {
    return border;
}

#endif // CLUSTERLIST_CLUSTER_H