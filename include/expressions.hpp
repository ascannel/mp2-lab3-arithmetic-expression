#pragma once
#include <vector>
#include <string>
#include <stack>

using namespace std;

enum class Status {
	start,
	end,
	error,
	number, 
	un_op,
	bin_op,
	left_bracket,
	right_bracket
};

enum class TypeLexeme {
	blank,
	number,
	un_minus,
	bin_minus,
	bin_plus,
	bin_div,
	bin_mult,
	pow,
	left_bracket,
	right_bracket
};

enum class Priority {
	blank,
	number,
	operations_low,
	operations_high,
	brackets
};


class Lexeme {
public:
	TypeLexeme type;
	Priority priority;
	double value;
	Lexeme() { type = TypeLexeme::blank; value = 0; priority = Priority::blank; }
	Lexeme(TypeLexeme input_type, double input_value, Priority input_priority) : type(input_type), value(input_value), priority(input_priority) {}
	~Lexeme() {}
};

TypeLexeme getType(char symbol, Status statusLexeme) {
	if (isdigit(symbol))
		return TypeLexeme::number;
	else if (symbol == '-' && (statusLexeme == Status::start || statusLexeme == Status::left_bracket))
		return TypeLexeme::un_minus;
	else if (symbol == '+')
		return TypeLexeme::bin_plus;
	else if (symbol == '-')
		return TypeLexeme::bin_minus;
	else if (symbol == '*')
		return TypeLexeme::bin_mult;
	else if (symbol == '/')
		return TypeLexeme::bin_div;
	else if (symbol == '^')
		return TypeLexeme::pow;
	else if (symbol == '(')
		return TypeLexeme::left_bracket;
	else if (symbol == ')')
		return TypeLexeme::right_bracket;
	throw "error when getting lexeme type";
}

Lexeme nextLexeme(string input, int& index, Status statusLexeme) {
	char symbol = input[index];
	if (isdigit(symbol)) {
		char* ptrEnd;
		double value = strtod(&input[index], &ptrEnd);
		int dif = (ptrEnd - &input[index]);
		index += dif - 1;
		return Lexeme(TypeLexeme::number, value, Priority::blank);
	}
	else if (symbol == '-' && (statusLexeme == Status::start || statusLexeme == Status::left_bracket))
		return Lexeme(TypeLexeme::un_minus, 0, Priority::operations_high);
	else if (symbol == '-')
		return Lexeme(TypeLexeme::bin_minus, 0, Priority::operations_low);
	else if (symbol == '+')
		return Lexeme(TypeLexeme::bin_plus, 0, Priority::operations_low);
	else if (symbol == '*')
		return Lexeme(TypeLexeme::bin_mult, 0, Priority::operations_high);
	else if (symbol == '/')
		return Lexeme(TypeLexeme::bin_div, 0, Priority::operations_high);
	else if (symbol == '^')
		return Lexeme(TypeLexeme::pow, 0, Priority::operations_high);
	else if (symbol == '(')
		return Lexeme(TypeLexeme::left_bracket, 0, Priority::brackets);
	else if (symbol == ')')
		return Lexeme(TypeLexeme::right_bracket, 0, Priority::brackets);
	throw "error when getting next lexeme";
}

vector<Lexeme> postfixForm(vector<Lexeme> input) {
	stack<Lexeme> stack;
	vector<Lexeme> res;
	for (Lexeme item : input) {
		if (item.type == TypeLexeme::number)
			res.push_back(item);
		else if (item.type == TypeLexeme::un_minus || item.type == TypeLexeme::left_bracket)
			stack.push(item);
		else if (item.type == TypeLexeme::right_bracket) {
			while (stack.top().type != TypeLexeme::left_bracket) {
				res.push_back(stack.top());
				stack.pop();
			}
			stack.pop();
		}
		else if (item.type == TypeLexeme::bin_minus || item.type == TypeLexeme::bin_plus || item.type == TypeLexeme::bin_mult || item.type == TypeLexeme::bin_div || item.type == TypeLexeme::pow) {
			while (!stack.empty()) {
				if (item.priority <= stack.top().priority && stack.top().type != TypeLexeme::left_bracket) {
					res.push_back(stack.top());
					stack.pop();
				}
				else
					break;
			}
			stack.push(item);
		}
	}
	while (!stack.empty()) {
		res.push_back(stack.top());
		stack.pop();
	}
	return res;
}

