#include "lexer.h"
#include <cctype>
#include <algorithm>
#include <iostream>
#include <unordered_map>

bool Lexer::isNumber(const char c) {
	return (c >= '0') && (c <= '9') || (c == '.');
}

bool Lexer::isLetter(const char c) {
	return (c >= 'A') && (c <= 'Z') || (c >= 'a') && (c <= 'z') || (c == '_');
}

bool Lexer::tokenize(const std::string& userInput) {
	input = userInput;
	tokens.clear();
	
	// Remove whitespaces, lowercase
	input.erase(std::remove_if(input.begin(), input.end(), [](unsigned char c) { return std::isspace(c); }), input.end());
	//std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });
	
	char c;
	std::string token;
	for (int i = 0; i < input.length(); ++i) {
		c = input[i];
		if (isNumber(c) || isLetter(c)) {
			token += c;
			c = input[i+1];
			if (isLetter(c)) {
				if (isNumber(token[0])) {
					std::cout << "Variable names cannot start with a number!\n";
					return false;
				
				}
			}
			if (!isNumber(c) && !isLetter(c)) {
				tokens.push_back(std::make_pair(token, Token::Atom));
				token = "";
			}
		}
		else {
			token += c;
			tokens.push_back(std::make_pair(token, Token::Op));
			token = "";
		}
	}
	tokens.push_back(std::make_pair("", Token::Eof)); 
	std::reverse(tokens.begin(), tokens.end());
	return true;
}

void Lexer::printfTokens() const {
	for (auto token = std::rbegin(tokens); token != std::rend(tokens); token++) {
		std::cout << '(' << (*token).first << ", " << static_cast<char>((*token).second) << ")\n";
	}
}

std::pair<std::string, Token> Lexer::next() {
	auto ret = tokens.back();
	tokens.pop_back();
	return ret;
}

std::pair<std::string, Token> Lexer::peek() {
	return tokens.back();
}

void Lexer::invalidToken(const std::string &expectedToken, const std::pair<std::string, Token> &token) const {
		std::cout << "Bad token! Expected Token::" << expectedToken << ", but got { " << token.first << ", " << static_cast<char>(token.second) << " }.\n";
		std::abort();
}

Expression Lexer::parseExpression(const float minBindingPower, unsigned int insideBrackets) {
	// Using Pratt Parsing algorithm 
	Expression lhs;
	std::pair<std::string, Token> token = next();
	switch (token.second) {
	case Token::Atom:
		lhs.atom = token.first;
		break;
	case Token::Op:
		switch (token.first[0]) {
		case '(':
			lhs = parseExpression(0.0f, insideBrackets + 1);
			if (next().first[0] != ')') {
				std::cout << "Bad sequence! Didn't find \')\' after \'(\'.\n";
				std::abort();
			}
			break;
		case '-': {
			lhs.atom = "0.0";
			Expression rhs = parseExpression(minBindingPower, insideBrackets);
			std::vector<Expression> atoms = { lhs, rhs };
			auto operation = std::make_pair('-', atoms);
			lhs = { "", operation };
			break;
		}
		case '+':
			lhs = parseExpression(minBindingPower, insideBrackets);
			break;
		default:
			invalidToken("Atom, \'(\' or unary minus", token);
		}
	break;
	case Token::Eof:
		return lhs;
	}
	
	while(true) {
		char op;
		token = peek();
		switch (token.second) {
		case Token::Op:
			switch (token.first[0]) {
			case ')':
				if (insideBrackets) {
					goto exit_loop;
				} else {
					std::cout << "Bad sequence! Didn't find \'(\' before \')\'.\n";
					std::abort();
				}
				break;
			default:
				op = token.first[0];
			}
		break;
		case Token::Eof:
			goto exit_loop;
			break;
		default:
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
		lhs = { "", operation };
	}
	exit_loop:
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
		std::cout << "Fatal error! Encountered undefined operator. Got: \'" << op << "\'.\n";
		std::abort();
	}
}