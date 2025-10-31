#ifndef LEXER_H_ 
#define LEXER_H_

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include "expr.h"

enum class Token : char {
	Atom = 'A',
	Op   = 'O',
	Eof  = 'E',
};

class Lexer {
private:
	std::string input;
	std::vector<std::pair<char, Token>> tokens;
	
public:
	void tokenize(const std::string& userInput);
	void printfTokens() const;
	std::pair<char, Token> next();
	std::pair<char, Token> peek();
	void invalidToken(const std::string &expectedToken, const std::pair<char, Token> &token) const;
	Expression parseExpression(const float minBidingPower = 0.0f, unsigned int insideBrackets = 0);
	std::pair<float, float> infixBindingPower(char op) const;
};

#endif // LEXER_H_