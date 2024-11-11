export module key_value_pair;

import std;

export
template <typename TKey, typename TVal>
class KeyValuePair
{
public:
   explicit KeyValuePair(TKey key, TVal value):
      key_{std::move(key)},
      value_{std::move(value)}
   {
   }

   const TKey& getKey() const
   {
      return key_;
   }

   void setKey(TKey key)
   {
      key_ = std::move(key);
   }

   const TVal& getValue() const
   {
      return value_;
   }

   void setValue(TVal value)
   {
      value_ = std::move(value);
   }

private:
   TKey key_;
   TVal value_;
};


// A partial specialization of KeyValuePair<> for const char* values.
export
template <typename TKey>
class KeyValuePair<TKey, const char*>
{
public:
   // See Chapter 9 about using pass-by-value semantics.
   explicit KeyValuePair(TKey key, const char* value):
      key_{std::move(key)},
      value_{value}
   {
   }

   const TKey& getKey() const
   {
      return key_;
   }

   void setKey(TKey key)
   {
      key_ = std::move(key);
   }

   const std::string& getValue() const
   {
      return value_;
   }

   void setValue(const char* value)
   {
      value_ = value;
   }

private:
   TKey key_;
   std::string value_;
};
