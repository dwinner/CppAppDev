import std;

using namespace std;

class FileError : public exception
{
public:
   explicit FileError(string filename)
      : filename_{move(filename)}
   {
   }

   const char* what() const noexcept override
   {
      return message_.c_str();
   }

   virtual const string& getFilename() const noexcept
   {
      return filename_;
   }

protected:
   virtual void setMessage(string message)
   {
      message_ = move(message);
   }

private:
   string filename_;
   string message_;
};


class FileOpenError : public FileError
{
public:
   explicit FileOpenError(string filename)
      : FileError{move(filename)}
   {
      FileError::setMessage(format("Unable to open {}.", FileError::getFilename()));
   }
};


class FileReadError : public FileError
{
public:
   explicit FileReadError(string filename, size_t lineNumber) :
      FileError{move(filename)},
      lineNumber_{lineNumber}
   {
      FileError::setMessage(format("Error reading {}, line {}.", FileError::getFilename(), lineNumber));
   }

   virtual size_t getLineNumber() const noexcept
   {
      return lineNumber_;
   }

private:
   size_t lineNumber_{0};
};


vector<int> ReadIntegerFile(const string& filename)
{
   ifstream inputStream{filename};
   if (inputStream.fail())
   {
      // We failed to open the file: throw an exception.
      throw FileOpenError{filename};
   }

   vector<int> integers;
   size_t lineNumber{0};
   while (!inputStream.eof())
   {
      // Read one line from the file.
      string line;
      getline(inputStream, line);
      ++lineNumber;

      // Create a string stream out of the line.
      istringstream lineStream{line};

      // Read the integers one-by-one and add them to the vector.
      int temp;
      while (lineStream >> temp)
      {
         integers.push_back(temp);
      }

      if (!lineStream.eof())
      {
         // We did not reach the end of the string stream.
         // This means that some error occurred while reading this line.
         // Throw an exception.
         throw FileReadError{filename, lineNumber};
      }
   }

   return integers;
}

int main()
{
   const string filename{"IntegerFile.txt"};
   vector<int> myInts;

   try
   {
      myInts = ReadIntegerFile(filename);
   }
   catch (const FileError& e)
   {
      println(cerr, "{}", e.what());
      return 1;
   }

   for (int myInt : myInts)
   {
      print("{} ", myInt);
   }

   println("");
}
