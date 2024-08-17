#ifndef SPREADSHEETCELLSTATICMEMBERFUNCTIONS_SPREADSHEETCELL_HPP
#define SPREADSHEETCELLSTATICMEMBERFUNCTIONS_SPREADSHEETCELL_HPP


class SpreadsheetCell
{
public:
   SpreadsheetCell() = default;

   SpreadsheetCell(double initialValue);

   SpreadsheetCell(std::string_view initialValue);

   void setValue(double value);

   double getValue() const;

   void setString(std::string_view value);

   std::string getString() const;

private:
   static std::string doubleToString(double value);

   static double stringToDouble(std::string_view value);

   double _value{0};
};


#endif //SPREADSHEETCELLSTATICMEMBERFUNCTIONS_SPREADSHEETCELL_HPP
