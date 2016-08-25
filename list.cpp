#include "list.h"

List::List()
{
    this->Head = NULL;
    this->Tail = NULL;
}
void List::append(ReaderInfo* info){
    if(this->Head == NULL){
        Node* s = new Node(info,NULL,NULL);
        this->Head = this->Tail = s;
    }
    else{
        Node* s = new Node(info,this->Tail,NULL);
        this->Tail->next = s;
        this->Tail = s;
    }
}

void List::remove(std::string id){
    if(this->Head->info->getId() == id){
        Node* t = this->Head;
        this->Head = this->Head->next;
        delete t;
    }
    else if(this->Tail->info->getId() == id){
        Node* t = this->Tail;
        this->Tail = this->Tail->front;
        delete t;
    }
    Node* s = Head;
    while(s->next){
        if(s->next->info->getId() == id){
            Node* t = s->next;
            s->next = t->next;
            t->next->front = s;
            delete t;
        }
    }
}

ReaderInfo* List::get(std::string id){
    for(Node* s = this->Head;s;s = s->next){
        if(s->info->getId() == id){
            return s->info;
        }
    }
    return NULL;
}

void List::each(){
    for(Node* s = this->Head;s;s = s->next){
        s->info->display();
    }
}
