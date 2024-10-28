#pragma once

#include <cstdlib>
#include <queue>
#include <stdexcept>

template<typename T>
class PacketBuffer final
{
public:
   // If maxSize is 0, the size is unlimited, because creating
   // a buffer of size 0 makes little sense. Otherwise, only
   // maxSize packets are allowed in the buffer at any one time.
   explicit PacketBuffer(std::size_t maxSize = 0);

   // Stores a packet in the buffer.
   // Returns false if the packet has been discarded because
   // there is no more space in the buffer, true otherwise.
   bool bufferPacket(const T &packet);

   // Returns the next packet. Throws out_of_range
   // if the buffer is empty.
   [[nodiscard]] T getNextPacket();

private:
   std::queue<T> packets_;
   std::size_t maxSize_;
};

template<typename T>
PacketBuffer<T>::PacketBuffer(std::size_t maxSize/* = 0 */)
    : maxSize_{maxSize}
{
}

template<typename T>
bool PacketBuffer<T>::bufferPacket(const T &packet)
{
   if (maxSize_ > 0 && packets_.size() == maxSize_)
   {
      // No more space. Drop the packet.
      return false;
   }

   packets_.push(packet);
   return true;
}

template<typename T>
T PacketBuffer<T>::getNextPacket()
{
   if (packets_.empty())
   {
      throw std::out_of_range{"Buffer is empty"};
   }

   // Retrieve the head element
   T temp{packets_.front()};

   // Pop the head element
   packets_.pop();

   // Return the head element
   return temp;
}
