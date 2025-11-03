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
	std::vector<std::pair<std::string, Token>> tokens;
	
public:
	bool isNumber(const char c);
	bool isLetter(const char c);
	bool tokenize(const std::string& userInput);
	void printfTokens() const;
	std::pair<std::string, Token> next();
	std::pair<std::string, Token> peek();
	void invalidToken(const std::string &expectedToken, const std::pair<std::string, Token> &token) const;
	Expression parseExpression(const float minBidingPower = 0.0f, unsigned int insideBrackets = 0);
	std::pair<float, float> infixBindingPower(char op) const;
};

#endif // LEXER_H_