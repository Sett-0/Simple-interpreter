#include "Lexer.h"
#include <iostream>
#include <string>

int main() {
	std::string s = "a + b * 4 - 9 * c"; 
	std::cout << s << '\n' << '\n';
	Lexer lexer(s);
	
	lexer.printfTokens();
	std::cout << '\n';
	
	Expression expr = lexer.parseExpression();
	expr.printfTree();
	expr.printfTree();
	return 0;
}	