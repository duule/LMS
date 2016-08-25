#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "readerinfo.h"

class List
{
    class Node{
    public:
        Node* next;
        Node* front;
        ReaderInfo* info;
        Node(ReaderInfo* info, Node* front, Node* next){
            this->info = info;
            this->front = front;
            this->next = next;
        }
    };
    Node* Head;
    Node* Tail;
public:
    List();
    void append(ReaderInfo* info);
    void remove(std::string id);
    ReaderInfo* get(std::string id);
    void each();
};

#endif // LIST_H
