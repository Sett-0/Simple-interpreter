#ifndef _LEXER_H_ 
#define _LEXER_H_

#include <string>
#include <vector>
#include <utility>
#include <iostream>

enum class Token : char {
	Atom = 'A',
	Op   = 'O',
	Eof  = 'E',
};

class Expression {
public:
	char Atom = 0;
	std::pair<char, std::vector<Expression>> Operation;
	
	void printfTree() const {
		bool isAtom 	 = Atom;
		bool isOperation = Operation.first && !Operation.second.empty();
		bool isEof		 = Atom == static_cast<char>(Token::Eof);
		//std::cout << "Atom: " << (int)Atom << ", isEof: " << isEof << '\n';
		if (!isAtom && !isOperation) {
			std::cout << "Error! Expression was not initialized!\n";
			return;
		}
		if (isAtom && isOperation) {
			std::cout << "Fatal error! Expression is an Atom and an Operation at the same time!\n";
			std::cout << "(char)Atom: " << Atom << ", (int)Atom: " << static_cast<int>(Atom) << ".\n";
			std::cout << "Operation: (" << Operation.first << ", " << Operation.second[0].Atom << Operation.second[1].Atom << ").\n";
			std::abort();
		}
		if (isAtom && !isEof) {
			std::cout << Atom;
		} else if (isOperation) {
			std::cout << '(' << Operation.first << ' ';
			Operation.second[0].printfTree();
			std::cout << ' ';
			Operation.second[1].printfTree();
			std::cout << ')';
		} else if (isEof) {
			std::cout << '\n' << '\n' << '\n';
		}
	}
};

class Lexer {
private:
	std::vector<std::pair<char, Token>> tokens;
	
public:
	Lexer(std::string& input);
	void printfTokens() const;
	std::pair<char, Token> next();
	std::pair<char, Token> peek();
	void invalidToken(const std::string &expectedToken, const std::pair<char, Token> &token) const;
	Expression parseExpression(const float minBidingPower = 1.0f);
	std::pair<float, float> infixBindingPower(char op);
};

#endif