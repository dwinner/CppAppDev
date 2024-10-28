#include <iostream>
#include <print>
#include "IPPacket.hpp"
#include "PacketBuffer.hpp"

using namespace std;

int main()
{
   PacketBuffer<IPPacket> ipPackets{3};

   // Add 4 packets
   for (int i{1}; i <= 4; ++i)
   {
      if (!ipPackets.bufferPacket(IPPacket{i}))
      {
         println("Packet {} dropped (queue is full).", i);
      }
   }

   while (true)
   {
      try
      {
         IPPacket packet{ipPackets.getNextPacket()};
         println("Processing packet {}", packet.getId());
      }
      catch (const out_of_range &)
      {
         println("Queue is empty.");
         break;
      }
   }
}
