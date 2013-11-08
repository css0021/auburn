#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

class System;
class Menu;

class User {

    private:
        string u_name;
        string wallPage;
        string homePage;
        string FriendList;
    public:
        User();
        User(string name);//done
        string get_name();//done
        void  wall(System s);
        void home(System s);
        void read_friends();
        void read_t_m();
};

class System {

    private:
        User current_user;
        string user_list;
        int m_count;
        int t_count;
        int u_time;

    public:
        System();
        void incrementTime();
        void open_user(); //done
        void write_msg(string message); //done
        void write_tweet(string tweet);//done
        void add_friend(string buddy);//done
        bool isUser(string name); //done
        bool isFriend(string name); //done
        bool fileExist(const char* fileName); //done
        int getSize(string name);
        int getTime();
        User get_current_user();//done


};

class Menu {
    private:
        string menu;
        char choice;

    public:
        bool check_input(char choice);
        void display_menu();
        void evaluate(System s);

};




User::User(){}

User::User(string name) {
    u_name = name;
}



string User::get_name(){
    return u_name;
}



System::System(){
    m_count = 0;
    t_count = 0;
    if (!fileExist("time.txt")) {
        ofstream outstream("time.txt");
        outstream << 0;
        u_time = 0;
        outstream.close();
    }
    else {
        string hold;
        ifstream start("time.txt");
        getline(start, hold);
        u_time = atoi(hold.c_str());
    }
}

User System::get_current_user() {
    return current_user;
}

int System::getTime() {
    return u_time;
}
int System::getSize(string name) {
    ifstream ins(name.c_str());
    ins.seekg(0, ins.end);
    int length = ins.tellg();
    ins.close();
    return length;
}
bool System::fileExist(const char* fileName) {
    ifstream testFile(fileName);
    return testFile;

}
bool System::isUser(string name) {
    ifstream instream("user_list.txt");
    if (instream.fail()) {
        cout << "File opening failed.\n" << endl;
        return true;
    }
    string users;
    getline(instream, users);
    instream.close();
    return (users.find(name) != std::string::npos);
}

bool System::isFriend(string name) {
    ifstream instream((current_user.get_name() + "_friends.txt").c_str());
    if (instream.fail()) {
        cout << "File opening failed.\n" << endl;
    }
    string friends;
    getline(instream, friends);
    instream.close();
    return (friends.find(name) != std::string::npos);

}

void System::incrementTime() {
    u_time++;
    ofstream oTime("time.txt", ios::trunc);
    oTime << u_time;
}
void System::open_user() {
    string greet = "The Distributed TigerBook Messaging System!";
	string spaces(8, ' ');
	string bars((2 * spaces.length()) + greet.length() + 2, '=');
	cout << "\t" <<bars << "\n" << "\t|" << spaces << greet << spaces << "|" << "\n" << "\t" << bars << endl;
	string name;
    bool success = false;
    while (success == false) {
        cout << "Enter user: ";
        getline(cin, name);
        if (name.at(0) >= 0x41 && name.at(0) <= 0x7A) {
            if (name.at(0) > 0x5A && name.at(0) < 0x61) {
                cout << "Please enter a valid username.\n" << endl;
                continue;
            }
            else {


                ofstream outStream((name + ".txt").c_str(), ios::app);
                ofstream friendStream((name + "_friends.txt").c_str(), ios::app);
                friendStream.close();
                User user(name);
                current_user = user;
                outStream.close();
                string users;
                ifstream is("user_list.txt");
                getline(is, users);
                is.close();
                if (users.find(name) == std::string::npos) {
                    outStream.open("user_list.txt", ios::app);
                    outStream << name << "|";
                    string greeting = "Welcome to Distributed TigerBook, " + current_user.get_name() + "!";
                    string spaces(8, ' ');
                    string bars((2 * spaces.length()) + greeting.length() + 2, '=');
                    cout << "\t" <<bars << "\n" << "\t|" << spaces << greeting << spaces << "|" << "\n" << "\t" << bars << endl;
                    success = true;
                    outStream.close();
                }
                else {
                    outStream.close();
                    string greeting = "Welcome to Distributed TigerBook, " + current_user.get_name() + "!";
                    string spaces(8, ' ');
                    string bars((2 * spaces.length()) + greeting.length() + 2, '=');
                    cout << "\t" <<bars << "\n" << "\t|" << spaces << greeting << spaces << "|" << "\n" << "\t" << bars << endl;
                    success = true;

                }
            }

        }

        else {
            cout << "Please enter a valid username.\n" << endl;
        }
    }
}

void System::write_msg(string message) {
    ofstream outStream, tStream;
    ifstream instream;
    string u_list;
    instream.open("user_list.txt");
    getline(instream, u_list);
    instream.close();
    if (u_list.find(current_user.get_name()) == std::string::npos) {
        cout << "User not found!" << endl;
    }
    else {
        outStream.open((current_user.get_name() + ".txt").c_str(), ios::app);
        tStream.open("time.txt");
        if (outStream.fail()) cout << "File could not be opened for writing.\n" << endl;

        else {
            if (getSize((current_user.get_name() + ".txt").c_str()) == 0) {
                if (message == "!!") {
                    cout << "You must enter a message first." << endl;
                     return;
                }
                outStream << "{<" << getTime() << ">}" << message << "\n";
                outStream.close();
                m_count++;
                incrementTime();
            }
            else {
                string buf, tmp, new_msg;
                outStream.close();
                instream.open((current_user.get_name() + ".txt").c_str());
                while(!instream.eof()) {
                    getline(instream, tmp);
                    buf += "\n" + tmp;
                }
                instream.close();
                new_msg = new_msg.insert(0, message + buf);
                outStream.open((current_user.get_name() +  ".txt").c_str(), ios::trunc  );
                outStream << "{<" << getTime() << ">}" << new_msg << endl;
                outStream.close();
                m_count++;
                incrementTime();

            }
        }

    }
}

