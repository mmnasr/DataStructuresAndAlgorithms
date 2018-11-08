#include <iostream>
#include <string>

void removeDuplicateChars(char* str, int n) {
	if (str == NULL) return;
	if (n < 2) return;

	bool charHit[256];
	for (int i=0; i < 256; i++)
		charHit[i] = false;
	
	int tail = 1; 
	charHit[str[0]] = true;
	for (int i=1; i < n; i++) {
		if (!charHit[str[i]]) {
			str[tail] = str[i];
			tail++;
			charHit[str[i]] = true;
		}
	}
	str[tail] = 0;

	for (int i=0; i<tail; i++) {
		std::cout << str[i] << std::endl;
	}
}

int main(int argc, char* argv[]) {

	char test[]="aaaaaa";
	removeDuplicateChars(test, 6);
	return 0;
}