vector<Lexeme> parse(std::string input)
{
	vector<Lexeme> res;
	Status statusLexeme = Status::start;
	size_t leftBracketCounter = 0, rightBracketCounter = 0;
	for (int i = 0; i < input.size(); i++)
	{
		if (rightBracketCounter > leftBracketCounter)
			throw "invalid brackets";

		Lexeme currLex = nextLexeme(input, i, statusLexeme);
		TypeLexeme currType = currLex.type;
		if (statusLexeme == Status::start || statusLexeme == Status::left_bracket)
		{
			switch (currType)
			{
			case TypeLexeme::number:
				statusLexeme = Status::number;
				break;
			case TypeLexeme::bin_plus:
				break;
			case TypeLexeme::bin_minus:
				break;
			case TypeLexeme::bin_mult:
				break;
			case TypeLexeme::bin_div:
				break;
			case TypeLexeme::pow:
				break;
			case TypeLexeme::un_minus:
				statusLexeme = Status::un_op;
				break;
			case TypeLexeme::left_bracket:
				statusLexeme = Status::left_bracket;
				leftBracketCounter++;
				break;
			case TypeLexeme::right_bracket:
				break;
			default:
				if (statusLexeme == Status::start && i == input.size() - 1)
					throw "nothing inputed";
				throw "error with parsing";
			}
		}
		else if (statusLexeme == Status::number || statusLexeme == Status::right_bracket)
		{
			switch (currType)
			{
			case TypeLexeme::bin_plus:
				statusLexeme = Status::bin_op;
				break;
			case TypeLexeme::bin_minus:
				statusLexeme = Status::bin_op;
				break;
			case TypeLexeme::bin_mult:
				statusLexeme = Status::bin_op;
				break;
			case TypeLexeme::bin_div:
				statusLexeme = Status::bin_op;
				break;
			case TypeLexeme::pow:
				statusLexeme = Status::bin_op;
				break;
			case TypeLexeme::right_bracket:
				statusLexeme = Status::right_bracket;
				rightBracketCounter++;
				break;
			default:
				if (i == input.size() - 1 && leftBracketCounter == rightBracketCounter)
					statusLexeme = Status::end;
				else
					throw "incorrect input!";
				break;
			}
		}
		else if (statusLexeme == Status::un_op || statusLexeme == Status::bin_op)
		{
			switch (currType)
			{
			case TypeLexeme::number:
				statusLexeme = Status::number;
				break;
			case TypeLexeme::left_bracket:
				statusLexeme = Status::left_bracket;
				leftBracketCounter++;
				break;
			default:
				throw "incorrect input!";
			}
		}
		res.push_back(currLex);
	}
	if (leftBracketCounter != rightBracketCounter)
		throw "invalid brackets";
	if (statusLexeme != Status::number && statusLexeme != Status::right_bracket && statusLexeme != Status::end)
		throw "invalid end";
	return res;
}

double countUp(vector<Lexeme> postfix) {
	stack<Lexeme> stack;
	for (Lexeme item : postfix) {
		if (item.type == TypeLexeme::number)
			stack.push(item);
		else if (item.type == TypeLexeme::bin_minus || item.type == TypeLexeme::bin_plus || item.type == TypeLexeme::bin_mult || item.type == TypeLexeme::bin_div || item.type == TypeLexeme::pow) {
			double a = stack.top().value;
			stack.pop();
			double b = stack.top().value;
			stack.pop();
			double temp = 0.;
			if (item.type == TypeLexeme::bin_plus)
				temp = a + b;
			else if (item.type == TypeLexeme::bin_minus)
				temp = b - a;
			else if (item.type == TypeLexeme::bin_mult)
				temp = a * b;
			else if (item.type == TypeLexeme::bin_div) {
				if (a == 0)
					throw "can't divide to 0";
				else
					temp = b / a;
			}
			else if (item.type == TypeLexeme::pow)
				temp = pow(b, a);
			Lexeme res(TypeLexeme::number, temp, Priority::blank);
			stack.push(res);
		}
		else if (item.type == TypeLexeme::un_minus) {
			double a = stack.top().value;
			stack.pop();
			Lexeme res(TypeLexeme::number, (-a), Priority::blank);
			stack.push(res);

		}
	}
	return stack.top().value;
}
