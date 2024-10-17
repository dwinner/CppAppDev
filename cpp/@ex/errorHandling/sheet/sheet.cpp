import std;
import spread_sheet;
import spreadSheet_errors;

using namespace std;
using namespace spreadSheet;

int main()
{
   try
   {
      Spreadsheet sheet{100, 256};
   }
   catch (const exception& caughtException)
   {
      println("{}", caughtException.what());
   }

   try
   {
      Spreadsheet sheet{49, 49};
      auto& cell{sheet.getCellAt(55, 55)};
   }
   catch (const exception& caughtException)
   {
      println("{}", caughtException.what());
   }

   try
   {
      Spreadsheet sheet{49, 49};
      sheet.setCellAt(55, 55, SpreadsheetCell{1.2});
   }
   catch (const exception& caughtException)
   {
      println("{}", caughtException.what());
   }
}
