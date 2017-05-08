#include "LinkedList.h"
#include <iostream>

template<class T>
class LinkedList<T>::Node{
    T* Info;
    Node* Next;
public:
    Node();
    Node(T*);
    Node(const Node&);

    void SetInfo(T*);
    T* GetInfo();

    void SetNext(Node* Next);
    Node* GetNext();

    ~Node();
};

template<class T>
LinkedList<T>::LinkedList(){
    CurrentNode = FirstNode = NULL;
    Size = 0;
}

template<class T>
void LinkedList<T>::Insert(T* Info){
    Node* NewNode = new Node(Info);
    NewNode->SetNext(FirstNode);
    FirstNode = NewNode;
    CurrentNode = FirstNode;
    Size++;
}

template<class T>
void LinkedList<T>::Insert(T* info, int i){
    Node* NewNode = new Node(info);
    if(i < 0) return;
    if(i >= Size){
        CurrentNode = FirstNode;
        while(CurrentNode->GetNext())
            CurrentNode = CurrentNode->GetNext();
        CurrentNode->SetNext(NewNode);
        Size++;
        return;
    }
    if(i == 0){
      Insert(info);
      return;
    }
    Node* PreviewsNode = FirstNode;
    CurrentNode = FirstNode;
    while(i--){
      PreviewsNode = CurrentNode;
      CurrentNode = CurrentNode->GetNext();
    }
    PreviewsNode->SetNext(NewNode);
    NewNode->SetNext(CurrentNode);
    Size++;
}

template<class T>
void LinkedList<T>::Remove(){
    Node* PrewiewNode = NULL;
    if(!FirstNode) return;

    PrewiewNode = CurrentNode = FirstNode;
    while(CurrentNode->GetNext()){
        PrewiewNode = CurrentNode;
        CurrentNode = CurrentNode->GetNext();
    }
    if(CurrentNode == FirstNode) FirstNode = NULL;
    PrewiewNode->SetNext(NULL);
    delete CurrentNode;
    CurrentNode = FirstNode;
    Size--;
}

template<class T>
void LinkedList<T>::Remove(int i){
    if(i < 0 || i >= Size) return;
    Node* AuxNode = CurrentNode;
    if(i == 0){
        CurrentNode = FirstNode;
        FirstNode = FirstNode->GetNext();
        delete CurrentNode;
        CurrentNode = AuxNode;
        Size--;
        return;
    }
    Node* PreviewsNode = FirstNode;
    CurrentNode = FirstNode;
    while(i--){
        PreviewsNode = CurrentNode;
        CurrentNode = CurrentNode->GetNext();
    }
    PreviewsNode->SetNext(CurrentNode->GetNext());
    delete CurrentNode;
    CurrentNode = AuxNode;
    Size--;
}

template<class T>
void LinkedList<T>::Remove(T* t){
    if(!t || !FirstNode) return;

    Node* PreviewsNode = FirstNode;
    CurrentNode = FirstNode;
    while(CurrentNode && CurrentNode->GetInfo() != t){
        PreviewsNode = CurrentNode;
        CurrentNode = CurrentNode->GetNext();
    }
    if(!CurrentNode) return;
    if(CurrentNode == FirstNode){
      CurrentNode = FirstNode->GetNext();
      delete FirstNode;
      FirstNode = CurrentNode;
      Size--;
      return;
    }
    PreviewsNode->SetNext(CurrentNode->GetNext());
    delete CurrentNode;
    CurrentNode = PreviewsNode->GetNext();
    Size--;
}


template<class T>
T* LinkedList<T>::GetAt(int i){
    CurrentNode = FirstNode;
    if(i >= Size) return NULL;
    while(i--) CurrentNode = CurrentNode->GetNext();
    return CurrentNode->GetInfo();
}

template<class T>
int LinkedList<T>::GetSize(){
    return Size;
}

template<class T>
void LinkedList<T>::SetBeginning(){
    CurrentNode = FirstNode;
}

template<class T>
T* LinkedList<T>::GetNextInfo(){
    if(!CurrentNode) return NULL;
    T* info = CurrentNode->GetInfo();
    CurrentNode = CurrentNode->GetNext();
    return info;
}

template<class T>
T* LinkedList<T>::operator[](int i){
    return GetAt(i);
}

template<class T>
void LinkedList<T>::ForEach(void (*CallBack)(T*)){
    SetBeginning();
    for(T* info = NULL; info = GetNextInfo();)
      CallBack(info);
}

template<class T>
void LinkedList<T>::Sort(ICompareable<T>* compareAble){
    for(int i = 0;i < Size-1;i++){
        Node* NextNode = FirstNode->GetNext();
        CurrentNode = FirstNode;    
        for(int j = 0;j < Size - i-1;j++) {
            if(compareAble->Compare(CurrentNode->GetInfo(), NextNode->GetInfo()) > 0){
                T* info = CurrentNode->GetInfo();
                CurrentNode->SetInfo(NextNode->GetInfo());
                NextNode->SetInfo(info);
            }
            
            CurrentNode = NextNode;
            NextNode = NextNode->GetNext();
        }
    }
}

template<class T>
LinkedList<T>::~LinkedList(){
    while(FirstNode){
        CurrentNode = FirstNode->GetNext();
        delete FirstNode;
        FirstNode = CurrentNode;
    }
}

template<class T>
LinkedList<T>::Node::Node(){
    Info = NULL;
    Next = NULL;
}

template<class T>
LinkedList<T>::Node::Node(const Node& node){
    Info = node.Info;
    Next = node.Next;
}

template<class T>
LinkedList<T>::Node::Node(T* Info){
    this->Info = Info;
    Next = NULL;
}

template<class T>
void LinkedList<T>::Node::SetInfo(T* Info){
    this->Info = Info;
}

template<class T>
T* LinkedList<T>::Node::GetInfo(){
    return Info;
}

template<class T>
void LinkedList<T>::Node::SetNext(Node* Next){
    this->Next = Next;
}

template<class T>
typename LinkedList<T>::Node* LinkedList<T>::Node::GetNext(){
    return Next;
}

template<class T>
LinkedList<T>::Node::~Node(){
    delete Info;
}

template class LinkedList<ILinkable>;
