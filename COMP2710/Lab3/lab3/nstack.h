#ifndef NSTACK_H_INCLUDED
#define NSTACK_H_INCLUDED

namespace nstack
{
    template<typename const T&>
    class Stack {
        public:
            Stack();
            Stack(const Stack<T>& cStack);
            Stack<T>& operator =(const Stack<T>& rightSide);
            virtual ~Stack();
            bool isEmpty() const;
            void push(T nItem);
            T pop();
            int size();
            T type(); {return *top;}

        private:
            Node<T>* top;

    };

     class Node {
        public:
            Node();
            Node(T data);
            Node<T>* getLink(T direction) const {return link};
            const T getData() const {return name;}
            void setName(T& n_name) {name = n_name;}
            void attachNewNode(Node<T>* newNode, T direction) {attachedNodes[direction] = newNode;}
            Node<T> getAttachedNode(T direction) const {return attachedNodes[direction];}
        private:
            T name;
            Node<T> Stack;
    };

}
#endif // NSTACK_H_INCLUDED
