#include <iostream>
#include <string>
#include "node.h"
#include "system.h"
#include <ctime>
#include <cstdlib>

using std::string;

int main() {
    srand((unsigned)time(NULL));
    System s;
    s.display_menu();
    return 0;
}
