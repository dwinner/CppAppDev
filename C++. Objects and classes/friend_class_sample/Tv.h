#ifndef FRIEND_CLASS_SAMPLE_TV_H
#define FRIEND_CLASS_SAMPLE_TV_H


class Tv
{
public:
    friend class Remote;   // Remote can access Tv private parts

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


#endif //FRIEND_CLASS_SAMPLE_TV_H
