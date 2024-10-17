export module spread_sheet;

import std;
import spreadSheet_errors;

export namespace spreadSheet
{
   class SpreadsheetCell
   {
   public:
      SpreadsheetCell() = default;

      SpreadsheetCell(double initialValue)
         : value_{initialValue}
      {
      }

      SpreadsheetCell(std::string_view initialValue)
         : value_{stringToDouble(initialValue)}
      {
      }

      void setValue(double value)
      {
         value_ = value;
      }

      double getValue() const
      {
         return value_;
      }

      void setString(std::string_view value)
      {
         value_ = stringToDouble(value);
      }

      std::string getString() const
      {
         return doubleToString(value_);
      }

   private:
      std::string doubleToString(double value) const
      {
         return std::to_string(value);
      }

      double stringToDouble(std::string_view value) const
      {
         double number{0};
         std::from_chars(value.data(), value.data() + value.size(), number);
         return number;
      }

      double value_{0};
   };

   class Spreadsheet
   {
   public:
      Spreadsheet(std::size_t width, std::size_t height)
         : width_{width}, height_{height}
      {
         if (width_ >= maxWidth)
         {
            const std::string errorMsg = std::format("Invalid width. The maximum value must be '{}'", maxWidth);
            throw InvalidCoordinateException(width_, errorMsg);
         }

         if (height_ >= maxHeight)
         {
            const std::string errorMsg = std::format("Invalid height. The maximum value must be '{}'", maxHeight);
            throw InvalidCoordinateException(height_, errorMsg);
         }

         try
         {
            cells_ = new SpreadsheetCell*[width_];
            for (size_t i{0}; i < width_; ++i)
            {
               cells_[i] = new SpreadsheetCell[height_];
            }
         }
         catch (const std::bad_alloc&)
         {
            std::throw_with_nested(OutOfMemoryException{"Not enough memory from ctor call"});
         }
      }

      Spreadsheet(const Spreadsheet& src)
      {
         for (size_t i{0}; i < width_; ++i)
         {
            for (size_t j{0}; j < height_; ++j)
            {
               cells_[i][j] = src.cells_[i][j];
            }
         }
      }

      Spreadsheet(Spreadsheet&& src) noexcept
      {
         swap(src);
      }

      ~Spreadsheet()
      {
         for (size_t i{0}; i < width_; ++i)
         {
            delete[] cells_[i];
         }

         delete[] cells_;
         cells_ = nullptr;
      }

      Spreadsheet& operator=(const Spreadsheet& rhs)
      {
         Spreadsheet temp{rhs};
         swap(temp);

         return *this;
      }

      Spreadsheet& operator=(Spreadsheet&& rhs) noexcept
      {
         auto moved{std::move(rhs)};
         swap(moved);

         return *this;
      }

      void setCellAt(std::size_t x, std::size_t y, const SpreadsheetCell& cell)
      {
         verifyCoordinate(x, y);
         cells_[x][y] = cell;
      }

      SpreadsheetCell& getCellAt(std::size_t x, std::size_t y)
      {
         verifyCoordinate(x, y);
         return cells_[x][y];
      }

      void swap(Spreadsheet& other) noexcept
      {
         std::swap(width_, other.width_);
         std::swap(height_, other.height_);
         std::swap(cells_, other.cells_);
      }

   private:
      static constexpr std::size_t maxWidth{100};
      static constexpr std::size_t maxHeight{100};

      void verifyCoordinate(std::size_t x, std::size_t y) const
      {
         if (x >= width_)
         {
            throw InvalidCoordinateException{
               width_, std::format("x ({}) must be less than width ({}).", x, width_)
            };
         }

         if (y >= height_)
         {
            throw InvalidCoordinateException{
               height_, std::format("y ({}) must be less than height ({}).", y, height_)
            };
         }
      }

      std::size_t width_{0};
      std::size_t height_{0};
      SpreadsheetCell** cells_{nullptr};
   };

   void Swap(Spreadsheet& first, Spreadsheet& second) noexcept
   {
      first.swap(second);
   }
}
