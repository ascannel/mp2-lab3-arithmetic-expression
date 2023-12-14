#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "expressions.hpp"

using namespace std;

int main() {
	string input;
	cout << "input expression : ";
	cin >> input;
	vector<Lexeme> parsed = parse(input);
	vector<Lexeme> postfix = postfixForm(parsed);
	double res = countUp(postfix);
	cout << "\nresult: ";
}