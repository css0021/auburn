/* Name: Chris Strong
 * Auburn UID: css0021
 * Filename: aubie.cpp
 * Date: 9/06/2013
 */


#include <iostream>
#include <string>



using namespace std;
/*
 * function: main 
 * description: runs the aubie message system program
 */
int main() {
	
	string username; //username 
	string b_user; //username with brackets
	string message; //message the user enters
	string message_buffer; //message buffer where all the messages are stored
	string add_user; //choice whether or not to add a user
	cout << "================================================================" << endl;
	cout << "|		Welcome to the Aubie Message System!		|" << endl;
	cout << "================================================================" << "\n\n";
	
	do { //prompt the user to enter user name and message. if message == !! then ask for more users.
		cout << "Enter user name> ";
		getline(cin, username);
		b_user = "{[" + username + "]}";
		cout << "Enter the message> ";
		message = "";
		while (message != "!!") {
			getline(cin, message);
			if (message == "!!") {
				continue;
			}
			message_buffer = "\n" + message_buffer.insert(0, message); 
		}
		message_buffer.insert(0, b_user);
		cout << "\nAny more users? > ";
		getline(cin, add_user);
		if (add_user == "yes") {
			cout << endl;	
			continue;
		}
	
	} while (add_user == "yes");
	string output;
	//loop through message buffer and add the indivudual messages to the output string
	
	cout << "\nThe current messages are: " << "\n";
	while (!message_buffer.empty()){
		username = message_buffer.substr(2, message_buffer.find("]}") - 2); //get username
		output.append("\n" + username + ":"); //add username plus colon to the output
		message_buffer.erase(0, message_buffer.find("]}") + 2); //erase the username plus brackets		
		message = message_buffer.substr(0, message_buffer.find("{[")); //get the message from index 0 to the next occurrence of {[
		while (!message.empty()) { //loop to parse the message to get individual messages from the user. Then adds to the output string
			string sub_message = message.substr(message.rfind("\n", - 1)); 
			output.append(sub_message); //add the sub message to the output 
			message.erase(message.rfind("\n", - 1)); //erase the sub_message because it is not needed anymore
		
			if (!message_buffer.empty()) {
				message_buffer = message_buffer.erase(0,message_buffer.find("{["));
			}
		
			else ; 
			if (message.empty())output.append("\n");
			}
	}	
	cout << output << endl;

	
 	return 0;
}
