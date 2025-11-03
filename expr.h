#ifndef EXPR_H_
#define EXPR_H_

#include <utility>
#include <vector>
#include <unordered_map>
#include <string>

class Expression {
public:
	std::string atom = "";
	std::pair<char, std::vector<Expression>> operation;

	bool isAtom() const;
	bool isOperation() const;
	void printfTree(unsigned int recDepth = 0) const;
	std::string eval();
};

#endif // EXPR_H_