#include "Lexer.h"
#include <iostream>
#include <string>

int main() {
	// TODO: adding more than 3 atoms breaks parsing for some reason
	std::string s = "a + b * c"; 
	Lexer lexer(s);
	
	lexer.printfTokens();
	
	Expression expr = lexer.parseExpression();
	expr.printfTree();
	//expr.printfTree();
	return 0;
}	