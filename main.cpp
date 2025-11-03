#include <iostream>
#include <string>
#include <unordered_map>
#include "lexer.h"

std::unordered_map<std::string, double> vars;

int main() {
	std::string input  = "";
	std::string result = "";
	Lexer lexer;
	
	while (true) {
		std::cout << ">> ";
		std::getline(std::cin, input);
		if (input == "quit" || input =="exit") break;
		if (!lexer.tokenize(input)) continue;
		result = lexer.parseExpression().eval();
		if (!result.empty()) 
			std::cout << ">> " << result << "\n";
	}
	std::cout << "Cya!\n";
	return 0;
}	