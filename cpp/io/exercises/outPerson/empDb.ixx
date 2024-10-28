export module empDb;

import std;
import emp;

export namespace empStore
{
   class Database
   {
   public:
      virtual ~Database() = default;

      Database() = default;

      void add(empNs::Person aPerson);

      virtual void save(std::string_view aFileName);

      virtual void load(std::string_view aFileName);

      void clear();

      friend std::ostream& operator<<(std::ostream& oStream, const Database& database);

   protected:
      std::vector<empNs::Person> staff_;
   };

   class DirDatabase : public Database
   {
   public:
      void save(std::string_view aDirName) override;

      void load(std::string_view aDirName) override;
   };
}
