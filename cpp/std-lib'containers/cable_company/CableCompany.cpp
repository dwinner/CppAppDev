#include <stdexcept>
#include <format>
#include "CableCompany.hpp"

using namespace std;

void CableCompany::addPackage(const string &packageName,
                              const bitset<NumChannels> &channels)
{
   packages_.emplace(packageName, channels);
}

void CableCompany::addPackage(const string &packageName, const string &channels)
{
   addPackage(packageName, bitset<NumChannels>{channels});
}

void CableCompany::removePackage(const string &packageName)
{
   packages_.erase(packageName);
}

const bitset<CableCompany::NumChannels> &CableCompany::getPackage(
    const string &packageName) const
{
   // Get an iterator to the specified package.
   if (auto it{packages_.find(packageName)};
       it != end(packages_))
   {
      // Found package. Note that 'it' is an iterator to a name/bitset pair.
      // The bitset is the second field.
      return it->second;
   }

   throw out_of_range{format("Invalid package '{}'.", packageName)};
}

void CableCompany::newCustomer(const string &name, const string &package)
{
   // Get the channels for the given package.
   auto &packageChannels{getPackage(package)};

   // Create the account with the bitset representing that package.
   newCustomer(name, packageChannels);
}

void CableCompany::newCustomer(const string &name,
                               const bitset<NumChannels> &channels)
{
   // Add customer to the customers map.
   if (auto [iter, success] {customers_.emplace(name, channels)};
       !success)
   {
      // Customer was already in the database. Nothing changed.
      throw invalid_argument{format("Duplicate customer '{}'.", name)};
   }
}

void CableCompany::addChannel(const string &name, int channel)
{
   // Get the current channels for the customer.
   auto &customerChannels{getCustomerChannelsHelper(name)};

   // We found the customer; set the channel.
   customerChannels.set(channel);
}

void CableCompany::removeChannel(const string &name, int channel)
{
   // Get the current channels for the customer.
   auto &customerChannels{getCustomerChannelsHelper(name)};

   // We found this customer; remove the channel.
   customerChannels.reset(channel);
}

void CableCompany::addPackageToCustomer(const string &name, const string &package)
{
   // Get the channels for the given package.
   auto &packageChannels{getPackage(package)};

   // Get the current channels for the customer.
   auto &customerChannels{getCustomerChannelsHelper(name)};

   // Or-in the package to the customer's existing channels.
   customerChannels |= packageChannels;
}

void CableCompany::deleteCustomer(const string &name)
{
   customers_.erase(name);
}

const bitset<CableCompany::NumChannels> &CableCompany::getCustomerChannels(
    const string &name) const
{
   // Find an iterator to the customer.
   if (auto it{customers_.find(name)};
       it != end(customers_))
   {
      // Found customer. Note that 'it' is an iterator to a name/bitset pair.
      // The bitset is the second field.
      return it->second;
   }

   throw invalid_argument{format("Unknown customer '{}'.", name)};
}

bitset<CableCompany::NumChannels> &CableCompany::getCustomerChannelsHelper(
    const string &name)
{
   // Forward to const getCustomerChannels() to avoid code duplication.
   return const_cast<bitset<NumChannels> &>(getCustomerChannels(name));
}
