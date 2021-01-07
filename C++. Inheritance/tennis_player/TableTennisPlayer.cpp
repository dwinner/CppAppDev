#include "TableTennisPlayer.h"
#include <iostream>

TableTennisPlayer::TableTennisPlayer(const string& firstName, const string& lastName, bool hasTable)
   : firstName_(firstName), lastName_(lastName), hasTable_(hasTable)
{
}

void TableTennisPlayer::getName() const
{
   std::cout << lastName_ << ", " << firstName_;
}
