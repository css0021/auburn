#include <iostream>
#include <string>

int main() {
	
	std::string message_buffer = "{[Martha]}Wazzup!{[Paul]}Please join our A	ubie message group!";
	
	std::cout << message_buffer.substr(2,6) << std::endl;

	return 0;


}
