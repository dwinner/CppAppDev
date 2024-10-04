export module kv;

import std;

export namespace keyVal
{
   template <std::integral TKey, std::floating_point TVal>
   class KeyValuePair
   {
   public:
      explicit KeyValuePair(TKey key, TVal val)
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

   /*KeyValuePair(const char*, const char*) -> KeyValuePair<std::string, std::string>;*/
}
