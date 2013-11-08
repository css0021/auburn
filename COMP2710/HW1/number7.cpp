#include <iostream>
#include <string>

int firstOccurence(std::string x,std::string y) {
        return x.find(y);
}


int main() {
	std::string message_buffer = "{[Martha]}Wazzup!{[Paul]}Please join our A	ubie message group!";
	
	
	std::cout << firstOccurence(message_buffer,"{[") << std::endl;;
	return 0;
}

