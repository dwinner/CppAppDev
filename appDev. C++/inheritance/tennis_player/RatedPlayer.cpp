#include "RatedPlayer.h"

RatedPlayer::RatedPlayer(unsigned int rating, const string& first_name, const string& last_name, bool has_table)
   : TableTennisPlayer(first_name, last_name, has_table)
{
   rating_ = rating;
}

RatedPlayer::RatedPlayer(unsigned int rating, const TableTennisPlayer& tennisPlayer)
   : TableTennisPlayer(tennisPlayer), rating_(rating)
{
}
