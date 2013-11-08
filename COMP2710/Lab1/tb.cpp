#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Friendlist;
class System;
class WallPage;
class Menu;
class User;

class FriendList {

	private:
		string friends;
	public:
		FriendList();
		void add_friend(System& s, User u);
		bool isFriend(User user);
		string get_friends();
};
class User {

	private:
		string name;
		FriendList friends;
		int num_msgs;
		int num_tweets;

	public:
		User();
		User(string name);
		string get_name();
		void set_name(string uname);
		int get_num_msgs();
		int get_num_tweets();
		void set_num_msgs(int x);
		void set_num_tweets(int y);
		string get_friends();
};


class System {

	private:
		string message_buffer;
		User users[10];
		int count;
		User current_user;
		int message_count;
		int tweet_count;

	public:
		System();
		void create_user(string name);
		User get_current_user();
		void post_message();
		void post_tweet();
		static void display_wall(System& s, User user);
        bool isUser(string name);
		bool isGood(string name);
		string get_message_buffer();
		void switch_user(string user);
		static void add(System& s);
        int get_count();
		int get_msg_count();
        int get_tweet_count();
};


class WallPage {

	private:
		string wall;
		User client;

	public:
		WallPage(User user);

		string get_wall();


};

class Menu {
	private:
		string menu;
		char choice;
	public:
		void check_input();
		void display_menu();
		void evaluate(System& sys);
		char get_choice();

};


int main() {
	System sys;
	Menu menu;
	string greet = "The TigerBook Messaging System!";
	string spaces(8, ' ');
	string bars((2 * spaces.length()) + greet.length() + 2, '=');
	cout << "\t" <<bars << "\n" << "\t|" << spaces << greet << spaces << "|" << "\n" << "\t" << bars << endl;
	menu.evaluate(sys);
	return 0;
}

User::User(){}

User::User(string uname) {
	name = uname;
	num_msgs = 0;
	num_tweets =0;
}

string User::get_name() {
	return name;
}

void User::set_name(string uname) {
	name = uname;
}
int User::get_num_msgs() {
    return num_msgs;
}

int User::get_num_tweets() {
    return num_tweets;
}

void User::set_num_msgs(int x) {
    num_msgs = x;
}

void User::set_num_tweets(int y) {
    num_tweets = y;

}

string User::get_friends() {
    return friends.get_friends();
}
System::System() {
    count = 0;
	message_count = 0;
	tweet_count = 0;
}

int System::get_msg_count() {
    return message_count;
}
int System::get_tweet_count() {
    return tweet_count;
}
int System::get_count() {
    return count;
}
string System::get_message_buffer() {
	return message_buffer;
}
bool System::isGood(string name) {
	return ((name.at(0) > 65 && name.at(0) < 90) || (name.at(0) > 97 && name.at(0) < 122));

}

FriendList::FriendList() {}

string FriendList::get_friends() {
	return friends;
}
bool FriendList::isFriend(User user) {
    size_t found = get_friends().find(user.get_name());
	if (found == std::string::npos) {
        return false;
     }

    else return true;
}

void FriendList::add_friend(System& s, User u) {

    if (u.get_name() == s.get_current_user().get_name()) {

        cout << "You cannot add yourself!" << endl;
        return;
    }


	if (s.isUser(u.get_name())) {
            if (isFriend(u.get_name()) == false) {
                friends = friends.append(u.get_name() + "\n");
                cout << "Friend added!\n" << endl;
            }

            else {
                cout << "Friend has already been added.\n" << endl;
        }
	}

	else {

        cout << "User does not exist.\n";
	}
}
bool System::isUser(string name) {
	for (int i = 0; i < 10; i++) { //10 IS MAX USER NUMBER
		if (users[i].get_name() == name) {
			return true;
		}
	}
	return false;
}

void System::create_user(string name) {
	User user;
	if (isGood(name)) {
		if (isUser(name)) {
			cout << "User already exists." << endl;
		}
		else {

			user = User(name);
			users[count] = user;
			count++;
			current_user = user;
			message_buffer = message_buffer.insert(0, "{[" + current_user.get_name() + "]}");
			if (count == 9) {
				cout << "Maximum number of users reached. Do not enter more." << endl;
			}
			string welcome = "Welcome to TigerBook, " + current_user.get_name() + "!";
			string spaces(8, ' ');
			string bars((2 * spaces.length()) + welcome.length() + 2, '=');
			cout << "\t" << bars << "\n" << "\t|" << spaces << welcome << spaces << "|" << "\n" << "\t" << bars << endl;
		}
	}
}

void System::switch_user(string user) {
	bool found = false;
	int j;
	for (j = 0; j < 10; j++) {
		if (users[j].get_name() == user) {
			found = true;
			break;
		}
	}

	if (found == true) {
		current_user = users[j];
		string welcome = "Welcome back to TigerBook, " + user + "!";
		string spaces(8, ' ');
		string bars((2 * spaces.length()) + welcome.length() + 2, '=');
		cout << "\t" <<bars << "\n" << "\t|" << spaces << welcome << spaces << "|" << "\n" << "\t" <<bars <<  endl;

	}
	else {
		cout << "User does not exist\n" << endl;
	}
}

