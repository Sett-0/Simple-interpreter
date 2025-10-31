#include <iostream>
#include <string>
#include <unordered_map>
#include "lexer.h"

std::unordered_map<char, double> vars;

// Nice example: "A * e ^ ((x / q) ^ 2 / 2) + 1";
int main() {
	std::string input  = "";
	std::string result = "";
	Lexer lexer;
	
	while (true) {
		std::cout << ">> ";
		std::getline(std::cin, input);
		if (input == "quit") break;
		
		lexer.tokenize(input);
		result = lexer.parseExpression().eval();
		if (!result.empty()) 
			std::cout << ">> " << result << "\n";
	}
	std::cout << "Cya!\n";
	return 0;
}	