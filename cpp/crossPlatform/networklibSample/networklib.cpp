#include "networklib.hpp"

HostHandle *lookupHostByName(const char *hostName)
{
   return new HostHandle{};
}

void freeHostHandle(HostHandle *host)
{
   delete host;
}

ConnectionHandle *connectToHost(HostHandle *host)
{
   return new ConnectionHandle{};
}

void closeConnection(ConnectionHandle *connection)
{
   delete connection;
}

char *retrieveWebPage(ConnectionHandle *connection, const char *page)
{
   return new char[]{"Hello Webpage!"};
}

void freeWebPage(char *page)
{
   delete[] page;
}
