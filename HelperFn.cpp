
#include "HelperFn.h"

bool IsValue(string input)
{

	// checks if the input string is a double value
	// return true if it's double value, false otherwise

	// Double values can be: 12.5, -12.5, -23, -23. , -23.0 …etc.

	//TODO: complete this function


	if (input[0] == '-' || isdigit(input[0]) || input[0] == '.')
	{
		int c = 0;
		int Num_dot = 0;
		if (input[0] == '-')
		{
			if (input.length() == 1)return false;
		}
		if (input[0] == '.')
		{
			if (input.length() == 1)return false;
			Num_dot++;
		}
		c++;
		while (c != input.length() && (isdigit(input[c]) || input[c] == '.') && Num_dot <= 1)
		{

			if (input[c] == '.')
			{
				if ((!isdigit(input[c - 1]) && input.length() == 2) || Num_dot == 1)
				{
					return false;
				}
				Num_dot++;
				++c;
			}
			else
			{
				++c;
			}

		}
		return !input.empty() && c == input.length();
	}
	return false;
}


bool IsVariable(string input)
{
	// checks if the input string is a variable name
	// return true if it can be a variable name, false otherwise

	// Variable names must start with an alphabetic letter (small or capital) or an underscore (_). 
	// After the first initial letter, variable names can contain letters, numbers and underscores.  
	// No spaces or special characters, however, are allowed.

	//TODO: complete this function
	int c = 0;
	if ((int(input[0]) >= 65 && int(input[0]) <= 90) || (int(input[0]) >= 97 && int(input[0]) <= 122) || (int(input[0]) == 95))
	{
		while (c != input.length() && ((int(input[c]) >= 65 && int(input[c]) <= 90) || (int(input[c]) >= 97 && int(input[c]) <= 122) || (int(input[c]) == 95) || (isdigit(input[c]))))
		{
			++c;
		}

	}
	return !input.empty() && c == input.length();

	return false;
}


OpType ValueOrVariable(string input)
{
	// checks if the input string is a double value or a variable name
	// chand returns enum "OpType" (the enum is declared in the .h)

	//TODO: complete this function
	if (IsVariable(input))return VARIABLE_OP;
	else if (IsValue(input))return VALUE_OP;
	else return INVALID_OP;
}
