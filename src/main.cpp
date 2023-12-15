#include <iostream>
#include "expressions.hpp"

using namespace std;

int main() {
	cout << "input expression: ";
	string input;
	cin >> input;
	try {
		vector<Lexeme> parsed = parse(input);
		vector<Lexeme> postfix = postfixForm(parsed);
		double res = countUp(postfix);
		cout << "\nresult: " << res;
	}
	catch (const char* s) {
		cout << "incorrect input: " << s << "\n";
	}
}