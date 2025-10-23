#include "Lexer.h"
#include <cctype>
#include <algorithm>
#include <iostream>

Lexer::Lexer(std::string &input) {
	// Remove whitespaces, lowercase
	input.erase(std::remove_if(input.begin(), input.end(), [](unsigned char c) { return std::isspace(c); }), input.end());
	std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });
	
	Token token;
	for (int i = 0; i < input.length(); ++i) {
		char c = input[i];
		if (c >= '0' && c <= '9' || c >= 'a' && c < 'z') {
			token = Token::Atom;
		} else {
			token = Token::Op;
		}
		tokens.push_back(std::make_pair(c, token)); 
	}
	tokens.push_back(std::pair<char, Token>('\0', Token::Eof)); 
	std::reverse(tokens.begin(), tokens.end());
}

void Lexer::printfTokens() const {
	for (const auto &token : tokens) {
		std::cout << '(' << static_cast<char>(token.first) << ", " << static_cast<char>(token.second) << ")\n";
	}
}

std::pair<char, Token> Lexer::next() {
	auto ret = tokens.back();
	tokens.pop_back();
	return ret;
}

std::pair<char, Token> Lexer::peek() {
	return tokens.back();
}

void Lexer::invalidToken(const std::string &expectedToken, const std::pair<char, Token> &token) const {
		std::cout << "Bad token! Expected Token::" << expectedToken << ", but got (" << token.first << ", " << static_cast<char>(token.second) << ").\n";
		std::abort();
}

Expression Lexer::parseExpression(const float minBindingPower) {
	// Using Pratt Parsing algorithm 
	Expression lhs;
	std::pair<char, Token> token = next();
	if (token.second == Token::Atom) {
		lhs.Atom = token.first;
	} else {
		invalidToken("Atom", token);
	}
	
	while(true) {
		Expression op;
		token = peek();
		if (token.second == Token::Eof) {
			return lhs;
		} else if (token.second == Token::Op) {
			op.Atom = token.first;
		} else {
			invalidToken("Op", token);
		}
		next();
		
		auto bindingPowers = infixBindingPower(op.Atom);
		if (bindingPowers.first < minBindingPower) {
			break;
		}
		Expression rhs;
		rhs = parseExpression(bindingPowers.second);
		
		std::vector<Expression> operation =  { lhs, rhs };
		Expression expr = { 0, std::make_pair(op.Atom, operation) };
		return expr;
	}
	return lhs;
}

std::pair<float, float> Lexer::infixBindingPower(char op) {
	if (op == '+' || op == '-') {
		return std::make_pair(1.0f, 1.1f);
	} else if(op == '*' || op == '/') {
		return std::make_pair(2.0f, 2.1f);
	} else {
		std::cout << "Fatal error! Encountered undefined operator! Got: " << op << '\n';
		std::abort();
	}
}