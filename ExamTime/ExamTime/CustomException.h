#pragma once
#include <string>
using namespace std;

class CustomException
{
private:
	string errorMessage;
public:
	CustomException(string msg): errorMessage{msg}{}
	string getMessage() const
	{
		return errorMessage;
	}
};

