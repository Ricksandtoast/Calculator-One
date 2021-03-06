#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;


// Computes the precedence of an operator.
int prec(char op);

// Applies an operator to numbers.
int evaluate(char op, int x, int y);

int main()
{
	int nst[41];       // The number stack.
	int ntop = -1;     // The top of the number stack.
	char ost[41];       // The operator stack.
	int otop = -1;     // The top of the operator stack.

					   // Prompt the user for an expresion and read it.
	string ebuff;       // Buffers the arithmetic expression.
	int ie = 0;         // Indexes the arithmetic expression.
	cout << "enter arithmetic expression:\n";
	getline(cin, ebuff);

	// Let's stick a special character at the end of the string.
	ebuff += ']';

	// Put the beginning of line character in the operator stack.
	otop = 0;
	ost[0] = '[';

	// Scan throught the expression one character at a time.
	bool expectNumber = true;  // For primative error detection.
	for (ie = 0;; ie++) {

		// Buffer the next character.
		char nchar = ebuff[ie];

		// If the next character is a blank or tab, there is nothing to do.
		if (nchar == ' ' || nchar == '\t') {

			continue;
		}
		// Stack the numbers immediately.  HW will be to handle any number.
		if (nchar >= '0' && nchar <= '9') {
			ntop++;
			nst[ntop] = nchar - '0';

			if (!expectNumber) {
				cout << "Syntax error" << endl;
				exit(1);
			}
			expectNumber = false;
			continue;
		}
		// If we have a left parentheses, stack it.
		if (nchar == '(') {
			otop++;
			ost[otop] = '(';

			if (!expectNumber) {
				cout << "Syntax error" << endl;
				exit(1);
			}
			expectNumber = true;
			continue;
		}
		// At this point we must have an operator.
		if (expectNumber) {
			cout << "Syntax error" << endl;
			exit(1);
		}

		// Perform as may operations from the stack as the precedence allows.
		while (prec(ost[otop]) >= prec(nchar)) {

			// Left paren or [ in stack means we have nothing left to
			// evaluate.
			if (ost[otop] == '[' || ost[otop] == '(') break;

			// Perform the indicated operation.
			nst[ntop - 1] = evaluate(ost[otop], nst[ntop - 1], nst[ntop]);
			ntop--;
			otop--;
		}
		// If we broke out because of matching the beginning of the line,
		// the number on the top of the stack is the result.
		if (nchar == ']') {

			if (ost[otop] == '(') {
				cout << "Imbalanced parentheses" << endl;
				exit(1);
			}
			cout << "value of expression is: " << nst[ntop] << endl;
			return 0;
		}
		// If we broke out due to matching parens, pop the paren out of the
		// stack and move on to the next character.
		if (ost[otop] == '(' && nchar == ')') {
			otop--;
			expectNumber = false;
			continue;
		}
		if (nchar == ')') {

			cout << "Imbalanced parentheses" << endl;
			exit(1);
		}
		// Stack the operator that we could not evaluate.
		otop++;
		ost[otop] = nchar;
		expectNumber = true;
		continue;
	}
}
// Function to return the precedence value for an operator.
int prec(char op)
{
	switch (op) {

	case '[':
		return 0;

	case ']':
		return 0;

	case '(':
		return 1;

	case ')':
		return 1;

	case '+':
		return 5;

	case '-':
		return 5;

	case '*':
		return 10;

	case '/':
		return 10;

	default:
		cout << "Illegal operator\n";
		exit(1);
		return 0;
	}
}
// Applies an operator to numbers.
int evaluate(char op, int x, int y)
{

	// Based on the operator, perform the operation.
	switch (op) {

	case '+':
		return x + y;

	case '-':
		return x - y;

	case '*':
		return x * y;

	case '/':
		return x / y;

	default:

		cout << "Illegal operator" << endl;
		exit(1);
		return 0;
	}
}
