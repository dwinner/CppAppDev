#include <string>
using std::string;

class SpreadsheetCell
{
 public:
  SpreadsheetCell();
  SpreadsheetCell(double initialValue);
  SpreadsheetCell(const string& initialValue);
  SpreadsheetCell(const SpreadsheetCell& src);
  SpreadsheetCell& operator=(const SpreadsheetCell& rhs);
  void set(double inValue);
  void set(const string& inString);

  double getValue() const {mNumAccesses++; return mValue; }
  string getString() const {mNumAccesses++; return mString; }
//  double getValue() const;
//  string getString() const;

  static string doubleToString(double inValue);
  static double stringToDouble(const string& inString);

 protected:
  double mValue;
  string mString;

  mutable int mNumAccesses = 0;
  //mutable int mNumAccesses;	// Pre-C++11
};

/*
inline double SpreadsheetCell::getValue() const
{
    mNumAccesses++;
    return mValue;
}
inline string SpreadsheetCell::getString() const
{
    mNumAccesses++;
    return mString;
}
*/
