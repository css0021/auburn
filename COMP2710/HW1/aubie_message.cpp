/* Name: Chris Strong
 * Auburn UID: css0021
 * Filename: aubie_message.cpp
 * Date: 9/06/2013
 */


#include <iostream>
#include <string>

using namespace std;

int main() {
	
	string username;
	string b_user;
	string message;
	string u_message;
	string message_buffer;
	string add_user = "yes";
	//make a row of equal signs for the welcome message
	int i = 0;
	while (i < 60) {
		cout << "=";
		i++;
	}
	//welcome message
	cout << "\n\tWelcome to the Aubie message group!\t" << endl;
	
	//bottom row of equal signs
	i = 0;
	while (i < 60) {
		cout << "=";
		i++;
	}
	cout << endl;
	//prompt the user for their username.


	
	do {
		cout << "Enter user name> ";
		cin >> username;
		b_user = "{[" + username + "]}";
		cout << "Enter the message> ";	
		getline(cin, message);

		if (message == "!!") {
			message.clear();
			message_buffer.erase(message_buffer.rfind("{["), 
			b_user.length()+1);
			cout << "Anymore users? Enter yes or no. > "; 
			cin >> add_user;
			cout << "Enter user name> ";
			cin >> username;
			b_user = "{[" + username + "]}";
			cout << "Enter the message> ";
			getline(cin, message);
		}
		else {
			u_message = b_user + message;
			message_buffer.insert(0, u_message);
			
		}
	}	
	while (message == "!!");
	//cout << "The current messages are: " 
	//	 <<  << 
	cout << message_buffer << endl;
	
	return 0;


