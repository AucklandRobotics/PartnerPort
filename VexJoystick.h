//
//  VexJoystick.h
//  PartnerPort
//
//  Created by Matthew Dyer on 2/03/15.
//
//

#ifndef __PartnerPort__VexJoystick__
#define __PartnerPort__VexJoystick__

#define NUM_CHANNELS 16
#define NUM_ANALOG_CHANNELS 4
#define NUM_BUTTONS 16

#include <stdio.h>

enum AnalogChannels{
    CH_1,CH_2,CH_3,CH_4
};

enum Buttons{
    CH_5U,CH_5D,CH_6U,CH_6D,CH_7U,CH_7D,CH_7R,CH_7L,CH_8U,CH_8D,CH_8R,CH_8L
};

class VexJoystick{
public:
    VexJoystick();
    void setChannel(AnalogChannels channel,char value);
    void setChannel(AnalogChannels channel,int value);
    void setChannel(Buttons b,bool value);

    unsigned char* getAnalogChannels();
    bool* getButtons();
    const int numChannels = NUM_CHANNELS;
private:
    unsigned char analogChannels[4]; //Wat
    bool buttons[16];
};

#endif /* defined(__PartnerPort__VexJoystick__) */
