#include "Lexer.h"
#include <iostream>
#include <string>

int main() {
	std::string s = "a + b * 4 + a"; 
	std::cout << s << '\n' << '\n';
	Lexer lexer(s);
	
	lexer.printfTokens();
	std::cout << '\n';
	
	Expression expr = lexer.parseExpression();
	expr.printfTree();
	return 0;
}	