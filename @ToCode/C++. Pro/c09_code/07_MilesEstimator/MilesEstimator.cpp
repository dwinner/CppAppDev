#include "MilesEstimator.h"

int MilesEstimator::getMilesLeft() const
{
	return getMilesPerGallon() * getGallonsLeft();
}

void MilesEstimator::setGallonsLeft(int inValue)
{
	mGallonsLeft = inValue;
}

int MilesEstimator::getGallonsLeft() const
{
	return mGallonsLeft;
}

int MilesEstimator::getMilesPerGallon() const
{
	return 20;
}
