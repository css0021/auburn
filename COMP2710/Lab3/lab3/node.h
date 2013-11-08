#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <string>


using std::string;

    class Node {
        public:
            Node() {}
            Node(string newName) {name = newName;}
            const string getData() const {return name;}
            void setName(string& n_name) {name = n_name;}
            void setStatus(bool yn) {visited = yn;}
            void attachNewNode(Node* newNode, int direction) {attachedNodes[direction] = newNode;}
            Node* getAttachedNode(int direction) const {return attachedNodes[direction];}
            bool getVisited() {return visited;}

        private:
            string name;
            Node* attachedNodes[4];
            bool visited;
    };

#endif // NODE_H_INCLUDED
