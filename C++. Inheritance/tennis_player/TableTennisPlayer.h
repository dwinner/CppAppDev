#ifndef TENNIS_PLAYER_TABLETENNISPLAYER_H
#define TENNIS_PLAYER_TABLETENNISPLAYER_H

#include <string>

using std::string;

// simple base class
class TableTennisPlayer
{
public:
   explicit TableTennisPlayer(const string& firstName = "none",
                              const string& lastName = "none",
                              bool hasTable = false);

   void getName() const;

   bool hasTable() const
   {
      return hasTable_;
   }

   void resetTable(bool v)
   {
      hasTable_ = v;
   }

private:
   string firstName_;
   string lastName_;
   bool hasTable_;
};


#endif //TENNIS_PLAYER_TABLETENNISPLAYER_H
