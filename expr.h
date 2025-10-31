#ifndef EXPR_H_
#define EXPR_H_

#include <utility>
#include <vector>
#include <unordered_map>

class Expression {
public:
	char atom = 0;
	std::pair<char, std::vector<Expression>> operation;

	bool isAtom() const;
	bool isOperation() const;
	void printfTree(unsigned int recDepth = 0) const;
	std::string eval();
};

#endif // EXPR_H_