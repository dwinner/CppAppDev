export module kv;

import std;

export namespace keyVal
{
   template <typename TKey, typename TVal>
   class KeyValuePair
   {
   public:
      [[nodiscard]] KeyValuePair(TKey key, TVal val)
         : key_(key),
           val_(val)
      {
      }

      TKey getKey() const
      {
         return key_;
      }

      void setKey(TKey key)
      {
         key_ = key;
      }

      TVal getVal() const
      {
         return val_;
      }

      void setVal(TVal val)
      {
         val_ = val;
      }

   private:
      TKey key_;
      TVal val_;
   };

   /*
    * TONOTE: You can provide specialization, or you can act like that:
    * KeyValuePair(const char*, const char*) -> KeyValuePair<std::string, std::string>;
    */

   template <>
   class KeyValuePair<const char*, const char*>
   {
   public:
      [[nodiscard]] KeyValuePair(const char* key, const char* tVal)
         : key_(key),
           val_(tVal)
      {
      }

      std::string getKey() const
      {
         return key_;
      }

      void setKey(const std::string& key)
      {
         key_ = key;
      }

      std::string getVal() const
      {
         return val_.c_str();
      }

      void setVal(const std::string& val)
      {
         val_ = val;
      }

   private:
      std::string key_;
      std::string val_;
   };
}
