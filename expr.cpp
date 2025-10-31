#include <iostream>
#include <unordered_map>
#include "expr.h"

void Expression::printfTree(unsigned int recDepth) const {
	bool isAtom 	 = Atom;
	bool isOperation = Operation.first && !Operation.second.empty();
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
	if (isAtom) {
		std::cout << Atom;
	} else if (isOperation) {
		std::cout << '(' << Operation.first << ' ';
		Operation.second[0].printfTree(recDepth + 1);
		std::cout << ' ';
		Operation.second[1].printfTree(recDepth + 1);
		std::cout << ')';
	}
	if (!recDepth) std::cout << '\n';
}
	
double Expression::eval() {
	
}