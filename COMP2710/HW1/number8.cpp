#include <iostream>
#include <string>

int secondOccurence(std::string x, std::string y) {
	return x.find(y, 1);
}


int main() {
	std::string message_buffer = "{[Martha]}Wazzup!{[Paul]}Please join our A	ubie message group!";
	
	
	std::cout << secondOccurence(message_buffer,"{[") << std::endl;
	return 0;
}

