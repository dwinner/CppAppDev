#include "Person.hpp"

#include <utility>
#include <iostream>

namespace hr
{
   class Person::Impl
   {
   public:
      Impl(const std::string& firstName, const std::string& lastName);

      Impl(std::string firstName, std::string lastName, std::string initials);

      Impl();

      Impl(const Impl&);

      Impl& operator=(const Impl&);

      Impl(Impl &&) noexcept;

      Impl& operator=(Impl &&) noexcept;

      const std::string& getFirstName() const
      {
         return firstName_;
      }

      void setFirstName(const std::string& firstName)
      {
         firstName_ = firstName;
      }

      const std::string& getLastName() const
      {
         return lastName_;
      }

      void setLastName(const std::string& lastName)
      {
         lastName_ = lastName;
      }

      const std::string& getInitials() const
      {
         return initials_;
      }

      void setInitials(const std::string& initials)
      {
         initials_ = initials;
      }

      std::string extractInitials(const std::string& firstName, const std::string& lastName);

      ~Impl();

      bool operator==(const Impl& rhs)
      {
         return std::tie(firstName_, lastName_) == std::tie(rhs.firstName_, rhs.lastName_);
      }

      bool operator!=(const Impl& rhs)
      {
         return !(*this == rhs);
      }

      bool operator<(const Impl& rhs)
      {
         return std::tie(firstName_, lastName_)< std::tie(rhs.firstName_, rhs.lastName_);
      }

      bool operator>(const Impl& rhs)
      {
         return !(*this<rhs);
         //return std::tie(firstName_, lastName_)> std::tie(rhs.firstName_, rhs.lastName_);
      }

      bool operator<=(const Impl& rhs)
      {
         return !(*this>rhs);
      }

      bool operator>=(const Impl& rhs)
      {
         return !(*this < rhs);
      }

      //std::ostream& operator<<(std::ostream& ostream);

   private:
      std::string firstName_;
      std::string lastName_;
      std::string initials_;
   };


   Person::Impl::Impl(const std::string& firstName, const std::string& lastName)
   : Impl{firstName, lastName, extractInitials(firstName, lastName)}
   {
   }

   Person::Impl::Impl(std::string firstName, std::string lastName, std::string initials)
   : firstName_(std::move(firstName)),
        lastName_(std::move(lastName)),
        initials_(std::move(initials))
   {
   }

   Person::Impl::Impl():Impl{"", "", ""}
   {
   }

   Person::Impl::Impl(const Impl&)=default;

   Person::Impl& Person::Impl::operator=(const Impl&)=default;

   Person::Impl::Impl(Impl&&) noexcept=default;

   Person::Impl& Person::Impl::operator=(Impl&&) noexcept=default;

   std::string Person::Impl::extractInitials(const std::string& firstName, const std::string& lastName)
   {
      std::string initials;
      if (!firstName.empty())
      {
         initials += static_cast<char>(std::toupper(firstName[0]));
      }

      if (!lastName.empty())
      {
         initials += static_cast<char>(std::toupper(lastName[0]));
      }

      return initials;
   }

   Person::Impl::~Impl()=default;

   /*std::ostream& Person::Impl::operator<<(std::ostream& ostream)
   {
      const auto empty = "EMPTY";
         ostream << "First name: " << (firstName_.empty() ? empty : firstName_)
         << ", Last name: " << (lastName_.empty() ? empty : lastName_)
         << ", Initials: " << (initials_.empty() ? empty : initials_);

         return ostream;
   }*/

   Person::Person() : impl_{std::make_unique<Impl>()}
   {
   }

   Person::Person(const std::string& firstName, const std::string& lastName)
   :impl_{std::make_unique<Impl>(firstName,lastName)}
   {
   }

   Person::Person(std::string firstName, std::string lastName, std::string initials)
      :impl_{std::make_unique<Impl>(firstName,lastName,initials)}
   {
   }

   Person::Person(const Person& src)
      : impl_{std::make_unique<Impl>(*src.impl_)}
   {
   }

   Person& Person::operator=(const Person& rhs)
   {
      *impl_=*rhs.impl_;
      return *this;
   }

   Person::Person(Person&& src) noexcept=default;

   Person& Person::operator=(Person&& rhs) noexcept=default;

   const std::string& Person::getFirstName() const
   {
      return impl_->getFirstName();
   }

   void Person::setFirstName(const std::string& firstName)
   {
      impl_->setFirstName(firstName);
   }

   const std::string& Person::getLastName() const
   {
      return impl_->getLastName();
   }

   void Person::setLastName(const std::string& lastName)
   {
      impl_->setLastName(lastName);
   }

   const std::string& Person::getInitials() const
   {
      return impl_->getInitials();
   }

   void Person::setInitials(const std::string& initials)
   {
      impl_->setInitials(initials);
   }

   Person::~Person()=default;

   bool operator==(const Person& lhs, const Person& rhs)
   {
      return lhs.impl_==rhs.impl_;
   }

   bool operator!=(const Person& lhs, const Person& rhs)
   {
      return !(lhs == rhs);
   }

   bool operator<(const Person& lhs, const Person& rhs)
   {
      return lhs.impl_<rhs.impl_;
   }

   bool operator>(const Person& lhs, const Person& rhs)
   {
      return rhs < lhs;
   }

   bool operator<=(const Person& lhs, const Person& rhs)
   {
      return rhs >= lhs;
   }

   bool operator>=(const Person& lhs, const Person& rhs)
   {
      return !(lhs < rhs);
   }

   std::ostream& operator<<(std::ostream& ostream, const Person& person)
   {
      const auto empty = "EMPTY";
         ostream << "First name: " << (person.impl_->getFirstName().empty() ? empty : person.impl_->getFirstName())
         << ", Last name: " << (person.impl_->getLastName().empty() ? empty : person.impl_->getLastName())
         << ", Initials: " << (person.impl_->getInitials().empty() ? empty : person.impl_->getInitials());

         return ostream;
   }
}
