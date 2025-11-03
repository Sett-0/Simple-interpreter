#include "lexer.h"
#include <cctype>
#include <algorithm>
#include <iostream>
#include <unordered_map>

void Lexer::tokenize(const std::string& userInput) {
	input = userInput;
	tokens.clear();
	
	// Remove whitespaces, lowercase
	input.erase(std::remove_if(input.begin(), input.end(), [](unsigned char c) { return std::isspace(c); }), input.end());
	std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });
	
	Token token;
	for (int i = 0; i < input.length(); ++i) {
		char c = input[i];
		if (c >= '0' && c <= '9' || c >= 'a' && c <= 'z') {
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
	for (auto token = std::rbegin(tokens); token != std::rend(tokens); token++) {
		std::cout << '(' << static_cast<char>((*token).first) << ", " << static_cast<char>((*token).second) << ")\n";
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
		std::cout << "Bad token! Expected Token::" << expectedToken << ", but got { " << token.first << ", " << static_cast<char>(token.second) << " }.\n";
		std::abort();
}

Expression Lexer::parseExpression(const float minBindingPower, unsigned int insideBrackets) {
	// Using Pratt Parsing algorithm 
	Expression lhs;
	std::pair<char, Token> token = next();
	if (token.second == Token::Atom) {
		lhs.atom = token.first;
	} 
	else if (token.first == '(') {
		lhs = parseExpression(0.0f, insideBrackets + 1);
		if (next().first != ')') {
			std::cout << "Bad sequence! Didn't find \')\' after \'(\'.\n";
			std::abort();
		}
	}
	else if (token.first == '-') {
		lhs.atom = '0';
		Expression rhs = parseExpression(minBindingPower, insideBrackets);
		std::vector<Expression> atoms = { lhs, rhs };
		auto operation = std::make_pair('-', atoms);
		lhs = { 0, operation };
	}
	else if (token.first == '+') {
		lhs = parseExpression(minBindingPower, insideBrackets);
	}
	else {
		invalidToken("Atom, \'(\' or unary minus", token);
	}
	
	while(true) {
		char op;
		token = peek();
		if (token.first == ')') {
			if (insideBrackets) {
				break;
			} else {
				std::cout << "Bad sequence! Didn't find \'(\' before \')\'.\n";
				std::abort();
			}
		} else if (token.second == Token::Eof) {
			break;
		} else if (token.second == Token::Op) {
			op = token.first;
		} else {
			invalidToken("Op", token);
		}
		
		auto bindingPowers = infixBindingPower(op);
		if (bindingPowers.first < minBindingPower) {
			break;
		}
		next();
		
		Expression rhs = parseExpression(bindingPowers.second, insideBrackets);
		std::vector<Expression> atoms = { lhs, rhs };
		auto operation = std::make_pair(op, atoms);
		lhs = { 0, operation };
	}
	return lhs;
}

std::pair<float, float> Lexer::infixBindingPower(char op) const {
	switch (op) {
	case '+':
	case '-':
		return std::make_pair(1.0f, 1.1f);
		break;
	case '*':
	case '/':
	case '%':
		return std::make_pair(2.0f, 2.1f);
		break;
	case '^':
		return std::make_pair(3.1f, 3.0f);
		break;
	case '=':
		return std::make_pair(0.2f, 0.1f);
	default:
		std::cout << "Fatal error! Encountered undefined operator. Got: " << op << '\n';
		std::abort();
	}
}