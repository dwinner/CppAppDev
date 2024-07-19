#ifndef CUSTOM_FORMATTIBLE_TYPES_KEYVALUE_H
#define CUSTOM_FORMATTIBLE_TYPES_KEYVALUE_H

#include <string_view>
#include <string>

class KeyValue
{
public:
   KeyValue(std::string_view key, int value)
       : m_key{key},
         m_value{value}
   {
   }

   [[nodiscard]] const std::string &getKey() const
   {
      return m_key;
   }

   [[nodiscard]] int getValue() const
   {
      return m_value;
   }

private:
   std::string m_key;
   int m_value{0};
};


#endif //CUSTOM_FORMATTIBLE_TYPES_KEYVALUE_H
