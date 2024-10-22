#pragma once

#include <initializer_list>
#include <string>
#include <string_view>
#include <set>
#include <vector>

class AccessList final
{
public:
   // Default constructor.
   AccessList() = default;

   // Constructor to support uniform initialization.
   AccessList(std::initializer_list<std::string_view> users)
   {
      allowedSet_.insert(begin(users), end(users));
   }

   // Adds the user to the permissions list.
   void addUser(std::string user)
   {
      allowedSet_.emplace(std::move(user));
   }

   // Removes the user from the permissions list.
   void removeUser(const std::string &user)
   {
      allowedSet_.erase(user);
   }

   // Returns true if the user is in the permissions list.
   bool isAllowed(const std::string &user) const
   {
      return allowedSet_.contains(user);
   }

   // Returns all the users who have permissions.
   const std::set<std::string> &getAllUsers() const
   {
      return allowedSet_;
   }

   // Returns a vector of all the users who have permissions.
   std::vector<std::string> getAllUsersAsVector() const
   {
      return {begin(allowedSet_), end(allowedSet_)};
   }

private:
   std::set<std::string> allowedSet_;
};
