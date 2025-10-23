#include <iostream>
#include "Lexer.h"
#include <string>

int main() {
	std::string s = "a + b = C";
	Lexer test(s);
	return 0;
}	