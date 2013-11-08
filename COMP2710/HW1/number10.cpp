#include <iostream>
#include <string>


int main() {
	
	std::string message_buffer = "{[Martha]}Wazzup!{[Paul]}Please join our Aubie message group!";
	
	std::cout << message_buffer.substr(19,4) << std::endl;

	return 0;


	


}
