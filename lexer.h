#ifndef _LEXER_H_ 
#define _LEXER_H_

#include <string>
#include <vector>

enum class Token {
	Atom,
	Op,
	Eof
};

class Lexer {
private:
	std::vector<Token> tokens;
	
public:
	Lexer(std::string& input);
};

#endif