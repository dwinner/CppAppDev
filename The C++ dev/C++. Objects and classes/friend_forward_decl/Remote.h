#ifndef FRIEND_CLASS_SAMPLE_REMOTE_H
#define FRIEND_CLASS_SAMPLE_REMOTE_H

#include "Tv.h"

class Tv;   // forward declaration

class Remote
{
public:
    Remote(int mode = Tv::TV) : mode_(mode)
    {
    }

    bool volumeUp(Tv &tv)
    {
       return tv.volumeUp();
    }

    bool volumeDown(Tv &tv)
    {
       return tv.volumeDown();
    }

    void onOff(Tv &tv)
    {
       tv.onOff();
    }

    void channelUp(Tv &tv)
    {
       tv.channelUp();
    }

    void channelDown(Tv &tv)
    {
       tv.channelDown();
    }

    void setChannel(Tv &tv, int channelNumber)
    {
       tv.channel_ = channelNumber;
    }

    void setMode(Tv &tv)
    {
       tv.setMode();
    }

    void setInput(Tv &tv)
    {
       tv.setInput();
    }

private:
    int mode_;              // controls TV or DVD
};


#endif //FRIEND_CLASS_SAMPLE_REMOTE_H
