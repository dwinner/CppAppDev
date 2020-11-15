#pragma once

#include <memory>
#include "CherryTree.h"

class BingCherryTree : public CherryTree
{
public:
	BingCherryTree() {}

	virtual BingCherry* pick() override
	{
		auto theCherry = std::make_unique<BingCherry>();
		theCherry->polish();
		return theCherry.release();
	}
};
