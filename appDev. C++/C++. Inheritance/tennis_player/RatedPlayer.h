#ifndef TENNIS_PLAYER_RATEDPLAYER_H
#define TENNIS_PLAYER_RATEDPLAYER_H

#include "TableTennisPlayer.h"

class RatedPlayer : public TableTennisPlayer
{
public:
   explicit RatedPlayer(unsigned int rating = 0, const string& first_name = "none",
                        const string& last_name = "none", bool has_table = false);

   RatedPlayer(unsigned int rating, const TableTennisPlayer& tennisPlayer);

   unsigned int getRating() const
   {
      return rating_;
   }

   void resetRating(unsigned int rating)
   {
      rating_ = rating;
   }

private:
   unsigned int rating_;
};


#endif //TENNIS_PLAYER_RATEDPLAYER_H
