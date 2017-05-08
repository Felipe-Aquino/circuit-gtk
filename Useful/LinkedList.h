#ifndef __LINKED_LIST_H_
#define __LINKED_LIST_H_

template<class T>
class ICompareable{
public:
    virtual int Compare(T*, T*) = 0;
};

template<class T>
class LinkedList {
    class Node;

    Node* FirstNode;
    Node* CurrentNode;

    int Size;
public:
    LinkedList();

    void Insert(T*);
    void Insert(T*, int);
    void Remove();
    void Remove(int);
    void Remove(T*);
    T* GetAt(int);
    int GetSize();

    void SetBeginning();
    T* GetNextInfo();

    T* operator[](int);

    void Sort(ICompareable<T>*);
    void ForEach(void (*CallBack)(T*));
    ~LinkedList();
};

class ILinkable{
public:
    virtual void Show() = 0;
    virtual ~ILinkable(){};
};

#endif
