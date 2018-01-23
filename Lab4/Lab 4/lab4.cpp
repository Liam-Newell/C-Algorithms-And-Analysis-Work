#include "stack.h"
#include <string>
#include <iostream>

using namespace std;

bool Paired(char open, char closed) 
{
	if (open == '(' && closed == ')')
		return true;
	else if (open == '{' && closed == '}')
		return true;
	else if (open == '[' && closed == ']')
		return true;
	else
		return false;
}

bool bracketCheck(const std::string& s){
	Stack<char> stack;
	
	auto it = s.begin();
	for (;it != s.end();it++) 
	{
		if ('[' == it[0] || '{' == it[0] || '(' == it[0]) {
			stack.push(it[0]);
		}
		else if (']' == it[0] || '}' == it[0] || ')' == it[0]) {
			if (stack.empty() || !Paired(stack.top(), it[0]))
				return false;
			else
				stack.pop();
		}
				

	}
	if (stack.empty())
		return true;
	return false;
}