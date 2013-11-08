#include <algorithm>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main() {

    string a("05");
    string b("01");
    //string c("ab");

    vector<string> msg;
    msg.push_back(b);
    //msg.push_back(c);
    msg.push_back(a);
    sort(msg.begin(), msg.end(), greater<string>());
    for (std::vector<string>::iterator i = msg.begin(); i != msg.end(); i++) {
        cout << ' ' << *i << endl;
    }

    return 0;
}