void System::post_message() {
	string message;
	cout << "Enter a message: ";
	while(true) {
		getline(cin, message);
		if (message == "!!") {
			message = "\n";
			break;
		}
		else {
            message_buffer = message_buffer.insert(message_buffer.find("{[" + current_user.get_name() + "]}") +
                                current_user.get_name().length() + 4, "\n" + message);
            current_user.set_num_msgs(current_user.get_num_msgs() + 1);
            message_count++;
            cout << "Message has been posted!\n" << endl;
		}



	}

}

void System::post_tweet() {
	string tweet;
	cout << "Enter tweet message: ";
	while (true) {
		getline(cin, tweet);
		if (tweet == "!!") {
			tweet = "\n";
			break;
		}
		else {

			if (message_buffer.find(current_user.get_name() + "::tweet")) {
				message_buffer.insert(message_buffer.find(current_user.get_name() + "::tweet") + current_user.get_name().length() + 7,
					tweet);
			}
			else {
				message_buffer.insert(0, "{[" + current_user.get_name() + "::tweet]}" + tweet);
				current_user.set_num_tweets(current_user.get_num_tweets() + 1);
				tweet_count++;

				cout << "Tweet has been posted!" << endl;

			}

		}

	}
}

void System::display_wall(System& s, User user) {
    string output, show;
	string cBuffer = s.get_message_buffer();
	int m_count = 0;
	int t_count = 0;
	string minOut;

	if (user.get_num_msgs() == 0) {
        output.append("No messages have been posted.\n\n");
	}
	else {
        int msgIdx = cBuffer.find("{[" + user.get_name() + "]}") + 4 + user.get_name().length(); //Beginning of the first message. 4 because of the brackets
        string message = cBuffer.substr(msgIdx, cBuffer.find("{[", msgIdx));
        while (!message.empty()) { //loop to parse the message to get individual messages from the user. Then adds to the output string
            string sub_message = message.substr(message.rfind("\n", - 1));
            if (m_count == 2) {
                minOut = output;
                output.clear();
            }

        output.append(sub_message); //add the sub message to the output
        message.erase(message.rfind("\n", - 1)); //erase the sub_message because it is not needed anymore
        m_count++;
        }
        cout << minOut << "\n" << endl;
        cout << "Display more messages? yes/no: ";
        cin >> show;
        cin.ignore(256, 'n');
        if (show == "yes") {
            cout << output;
        }
	}
	if (user.get_num_tweets() == 0) {
        output.append("No tweets have been posted.\n\n");
	}
	else {
        int tweetIdx = cBuffer.find("{[" + user.get_name() + "::tweet" + "]}") + user.get_name().length() + 11; //Beginning of the tweet. 11 because the length of ::tweet plus brackets
        string tweet = cBuffer.substr(tweetIdx, cBuffer.find("{[", tweetIdx));
        while (!tweet.empty()) { //loop to parse the message to get individual messages from the user. Then adds to the output string
            string sub_tweet = tweet.substr(tweet.rfind("\n", - 1));
            if (t_count == 2) {
                string mOut = output;
            }

        output.append(sub_tweet); //add the sub message to the output
        tweet.erase(tweet.rfind("\n", - 1)); //erase the sub_message because it is not needed anymore
        }


	}



	cout << output << endl;
}

User System::get_current_user() {
	return current_user;
}

WallPage::WallPage(User user) {
	client = user;
	wall = "";

}

string WallPage::get_wall() {
	return wall;
}


void Menu::display_menu() {

	cout << "1) Create new user\n"
	     << "2) Post a message\n"
	     << "3) Tweet a message\n"
	     << "4) Display Wall Page\n"
	     << "5) Display Home Page\n"
	     << "6) Add a Friend\n"
	     << "7) Switch User\n"
	     << "8) Exit Program" << endl;

	cout << "\n\tPlease choose an option: ";
	cin >> choice;
	cin.ignore(256, '\n');
}

void Menu::check_input() {

	if (choice < 0x31 || choice > 0x39) {
		cout << "Option invalid." << endl;
	}
}
char Menu::get_choice() {
	return choice;
}
void Menu::evaluate(System& s) {
    FriendList list;
	while (true) {
		display_menu();
		check_input();
        if (s.get_current_user().get_name().length() == 0) {
                if (choice != '1' && choice != '8'){
                    cout << "You must create a user!\n" << endl;
                    continue;
                }
        }
		switch (choice) {
			case '1':
			{
				string toCreate;
				cout << "Please enter user name: ";
				getline(cin, toCreate);
				s.create_user(toCreate);
				break;
			}
			case '2':
			{

				s.post_message();
				break;
			}
			case '3':
				s.post_tweet();
				break;
			case '4':
				System::display_wall(s, s.get_current_user());
				break;
			case '5':
				//****display_home(sys.get_current_user());
				break;
			case '6':
			{
				string newFriend;
				cout << "Enter friend's name: ";
				getline(cin, newFriend);
				list.add_friend(s, newFriend);
				break;
			}
			case '7':
			{
				string newUser;
				cout << "Enter user's name: ";
				getline(cin, newUser);
				s.switch_user(newUser);
				break;
			}
			case '8':
			{
				string bye = "Thank you for using TigerBook" ;
				string spaces(8, ' ');
				string bars((2 * spaces.length()) + bye.length() + 2, '=');
				cout << "\t" <<bars << "\n" << "\t|" << spaces << bye << spaces << "|" << "\n" << "\t" <<bars <<  endl;
				goto exit;
			}
			default:
				cout << "Please enter a valid choice" << endl;
		}

	}
	exit:;
}
