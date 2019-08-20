#pragma once

#include <string>

class SpreadsheetApplication; // forward declaration

class Spreadsheet
{
public:

	class SpreadsheetCell
	{
	public:
		SpreadsheetCell();
		SpreadsheetCell(double initialValue);
		SpreadsheetCell(const std::string& initialValue);
		SpreadsheetCell(const SpreadsheetCell& src);

		SpreadsheetCell& operator=(const SpreadsheetCell& rhs);
		
		void set(double inValue);
		void set(const std::string& inString);

		double getValue() const { mNumAccesses++; return mValue; }
		const std::string& getString() const { mNumAccesses++; return mString; }

		static std::string doubleToString(double inValue);
		static double stringToDouble(const std::string& inString);

	private:
		double mValue;
		std::string mString;

		mutable int mNumAccesses = 0;
	};

	Spreadsheet(const SpreadsheetApplication& theApp,
		int inWidth = kMaxWidth, int inHeight = kMaxHeight);
	Spreadsheet(const Spreadsheet& src);
	~Spreadsheet();
	Spreadsheet& operator=(const Spreadsheet& rhs);

	void setCellAt(int x, int y, const SpreadsheetCell& cell);
	SpreadsheetCell& getCellAt(int x, int y);

	int getId() const;

	// Initializing here doesn't work in some compilers
	static const int kMaxHeight = 100;
	static const int kMaxWidth = 100;

private:
	bool inRange(int val, int upper);
	void copyFrom(const Spreadsheet& src);

	int mWidth, mHeight;
	int mId;
	SpreadsheetCell** mCells;

	const SpreadsheetApplication& mTheApp;

	static int sCounter;
};

using SCell = Spreadsheet::SpreadsheetCell;
