#ifndef EXPR_H_
#define EXPR_H_

#include <utility>
#include <vector>

class Expression {
public:
	char Atom = 0;
	std::pair<char, std::vector<Expression>> Operation;
	
	void printfTree(unsigned int recDepth = 0) const;
	double eval();
};

#endif // EXPR_H_