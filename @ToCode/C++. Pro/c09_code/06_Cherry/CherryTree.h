#pragma once

class CherryTree
{
public:
	CherryTree() {}

	virtual Cherry* pick()
	{
		return new Cherry();
	}
};
