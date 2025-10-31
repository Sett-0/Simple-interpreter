#include "Lexer.h"
#include <iostream>
#include <string>
	
// Nice example: "A * e ^ ((x / q) ^ 2 / 2) + 1";

int main() {
	std::string input = "";
	Lexer lexer;
	while (true) {
		std::cout << ">> ";
		std::getline(std::cin, input);
		if (input == "q") break;
		
		lexer.setInput(input);
		std::cout << ">> "; lexer.parseExpression().printfTree();
	}
	std::cout << "Cya!\n";
	return 0;
}	