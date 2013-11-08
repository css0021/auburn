/**
Author: Chris Strong
Email: css0021@auburn.edu
Final version last modified: 10/27/13

This program, Distributed TigerBook, offers a
way to communicate with friends over a shared
network file system. There is one computer per user
so multiple users can connect to the system and
communicate and connect.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

class System;
class Menu;

class User {

private:
    string u_name;
    string wallPage;
    string homePage;
    string friendList;
public:
    User();
    User(string name);//done
    string get_name();//done
    void  wall(System s);
    void home(System s);
    string read_friends();
    string read_msgs();
    string read_tweets();
};

class System {

private:
    User current_user;
    string user_list;
    string msg_to_file;
    string c_contents;
    int m_count;
    int t_count;
    int u_time;


public:
    System();
    void open_user(); //done
    void write_msg(string message); //done
    void write_tweet(string tweet);//done
    void add_friend(string buddy);//done
    void setTime(int time); //done
    void set_msg_to_file(string change); //done
    void read_messages(const char* fname);
    bool isUser(string name); //done
    bool isFriend(string name); //done
    bool fileExist(string fileName); //done
    int getLength(string name); //done
    static const int MSG_DISPLAY = 2;
    int getTime(); //done
    string get_msg_to_file(); //done
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




User::User() {}

User::User(string name) {
    u_name = name;
}



string User::get_name() {
    return u_name;
}


System::System() {
    m_count = 0;
    t_count = 0;
    string tmp;
    ifstream time("time.txt");
    time >> tmp;
    if (tmp == string()) {
        ofstream otime("time.txt");
        otime << 0;
        time.close();
    } else {
        u_time = atoi(tmp.c_str());
        time.close();
    }
}

User System::get_current_user() {
    return current_user;
}

inline int System::getTime() {
    ifstream gtime("time.txt");
    gtime >> u_time;
    gtime.close();
    return u_time;
}

inline void System::setTime(int time) {
    ofstream oTime("time.txt", ios::trunc);
    oTime << time;
    oTime.close();
}
inline int System::getLength(string name) {
    ifstream ins(name.c_str());
    ins.seekg(0, ins.end);
    int length = ins.tellg();
    ins.close();
    return length;
}

inline string System::get_msg_to_file() {
    return msg_to_file;
}

inline void System::set_msg_to_file(string change) {
    msg_to_file = change;
}
inline bool System::fileExist(string fileName) {
    ifstream test((fileName + ".txt").c_str());
    return test.fail();
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

string User::read_friends() {
    string name;
    ifstream friendstream((this->get_name() + "_friends.txt").c_str());
    while (!friendstream.eof()) {
        getline(friendstream, name);
        friendList += name;
    }

    return friendList;

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
            } else {


                ofstream outStream((name + ".txt").c_str(), ios::app);3
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
                } else {
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
    ofstream outStream;
    ifstream instream;
    string u_list;
    instream.open("user_list.txt");
    getline(instream, u_list);
    instream.close();
    if (!isUser(current_user.get_name())) {
        cout << "User not found!" << endl;
    } else {
        outStream.open((current_user.get_name() + ".txt").c_str(), ios::app);
        if (outStream.fail()) cout << "File could not be opened for writing.\n" << endl;
        if (getLength((current_user.get_name() + ".txt")) == 0) {
            if (msg_to_file.size() == 0) {
                int t = getTime();
                stringstream s;
                s << t;
                string time = s.rdbuf()->str();
                msg_to_file.insert(0, "{<" + time + ">}" + message);
                t++;
                setTime(t);
            }

            else {
                if (message != "!!") {
                    msg_to_file.append("\n" + message);
                } else {

                    ofstream ostream((current_user.get_name() + ".txt").c_str());
                    ostream << msg_to_file;
                    ostream.close();
                }
            }
        } else {
            if (msg_to_file.size() == 0) {
                int t = getTime();
                stringstream s;
                s << t;
                string time = s.rdbuf()->str();
                msg_to_file.insert(0, "{<" + time + ">}" + message);
                t++;
                setTime(t);
            }

            else {
                if (message != "!!") {
                    msg_to_file.append("\n" + message);
                } else {
                    ifstream msgstream((current_user.get_name() + ".txt").c_str());
                    stringstream currentc;
                    currentc << msgstream.rdbuf();
                    c_contents = currentc.rdbuf()->str();
                    c_contents.insert(0, msg_to_file);
                    msgstream.close();
                    ofstream tofile((current_user.get_name() + ".txt").c_str(), ios::trunc);
                    tofile << c_contents;
                    tofile.close();
                }

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
    if (!isUser(current_user.get_name())) {
        cout << "User not found!" << endl;
    } else {
        outStream.open("tweet.txt", ios::app);
        if (outStream.fail()) cout << "File could not be opened for writing.\n" << endl;
        if (getLength("tweet.txt") == 0) {
            if (msg_to_file.size() == 0) {
                int t = getTime();
                stringstream s;
                s << t;
                string time = s.rdbuf()->str();
                msg_to_file.insert(0, "{<" + time + ">}" + "{[" + current_user.get_name() + "]}" + tweet);
                t++;
                setTime(t);
            }

            else {
                if (tweet != "!!") {
                    msg_to_file.append("\n" + tweet);
                } else {

                    ofstream ostream("tweet.txt");
                    ostream << msg_to_file;
                    ostream.close();
                }
            }
        } else {
            if (msg_to_file.size() == 0) {
                int t = getTime();
                stringstream s;
                s << t;
                string time = s.rdbuf()->str();
                msg_to_file.insert(0, "{<" + time + ">}" + "{[" + current_user.get_name() + "]}" + tweet);
                t++;
                setTime(t);
            }

            else {
                if (tweet != "!!") {
                    msg_to_file.append("\n" + tweet);
                } else {
                    ifstream tweetstream("tweet.txt");
                    stringstream currentc;
                    currentc << tweetstream.rdbuf();
                    c_contents = currentc.rdbuf()->str();
                    c_contents.insert(0, msg_to_file);
                    tweetstream.close();
                    ofstream tofile("tweet.txt", ios::trunc);
                    tofile << c_contents;
                    tofile.close();
                }

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
        } else {
            ofstream outstream((current_user.get_name() + "_friends.txt").c_str(), ios::app);
            if (outstream.fail()) {
                cout << "File opening has failed.\n" << endl;
                return;
            }

            outstream << buddy + "|";
            outstream.close();
            string greeting = "Added " + buddy + " to Friend's list";
            string spaces(8, ' ');
            string bars((2 * spaces.length()) + greeting.length() + 2, '=');
            cout << "\t" << bars << "\n" << "\t|" << spaces << greeting << spaces << "|" << "\n" << "\t" << bars << endl;
        }
    } else {
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
    input = tolower(option[0]);
    if (check_input(input) == false) {
        cout << "Please enter a valid option.\n" << endl;
    }
    for (;;) {
        switch(input) {

        case 'f': {
            string aFriend;
            cout << "\nEnter name: ";
            getline(cin, aFriend);
            s.add_friend(aFriend);

            break;
        }
        case 'p': {
            string message;
            cout << "\nEnter message: ";
            while (message != "!!") {
                getline(cin, message);
                if (message == "!!") {
                    s.write_msg(message);
                    s.set_msg_to_file(string());
                    break;
                }
                s.write_msg(message);
            }
            string greeting = "Message posted!";
            string spaces(8, ' ');
            string bars((2 * spaces.length()) + greeting.length() + 2, '=');
            cout << "\t" << bars << "\n" << "\t|" << spaces << greeting << spaces << "|" << "\n" << "\t" << bars << endl;
            break;
        }
        case 't': {
            string tweet;
            ofstream gen_tweet("tweet.txt", ios::app);
            gen_tweet.close();
            cout << "\nEnter tweet: ";
            while (tweet != "!!") {
                getline(cin, tweet);
                if (tweet == "!!") {
                    s.write_tweet(tweet);
                    s.set_msg_to_file(string());
                    break;

                }
                s.write_tweet(tweet);
            }

            string greeting = "Tweet posted!";
            string spaces(8, ' ');
            string bars((2 * spaces.length()) + greeting.length() + 2, '=');
            cout << "\t" << bars << "\n" << "\t|" << spaces << greeting << spaces << "|" << "\n" << "\t" << bars << endl;
            break;
        }
        case 'w': {
            User u(s.get_current_user());
            u.wall(s);

            break;
        }
        case 'h': {
            User u(s.get_current_user());
            u.home(s);
            break;
        }
        case 'q': {
            string greeting = "Thank you for using Distributed TigerBook!";
            string spaces(8, ' ');
            string bars((2 * spaces.length()) + greeting.length() + 2, '=');
            cout << "\t" << bars << "\n" << "\t|" << spaces << greeting << spaces << "|" << "\n" << "\t" << bars << endl;
            exit(EXIT_SUCCESS);

        }
        }
        break;
    }

}


void User::wall(System s) {
    string greeting = s.get_current_user().get_name() + "'s Wall Page";
    string spaces(8, ' ');
    string bars((2 * spaces.length()) + greeting.length() + 2, '=');
    cout << "\t" << bars << "\n" << "\t|" << spaces << greeting << spaces << "|" << "\n" << "\t" << bars << endl;
    vector<string> messages;
    string file = (s.get_current_user().get_name() + ".txt");
    if (s.getLength(file) == 0) {
        cout << "No messages have been posted.\n";
    }
    string msgbufr, tmp;

    if (s.getLength(file) != 0) {
        ifstream msgstream(file.c_str());
        stringstream bufrstream;
        bufrstream << msgstream.rdbuf();
        msgstream.close();
        string time, msg, msgbufr;
        int check = 0;
        msgbufr = bufrstream.rdbuf()->str();
        bufrstream.str(msgbufr);
        while (!bufrstream.eof()) {
            getline(bufrstream, time, '>');
            check == 0 ? time.erase(0,2) : time.erase(0,1);
            if (time.length() < 2) {
                time.insert(0,"0");
            }
            time.append("!");
            getline(bufrstream, msg, '{');
            msg.erase(0, 1);
            messages.push_back(time + msg);
            check++;
        }

        check = 0;

        ifstream checkf("tweet.txt");
        if (checkf.fail() == true) {
            cout << "Opening of tweet file failed. Maybe no tweets have been posted?";
        } else {
            if (s.getLength("tweet.txt") == 0) {
                cout << "No tweets have been posted.\n";

            } else {
                ifstream tweetstream("tweet.txt");
                stringstream tbuffer;
                tbuffer << tweetstream.rdbuf();
                string tweet = tbuffer.rdbuf()->str();
                tweetstream.close();
                tbuffer.str(tweet);
                string name;
                while (!tbuffer.eof()) {
                    getline(tbuffer, time, '>');
                    check == 0 ? time.erase(0,2) : time.erase(0,1);
                    if (time.length() < 2) {
                        time.insert(0,"0");
                    }
                    getline (tbuffer, name, ']');
                    if (name.find(s.get_current_user().get_name()) != std::string::npos) {
                        time.append("!");
                        getline(tbuffer, tweet, '{');
                        tweet.erase(0,1);
                        messages.push_back(time + tweet);

                    }
                    check++;


                }
                sort(messages.begin(), messages.end(), greater<string>());
                int times_trav = 0;
                string choice;
                for (std::vector<string>::iterator msg_traverse = messages.begin(); msg_traverse != messages.end(); ++msg_traverse) {
                    if (messages.size() <= System::MSG_DISPLAY) {
                        string to_wall = *msg_traverse;
                        int prd = to_wall.find(".");
                        to_wall.erase(0, prd+1);
                        cout << to_wall << "\n\n";
                        continue;
                    } else {

                    }
                    if (times_trav == System::MSG_DISPLAY) {
                        cout << "\n\n\t\tDisplay more messages?: (yes/no): ";
                        getline(cin, choice);
                        if (choice == "no") {
                            break;
                        } else cout << "\n";


                    }
                    string to_wall = *msg_traverse;
                    int prd = to_wall.find(".");
                    to_wall.erase(0, prd+1);
                    cout << to_wall << "\n\n";
                    times_trav++;
                }
                string greeting = "End of " + s.get_current_user().get_name() + "'s Wall Page";
                string spaces(8, ' ');
                string bars((2 * spaces.length()) + greeting.length() + 2, '=');
                cout << "\t" << bars << "\n" << "\t|" << spaces << greeting << spaces << "|" << "\n" << "\t" << bars << "\n" << endl;

            }

        }
    }

}

void User::home(System s) {
    string greeting = s.get_current_user().get_name() + "'s Home Page";
    string spaces(8, ' ');
    string bars((2 * spaces.length()) + greeting.length() + 2, '=');
    cout << "\t" << bars << "\n" << "\t|" << spaces << greeting << spaces << "|" << "\n" << "\t" << bars << endl;
    vector<string> messages;
    string file = (s.get_current_user().get_name() + ".txt");
    if (s.getLength(file) == 0) {
        cout << "No messages have been posted.\n";
    }
    string msgbufr, tmp;

    string friends = read_friends();
    stringstream friendparse (friends);
    string name;
    int check = 0;
    //get friend's posts
    while (!friendparse.eof()) {
        getline(friendparse, name, '|');
        string filename = (name + ".txt");
        ifstream read_msg(filename.c_str());
        if (s.getLength(filename) == 0) {
            cout << "No messages from " + name;
        }
        stringstream tmp;
        tmp << read_msg.rdbuf();
        string mesgs = tmp.rdbuf()->str();
        read_msg.close();
        stringstream bufrstream (mesgs);
        string time, msg;

        while (!bufrstream.eof()) {
            getline(bufrstream, time, '>');
            if (time == "") {
                continue;
            }
            check == 0 ? time.erase(0,2) : time.erase(0,1);
            if (time.length() < 2) {
                time.insert(0,"0");
            }
            time.append("!");
            getline(bufrstream, msg, '{');
            msg.erase(0, 1);
            messages.push_back(time + name + ": \n"  + msg);
            check++;
        }
        check = 0;
    }



    //get user's posts
    if (s.getLength(file) != 0) {
        ifstream msgstream(file.c_str());
        stringstream bufrstream;
        bufrstream << msgstream.rdbuf();
        msgstream.close();
        string time, msg, msgbufr;
        int check = 0;
        msgbufr = bufrstream.rdbuf()->str();
        bufrstream.str(msgbufr);
        while (!bufrstream.eof()) {
            getline(bufrstream, time, '>');
            if (time == "") {
                continue;
            }
            check == 0 ? time.erase(0,2) : time.erase(0,1);
            if (time.length() < 2) {
                time.insert(0,"0");
            }
            time.append("!");
            getline(bufrstream, msg, '{');
            msg.erase(0, 1);
            messages.push_back(time + s.get_current_user().get_name() + ": \n" + msg);
            check++;
        }
    }



    //add the tweets to the vector
    ifstream checkf("tweet.txt");
    if (checkf.fail() == true) {
        cout << "Opening of tweet file failed. Maybe no tweets have been posted?";
    } else {
        if (s.getLength("tweet.txt") == 0) {
            cout << "No tweets have been posted.\n";

        } else {
            ifstream tweetstream("tweet.txt");
            stringstream tbuffer;
            tbuffer << tweetstream.rdbuf();
            string tweet = tbuffer.rdbuf()->str();
            tweetstream.close();
            tbuffer.str(tweet);
            string twittername;
            string time;
            int check = 0;
            while (!tbuffer.eof()) {
                getline(tbuffer, time, '>');
                if (time == "") {
                    continue;
                }
                check == 0 ? time.erase(0,2) : time.erase(0,1);
                if (time.length() < 2) {
                time.insert(0,"0");
            }
                getline(tbuffer, twittername, ']');
                twittername.erase(0, twittername.find("[")+1);
                time.append("!");
                getline(tbuffer, tweet, '{');
                tweet.erase(0,1);
                messages.push_back(time + twittername + ": \n" + tweet);        //fix it to where it finds the name rather than


                check++;
            }
            //sort the messages by string, in reverse order

        }

    }

    std::sort(messages.begin(), messages.end(), greater<string>());
    //iterate through and output the messages.
    int times_trav = 0;
    string choice;
    for (std::vector<string>::iterator msg_traverse = messages.begin(); msg_traverse != messages.end(); ++msg_traverse) {
        if (messages.size() <= System::MSG_DISPLAY) {
            string to_wall = *msg_traverse; //dereference the iterator
            int prd = to_wall.find("!");
            to_wall.erase(0, prd+1);
            cout << to_wall << "\n\n";
            continue;
        } else {

        }
        if (times_trav == System::MSG_DISPLAY) {
            cout << "\n\n\t\tDisplay more messages?: (yes/no): ";
            getline(cin, choice);
            if (choice == "no") {
                break;
            } else cout << "\n";
        }
        string to_wall = *msg_traverse; //dereference the iterator
        int prd = to_wall.find("!");
        to_wall.erase(0, prd+1);
        cout << to_wall << "\n\n";
        times_trav++;
    }
    string ending = "End of " + s.get_current_user().get_name() + "'s Wall Page";
    string space(8, ' ');
    string bar((2 * space.length()) + ending.length() + 2, '=');
    cout << "\t" << bar << "\n" << "\t|" << space << ending << space << "|" << "\n" << "\t" << bar << "\n" << endl;
}


int main() {

    System s;
    s.open_user();
    Menu menu;
    for (;;) {
        menu.evaluate(s);
    }

}
