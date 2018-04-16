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



int prec(char op);
int evaluate(char op, int x, int y);

int main() 
{
	
	int numStack[100];
	int count = 0;
	int numTop = 0;
	char opStack[100];
	opStack[0] = '[';
	int opTop = 0;
	cout << "Enter Arithmetic Expression" << endl;
	string line; //this is the user given equation
	getline(cin, line);
	line += ']';

	bool expectingNum = false; //incase first number is negative
	for (int iline = 0; ; iline++) 
	{
		
		
		cout << "I am reading this " << line[iline] << endl;
		char nChar = line[iline];
		if (line[iline] == '-' && iline==0) {
			cout << " I added a zero to the beginning because - is first " << endl;
			numStack[++numTop] = 0;
		}
		// skip white space
		if (nChar == ' ' || nChar == '\t') { // \t is a tab
			continue;
		}
		int num = 0;
		if (nChar >= '0' && nChar <= '9') 
		{
			int counter;
			counter = 0;
			int mask = iline;
			char next = line[iline + 1];
			while (next >= '0' && next <= '9') 
			{
				
				num *= 10;
				num += line[iline] - '0';
				cout << line[iline] << endl<<num<<endl;
				iline++;
				next = line[iline];
				counter++;
				
			}
			iline = mask;
			
			if (counter == 0) 
			{
				cout << "I found a number " << endl;
				num = nChar - '0'; //why am I doing this??
				numStack[++numTop] = num;
				cout << "i am adding " << num << " to the numStack" << endl;
			}
			else if (counter > 0)
			{
				numStack[++numTop] = num;
				cout << numStack[++numTop];
			}
		
			expectingNum = false;
			continue;
		}
		if (nChar == '(') {
			
			opTop++;
			opStack[opTop] = '(';
			if (!expectingNum) {
				cerr << "PROBLEMMMMMSSS" << endl;
				exit(1);
			}
			
			expectingNum = true;
			continue;
		}
		if (expectingNum) {
			cout << "I found two operators in a row: " << endl;
			char firstOp = line[iline - 1];

			if (firstOp == '-') {
				
			}
			if (firstOp == '*') {
				cout << "I found a minus then a *" << endl;
				cout << "I am firstOp " << firstOp << endl;
			}
		}
	
		
		while (prec(opStack[opTop]) >= prec(nChar))
		{
			if (opStack[opTop] == '[' || opStack[opTop] == '(') break;

			cout << " " << opStack[opTop] << "should be>= " << nChar << endl;
			cout << "This is where I determine precedence " << endl;
			iline++;
			iline++;
			//opTop--; //because I used the minus sign
			opStack[opTop] = line[iline]; //in order to skip to the last character
			cout << "boutta crash" << endl;
			cout << "This is opTop sign " << opStack[opTop] << endl;
			cout << "This opTop -1 " << opStack[opTop - 1] << endl;
			opTop--;
			nChar = line[iline];
			//continue; 

		//else {
			//Perform the indicated opertion
			cout << "numTop: " << numTop << endl;
			cout << " I want to evaluate " << endl;
			cout << numStack[numTop - 1] << "  " << opStack[opTop] << " " << numStack[numTop] << endl;
			numStack[numTop - 1] = evaluate(opStack[opTop], numStack[numTop - 1], numStack[numTop]);
			cout << "Top of the stack is now " << numStack[numTop - 1] << endl;
			numTop--;
			cout << "This might be the top of num stack" << numStack[numTop] << endl;
			opTop--;
			//}
		}
		if (nChar == ']') {
			if (opStack[opTop] == '(') {
				cout << "Imbalnced parentheses" << endl;
				exit(1);
			}
			cout << "value of expression is: " << numStack[numTop] << endl;
			return 0;
		}

		if (opStack[opTop] == '('&& nChar == ')') {
			opTop--;
			expectingNum = false;
			continue;
		}

		if (nChar == ')'){
			cout << "Imbalanced parentheses" << endl;
			exit(1);
		}
		
		opTop++;
		cout << "optop increase by 1 " << opTop << endl;
		opStack[opTop] = nChar;
		expectingNum = true;
		continue;
	}
}
int prec(char op) {
	switch (op) {
	case '[':
		return 0;
	case ']':
		return 0;
	case'(':
		return 1;
	case ')':
		return 1;
	case '+':
		return 5;
	case '-':
		return 5;
	case'*':
		return 10;
	case'/':
		return 10;
	case '^' :
		return 15;
	}
}
	int evaluate(char op, int x, int y) {
		cout << "I have been called and I am now evaluating " << x << op << y << endl;
		switch (op) {
		case '+':
			return x + y;
		case '-':
			return x - y;
		case '*':
			return x*y;
		case '/':
			return x / y;
		case'^':
			return pow(x, y);
		
		default:
			cout << "Illegal operator" << endl;
			exit(1);
			return 0;
		}
	}
