#ifndef FRIEND_CLASS_SAMPLE_TV_H
#define FRIEND_CLASS_SAMPLE_TV_H

#include "Remote.h"

class Tv
{
public:
    friend void Remote::setChannel(Tv &tv, int channelNumber);

    enum
    {
        Off,
        On
    };

    enum
    {
        MinVal,
        MaxVal = 20
    };

    enum
    {
        Antenna,
        Cable
    };

    enum
    {
        TV,
        DVD
    };

    Tv(int state = Off, int maxChannel = 125)
            : state_(state),
              volume_(5),
              maxChannel_(maxChannel),
              channel_(2),
              mode_(Cable),
              input_(TV)
    {}

    void onOff()
    {
       state_ = (state_ == On) ? Off : On;
    }

    bool isOn() const
    {
       return state_ == On;
    }

    bool volumeUp();

    bool volumeDown();

    void channelUp();

    void channelDown();

    void setMode()
    {
       mode_ = (mode_ == Antenna) ? Cable : Antenna;
    }

    void setInput()
    {
       input_ = (input_ == TV) ? DVD : TV;
    }

    void settings() const; // display all settings

private:
    int state_;             // on or off
    int volume_;            // assumed to be digitized
    int maxChannel_;        // maximum number of channels
    int channel_;           // current channel setting
    int mode_;              // broadcast or cable
    int input_;             // TV or DVD
};

/*
Also you can use Remote to resolve some preprocessor issues like that:
// Remote methods as inline functions
inline bool Remote::volup(Tv & t) { return t.volup();}
inline bool Remote::voldown(Tv & t) { return t.voldown();}
inline void Remote::onoff(Tv & t) { t.onoff(); }
inline void Remote::chanup(Tv & t) {t.chanup();}
inline void Remote::chandown(Tv & t) {t.chandown();}
inline void Remote::set_mode(Tv & t) {t.set_mode();}
inline void Remote::set_input(Tv & t) {t.set_input();}
inline void Remote::set_chan(Tv & t, int c) {t.channel = c;} 
*/

#endif //FRIEND_CLASS_SAMPLE_TV_H
