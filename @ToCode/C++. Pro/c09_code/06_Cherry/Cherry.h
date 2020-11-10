#pragma once

#include <iostream>

class Cherry
{
public:
	Cherry() {}

	virtual void printType()
	{
		std::cout << "I am a Cherry" << std::endl;
	}
};
