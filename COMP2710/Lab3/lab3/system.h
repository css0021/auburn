#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED
#include <vector>
#include "node.h"
#include <string>


using std::string;

class System {

    public:
        void loadNodes(const char* fileName);
        string backtrack();
        void advance(int direction);
        void display_output();
    private:
        std::vector<Node> nVector;

};

#endif // SYSTEM_H_INCLUDED
