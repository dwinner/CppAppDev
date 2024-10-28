#pragma once

class IPPacket final
{
public:
   explicit IPPacket(int id)
       : id_{id}
   {
   }

   int getId() const
   {
      return id_;
   }

private:
   int id_;
};
