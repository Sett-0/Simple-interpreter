#include <iostream>
#include <string>
#include "lexer.h"
	
// Nice example: "A * e ^ ((x / q) ^ 2 / 2) + 1";

int main() {
	std::string input = "";
	Lexer lexer;
	while (true) {
		std::cout << ">> ";
		std::getline(std::cin, input);
		if (input == "q") break;
		
		lexer.tokenize(input);
		std::cout << ">> "; lexer.parseExpression().printfTree();
	}
	std::cout << "Cya!\n";
	return 0;
}	