void System::write_tweet(string tweet) {
    ofstream outStream;
    ifstream instream;
    string u_list;
    instream.open("user_list.txt");
    getline(instream, u_list);
    instream.close();
    if (u_list.find(current_user.get_name()) == std::string::npos) {
        cout << "User not found!" << endl;
    }
    else {
        outStream.open("tweet.txt", ios::app);
        if (outStream.fail()) cout << "File could not be opened for writing.\n" << endl;

        else {
            if (getSize("tweet.txt") == 0) {
                if (tweet == "!!") {
                    cout << "You must enter a message first." << endl;
                    return;
                }
                outStream << "{<" << getTime() << ">}" << "{[" << current_user.get_name() << "]}" << tweet << "\n";
                outStream.close();
                t_count++;
                incrementTime();
            }
            else {
                instream.open((current_user.get_name() + ".txt").c_str());
                string buf, tmp, new_msg;
                while(!instream.eof()) {
                    getline(instream, tmp);
                    buf += "\n" + tmp;
                }
                instream.close();
                new_msg = new_msg.insert(0, tweet + buf);
                outStream.open((current_user.get_name() +  ".txt").c_str(), ios::trunc);
                outStream << "{<" << getTime() << ">}" << "{[" << current_user.get_name() << "]}" << new_msg << endl;
                outStream.close();
                t_count++;
                incrementTime();


            }
        }

    }
}
void System::add_friend(string buddy) {
    if(current_user.get_name() == "") {
        cout << "You must create a user first!\n" << endl;
        return;
    }
    if (isUser(buddy)) {
        if (isFriend(buddy)) {
            cout << "This user is already on your friends list.\n" << endl;
            return;
        }
        else {
            ofstream outstream((current_user.get_name() + "_friends.txt").c_str(), ios::app);
            if (outstream.fail()) {
                cout << "File opening has failed.\n" << endl;
                return;
            }

            outstream << buddy + "|";
            outstream.close();
            cout << "Friend added!\n" << endl;
        }
    }
    else {
        cout << "User does not exist.\n" << endl;
    }

}

void Menu::display_menu() {
    cout << "Add friend (f), Post (p), Tweet (t), Wall (w), Home (h), Quit (q)\n" << endl;
}

bool Menu::check_input(char choice) {

    if (choice != 'f' && choice != 'p' && choice != 't' && choice != 'w' && choice != 'h' && choice != 'q') {
        return false;
    }

    return true;

}

void Menu::evaluate(System s) {
    display_menu();
    string option;
    char input;
    cout << "Enter option: ";
    getline(cin, option);
    input = option[0];
    if (check_input(input) == false) {
        cout << "Please enter a valid option.\n" << endl;
    }
    for (;;) {
        switch(input) {

            case 'f':
                {
                string aFriend;
                cout << "Enter name: ";
                getline(cin, aFriend);
                s.add_friend(aFriend);
                break;
                }
            case 'p':
                {
                string message;
                cout << "Enter message: ";
                while (message != "!!"){
                    getline(cin, message);
                    if (message == "!!") {
                        return;
                    }
                    s.write_msg(message);
                }
                cout << "\nMessage posted!\n" << endl;
                break;
                }
            case 't':
                {
                string tweet;
                ofstream gen_tweet("tweet.txt");
                gen_tweet.close();
                cout << "Enter tweet: ";
                while (tweet != "!!") {
                    getline(cin, tweet);
                    if (tweet == "!!") {
                        return;
                    }
                    s.write_tweet(tweet);
                }

                cout << "\nTweet posted!\n" << endl;
            }
                break;
            case 'w':
                {
		    User u(s.get_current_user());
		    u.wall(s);
                    //cout << "Still working." << endl;
                    break;
                }
            case 'h':
                {
                    cout << "Still working.\n" << endl;
                    break;
                }
            case 'q':
                {
                    exit(EXIT_SUCCESS);
                }
        }
        break;
    }

}

void User::wall(System s) {
    string buffer,output;
    ifstream instream;
    instream.open("time.txt");
    getline(instream, buffer);
    string user = s.get_current_user().get_name();
    string usermsgs;
    string msg;
    int latestTime = atoi(buffer.c_str()) - 1;
    instream.close();
    instream.open((user + ".txt").c_str());
    while (!instream.eof()) {
        getline(instream, msg, '\n');
        msg.erase(0,5);
	output.insert(0, msg + "\n");
    }
    ifstream tweetstream("tweets.txt");
    while (!tweetstream.eof()) {
  	


    }
    cout << output << endl << endl;
    //stringstream parseUser(usermsgs);


}

int main() {

    System s;
    s.open_user();
    Menu menu;
    for (;;) {
        menu.evaluate(s);
    }

}
