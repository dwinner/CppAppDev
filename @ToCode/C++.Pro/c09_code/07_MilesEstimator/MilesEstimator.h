#pragma once

#include <iostream>

class MilesEstimator
{
public:
	virtual int getMilesLeft() const;

	virtual void setGallonsLeft(int inValue);
	virtual int  getGallonsLeft() const;

private:
	int mGallonsLeft;
	virtual int getMilesPerGallon() const;
};
