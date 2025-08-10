#include "DoublyLinkedList.h"

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : length(0)
{
    head = new Node(); // dummy head
    tail = new Node(); // dummy tail
    head->next = tail;
    tail->prev = head;
}

template <typename T>
DoublyLinkedList<T> :: ~DoublyLinkedList(){
    while (head) {
        Node* del = head;
        head = head->next;
        delete del;
    }
}

template <typename T>
void DoublyLinkedList<T> :: insertAtHead(T data){
    Node* newNode = new Node(data, head, head->next);
    head->next->prev = newNode;
    head->next = newNode;
    ++length;
}

template <typename T>
void DoublyLinkedList<T>::insertAtTail(T data) {
    Node* newNode = new Node(data, tail->prev, tail);
    tail->prev->next = newNode;
    tail->prev = newNode;
    ++length;
}

template <typename T>
void DoublyLinkedList<T> :: insertAt(int index, T data){
    if (index<0 || index > length) return;
    if (index == 0) {
        insertAtHead(data);
        return;
    }
    if (index == length) {
        insertAtTail(data);
        return;
    }
    Node* cur = head->next;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }

    Node* newNode = new Node(data);
    newNode->prev      = cur->prev;
    newNode->next      = cur;
    cur->prev->next     = newNode;
    cur->prev           = newNode;

    length++;

}

template <typename T>
void DoublyLinkedList<T> :: deleteAt(int index){
    if (index<0 || index >= length) return;

    if (index == 0) {
        if (length == 0) return;
        Node* toDelete = head->next;
        head->next = toDelete->next;
        toDelete->next->prev = head;
        delete toDelete;
        --length;
        return;
    }
    if (index == length - 1) {
        if (length == 0) return;
        Node* toDelete = tail->prev;
        tail->prev = toDelete->prev;
        toDelete->prev->next = tail;
        delete toDelete;
        --length;
        return;
    }

    Node* cur = head->next;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }
    
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    delete cur;

    length--;
}

template <typename T>
int DoublyLinkedList<T>::size() const {
    return length;
}

template <typename T>
T& DoublyLinkedList<T> :: get(int index) const{
    if (index < 0 || index >= length) {
        throw out_of_range("Index is invalid!");
    }
    
    Node* tmp = head->next;
    while (index>0){
        index--;
        tmp = tmp->next;
    }
    
    return tmp->data;

}

template <typename T>
int DoublyLinkedList<T> :: indexOf(T item) const{
    Node* tmp = head->next;
    int idx=0;
    while (tmp!=tail){
        if ( tmp->data == item) return idx;
        idx++;
        tmp=tmp->next;
    }
    return -1;
}

template <typename T>
bool DoublyLinkedList<T> :: contains(T item) const{
    Node* tmp = head->next;
    while (tmp!=tail){
        if ( tmp->data == item) return 1;
        tmp=tmp->next;
    }
    return 0;
}

template <typename T>
void DoublyLinkedList<T> :: reverse(){
    Node* left = head->next;
    Node* right = tail->prev;
    for (int i=0; i<length/2; i++){
        T tmp = left->data;
        left->data = right->data;
        right->data = tmp;
        right = right->prev;
        left = left->next;
    }
}

template <typename T>
string DoublyLinkedList<T> :: toString(string (*convert2str)(T&)) const {
    ostringstream oss;
    oss << '[';
    Node* curr = head->next;
    while (curr != tail) {
        if (convert2str)
            oss << convert2str(curr->data);
        else
            oss << curr->data;

        curr = curr->next;
        if (curr != tail)
            oss << ", ";
    }
    oss << ']';
    return oss.str();
}

// Explicit template instantiation for char, string, int, double, float, and Point
template class DoublyLinkedList<char>;
template class DoublyLinkedList<string>;
template class DoublyLinkedList<int>;
template class DoublyLinkedList<double>;
template class DoublyLinkedList<float>;
template class DoublyLinkedList<Point>;