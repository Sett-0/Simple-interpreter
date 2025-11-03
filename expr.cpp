#include <iostream>
#include <cmath>
#include "expr.h"

extern std::unordered_map<std::string, double> vars;

bool Expression::isAtom() const { 
	return !atom.empty(); 
}
bool Expression::isOperation() const {
	return static_cast<bool>(operation.first) && !operation.second.empty(); 
}

void Expression::printfTree(unsigned int recDepth) const {
	bool is_atom 	  = isAtom();
	bool is_operation = isOperation();
	
	if (!is_atom && !is_operation) {
		std::cout << "";
		return;
	}
	if (is_atom && is_operation) {
		std::cout << "Fatal error! Expression is an Atom and an Operation at the same time!\n";
		std::cout << "Atom: " << atom << ".\n";
		std::cout << "Operation: (" << operation.first << ", " << operation.second[0].atom << operation.second[1].atom << ").\n";
		std::abort();
	}
	if (is_atom) {
		std::cout << atom;
	} 
	else if (is_operation) {
		std::cout << '(' << operation.first << ' ';
		operation.second[0].printfTree(recDepth + 1);
		std::cout << ' ';
		operation.second[1].printfTree(recDepth + 1);
		std::cout << ')';
	}
	if (!recDepth) std::cout << '\n';
}
	
std::string Expression::eval() {
	bool is_atom 	  = isAtom();
	bool is_operation = isOperation();
	
	if (!is_atom && !is_operation) {
		return "";
	}
	if (is_atom && is_operation) {
		std::cout << "Fatal error! Expression is an Atom and an Operation at the same time!\n";
		std::cout << "Atom: " << atom << ".\n";
		std::cout << "Operation: (" << operation.first << ", " << operation.second[0].atom << operation.second[1].atom << ").\n";
		std::abort();
	}
	if (is_atom) {
		if (atom[0] >= '0' && atom[0] <= '9') return atom;
		else return std::to_string(vars[atom]);
	} 
	else if (is_operation) {
		char op = operation.first;
		Expression lhs = operation.second[0], rhs = operation.second[1];
		
		if (op == '=') {
			if(!lhs.isAtom()) {
				std::cout << "Cannot assign to expression here!\n";
				std::abort();
			} else if (std::tolower(lhs.atom[0]) < 'a' || std::tolower(lhs.atom[0]) > 'z') {
				std::cout << "Invalid sytnax!\n";
				std::abort();
			} else {
				vars[lhs.atom] = std::stod(rhs.eval());
			}
			return "";
		}
		
		double lhs_v = std::stod(lhs.eval());
		double rhs_v = std::stod(rhs.eval());
		switch (op) {
		case '+': return std::to_string(lhs_v + rhs_v);
		case '-': return std::to_string(lhs_v - rhs_v);
		case '*': return std::to_string(lhs_v * rhs_v);
		case '/': return std::to_string(lhs_v / rhs_v);
		case '%': return std::to_string(std::fmod(lhs_v, rhs_v));
		case '^': return std::to_string(std::pow(lhs_v, rhs_v));
		default:
			std::cout << "Fatal error! Encountered undefined operator. Got: \'" << op << "\'.\n";
			std::abort();
		}
	}
	return "";
}