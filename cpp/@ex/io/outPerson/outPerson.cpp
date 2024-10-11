import std;
import emp;
import empDb;

using namespace std;
using namespace empNs;
using namespace empStore;

void OutputSample()
{
   const Person person{ "Den", "Vin" };

   // output to the std. console
   cout << person << '\n';

   // output to the string stream
   ostringstream oStrStream;
   oStrStream << person;
   cout << oStrStream.str() << endl;

   // output to a file stream
   ofstream oFileStream("personInf.log");
   oFileStream << person;
   oFileStream.close();
}

void EmpDbSample()
{
   // create employee database
   Database empDb;

   // add some staff
   empDb.add(Person{"John","Doe"});
   empDb.add(Person{"James","Dean"});
   empDb.add(Person{"Marylin","Manson"});

   // save staff into file
   string fileDb="staff.log";
   empDb.save(fileDb);

   // load stuff into database again
   empDb.clear();
   empDb.load(fileDb);

   // print all staff out
   cout << empDb;
}

void EmpDirDbSample()
{
   // create employee database
   DirDatabase empDb;

   // add some staff
   empDb.add(Person{"John","Doe"});
   empDb.add(Person{"James","Dean"});
   empDb.add(Person{"Marylin","Manson"});

   // save staff into file
   string empDir="staff";
   empDb.save(empDir);

   // load stuff into database again
   empDb.clear();
   empDb.load(empDir);

   // print all staff out
   cout << empDb;
}

int main()
{
   EmpDirDbSample();
}
