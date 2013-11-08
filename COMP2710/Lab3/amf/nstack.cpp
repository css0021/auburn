#include "nstack.h"
#include <cstdlib>
#include <iostream>
#include <cstddef>
using std::cout;

namespace nstack {

    template<class T>
    Stack<T>::Stack() {
        top = NULL;
    }
    template<class T>
    bool Stack<T>::isEmpty() const {
        return (top == NULL);
    }
    template<class T>
    void Stack<T>::advance(T nItem) {
        top = new Node<T>(nItem, top);
        top.setStatus(true);
    }

    template<class T>
    T Stack<T>::backtrace() {
        top.setStatus(false);
        if (top == NULL) {
            cout << "Stack is empty.\n";
        }
        else {
            Node<T>* away;
            away = top;
            T out = top->getData();
            top = top->getPrev();
            delete away;
            return out;

        }

    }
}



