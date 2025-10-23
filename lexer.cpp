#include "Lexer.h"
#include <string>
#include <cctype>
#include <algorithm>
#include <map>

#include <iostream>

Lexer::Lexer(std::string &input) {
	input.erase(std::remove_if(input.begin(), input.end(), [](unsigned char c) { return std::isspace(c); }), input.end());
	std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });
	std::map<char, Token> tokensMap;
	for (int i = 0; i < input.length(); ++i) {
		char c = input[i];
		if (c >= '0' && c <= '9' || c >= 'a' && c < 'z') {
			tokensMap[c] = Token::Atom;
		} else if (c != '\0') {
			tokensMap[c] = Token::Op;
		} else {
			tokensMap[c] = Token::Eof;
		}
	}
	
	for (int i = 0; i < input.length(); i++)
		std::cout << static_cast<int>(tokensMap[input[i]]) << std::endl;
}
