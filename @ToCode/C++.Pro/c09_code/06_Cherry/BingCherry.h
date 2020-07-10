#pragma once

#include <iostream>
#include "Cherry.h"

class BingCherry : public Cherry
{
public:
	BingCherry() {}

	virtual void printType() override
	{
		std::cout << "I am a Bing Cherry" << std::endl;
	}

	virtual void polish() {}
};
