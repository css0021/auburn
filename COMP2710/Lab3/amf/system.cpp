#include "system.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>



inline std::string& System::ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

inline std::string& System::rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

inline std::string& System::trim(std::string &s) {
        return ltrim(rtrim(s));
}

void System::display_menu() {
    std::string greet = "Welcome to the Automatic Maze Path Finder!";
    std::string spaces(8, ' ');
    std::string bars((2 * spaces.length()) + greet.length() + 2, '=');
    std::cout << "\t" <<bars << "\n" << "\t|" << spaces << greet << spaces << "|" << "\n" << "\t" << bars << "\n" <<std::endl;
    std::string file;
    while (file != "quit") {
        output = "";
        std::cout << "\nEnter the name of the Maze configuration file: ";
        std::getline (std::cin, file);
        if (file == "quit") {
            std::string bye = "Thank you for using the Automatic Maze Path Finder!";
            std::string spaces(8, ' ');
            std::string bars((2 * spaces.length()) + bye.length() + 2, '=');
            std::cout << "\t" <<bars << "\n" << "\t|" << spaces << bye << spaces << "|" << "\n" << "\t" << bars << "\n" <<std::endl;
            exit(EXIT_SUCCESS);
        }
        loadNodes((file + ".txt").c_str());
        solve();
    }

}

void System::loadNodes(const char* fileName) {
    std::ifstream mazefile(fileName);
    if (!mazefile.good()) {
        std::cout << "There was a problem with file opening..." << std::endl;
        display_menu();
    }
    std::string n_file, tmp, s_node_n, e_node_n, cen_node_att, node_name;
    int c_location = 0;
    int array_size;
    std::getline(mazefile, tmp);
    trim(node_name);
    array_size = atoi(tmp.c_str());
    dynamic_array_holder.reserve(array_size);
    std::getline(mazefile, s_node_n);
    trim(s_node_n);
    start = new Node(s_node_n);
    std::getline(mazefile, e_node_n);
    trim(e_node_n);
    Node* last = new Node(e_node_n);
    Node* member_ptr;
    while (!mazefile.eof()) {
        std::getline(mazefile, cen_node_att);
        std::stringstream split (cen_node_att);
        std::getline(split, node_name, ' ');
        trim(node_name);
        dynamic_array_holder.push_back(new Node(node_name));
        dynamic_array_holder.back()->setName(node_name);
        std::getline(split, node_name, ' ');
        trim(node_name);
        node_name == "*" ? member_ptr = NULL : member_ptr = new Node(node_name);
        dynamic_array_holder.back()->attachNewNode(member_ptr, 0);
        std::getline(split, node_name, ' ');
        trim(node_name);
        node_name == "*" ? member_ptr = NULL : member_ptr = new Node(node_name);
        dynamic_array_holder.back()->attachNewNode(member_ptr, 1);
        std::getline(split, node_name, ' ');
        trim(node_name);
        node_name == "*" ? member_ptr = NULL : member_ptr = new Node(node_name);
        dynamic_array_holder.back()->attachNewNode(member_ptr, 2);
        if (c_location == array_size - 1) {
            std::getline(split, node_name);
            trim(node_name);

        }
        else {
            std::getline(split, node_name, '\r');
            trim(node_name);

        }
        node_name == "*" ? member_ptr = NULL : member_ptr = new Node(node_name);
        dynamic_array_holder.back()->attachNewNode(member_ptr, 3);
    }
    member_ptr = NULL;
    dest = dynamic_array_holder.at(get_dynamic_array_pos(*last));
}

int System::get_dynamic_array_pos(Node node) {
    unsigned int i = 0;
    unsigned int loc;
    while (i < dynamic_array_holder.size()) {
        temp = dynamic_array_holder.at(i)->getData();
        if (temp == node.getData()) {
            loc = i;
            return loc;
        }
        i++;
    }
    return 0;
}

void System::solve() {


    std::cout << "The Start Node is: " << start->getData() << std::endl;
    std::cout << "The Destination Node is: " << dest->getData() << std::endl;
    std::cout << "Finding a path from the Start to Destination Node..." << std::endl;
    int count = 0;
    int k;
    Node* current_node_ptr = dynamic_array_holder.at(get_dynamic_array_pos(*start));
    nStack.push(*current_node_ptr);
    current_node_ptr->setStatus(true);

    while (!nStack.empty() && current_node_ptr != dest) {
        srand((unsigned)time(NULL));
        int POS_MOVES[4];
        for (k = 0; k < 4; k++) {
            bool is_used;
            int buf;
            do {
                buf = rand() % 4;
                is_used = true;
                for (int y = 0; y < k; y++)
                    if (buf == POS_MOVES[y]) {
                        is_used = false;
                        break;
                    }

            } while (!is_used);
            POS_MOVES[k] = buf;
         }

        if ( count < 4 && current_node_ptr->getAttachedNode(POS_MOVES[count]) != NULL) {
            Node* to_find = (current_node_ptr->getAttachedNode(POS_MOVES[count]));
            int n_location = get_dynamic_array_pos(*to_find);
            Node* temp_node = dynamic_array_holder.at(n_location);
            if (temp_node->getStatus() == false) {
                current_node_ptr = temp_node;
                current_node_ptr->setStatus(true);
                nStack.push(*current_node_ptr);
                count = 0;
            }
            else {
                count++;
            }
        }
        else {
            count++;
            if (count > 3) {
                count = 0;
                Node popped = nStack.top();
                nStack.pop();
                if (nStack.empty()) {
                    output = "No path could be found.";
                    std::cout << output << std::endl;
                    dynamic_array_holder.clear();
                    return;
                }
                current_node = nStack.top();

                popped.setStatus(false);
                current_node_ptr = dynamic_array_holder.at(get_dynamic_array_pos(current_node));

            }
            else continue;

        }

    }

    if (current_node_ptr == dest) {


        std::cout << "Congratulations! Found a path successfully." << std::endl;
        std::cout << "The path is: ";

        while (!nStack.empty()) {
            Node part_path = nStack.top();
            nStack.pop();
            output.insert(0, part_path.getData() + " ");
        }
            std::cout << output << std::endl;
            dynamic_array_holder.clear();

    }
}











