#pragma once

#include <cstddef>
#include <cassert>

//templates are the way to go, but feel like cheating b/c they weren't in the course
//but List HAS to be universal and agnostic of its contents, so it's worthwhile cheating
//alternatively, one could use
//using T = Bunny;
//but EVEN THEN it should have treated T as universal, not using any Bunny-specific things here
template<typename T>
class DoublyLinkedList
{
public:
    struct iterator;
    DoublyLinkedList();

    size_t size() const { return sz; }
    iterator begin() const { return *head; }
    iterator end() const { return *tail; }

    void push_back(T elem);
    void erase(iterator);

private:
    iterator *head, *tail;
    size_t sz{ 0 };
};

template<typename T>
struct DoublyLinkedList<T>::iterator
{
           T* data{ nullptr };
    iterator* next{ nullptr };
    iterator* prev{ nullptr };

          T&    operator* ()        { return *data; }
    const T&    operator* () const  { return *data; }
          T*    operator->()        { return  data; }
    const T*    operator->() const  { return  data; }

    bool operator==(const iterator& other) const { return next==other.next || prev==other.prev; }
    bool operator!=(const iterator& other) const { return !(*this==other); }
    iterator operator++()
    {
        if (next)
        {
            data = next->data;
            prev = next->prev;
            next = next->next;
        }
        else
        {
            data = nullptr;
            prev = nullptr;
        }
        return *this;
    }
};




template<typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
    head = tail = new iterator;
}

template<typename T>
void DoublyLinkedList<T>::push_back(T elem)
{
    tail->data = new T(elem);
    tail->next = new iterator;
    tail->next->prev = tail;
    tail = tail->next;

    ++sz;
}

template<typename T>
void DoublyLinkedList<T>::erase(DoublyLinkedList::iterator it)
{
    (it.prev ? it.prev->next : head) = it.next;
    it.next->prev = it.prev;
    delete it.data;
    --sz;
}
