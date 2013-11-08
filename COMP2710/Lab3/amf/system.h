#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED
#include <vector>
#include "node.h"
#include <string>
#include <stack>


using std::string;

class System {

    public:
        void loadNodes(const char* fileName);
        int get_dynamic_array_pos(Node node);
        void solve();
        std::string& ltrim(std::string& s);
        std::string& rtrim(std::string& s);
        std::string& trim(std::string& s);
        void display_menu();
    private:

        std::stack<Node> nStack;
        Node* start;
        Node* dest;
        Node current_node;
        int node_c_size;
        std::vector<Node*> dynamic_array_holder;
        std::string output;
        std::string temp;

};

#endif // SYSTEM_H_INCLUDED
