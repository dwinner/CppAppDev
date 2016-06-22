#include <initializer_list>
#include <vector>

class PointSequence
{
public:
   PointSequence(std::initializer_list<double> args);
   void dumpPoints() const;
protected:
   std::vector<double> points;
};
