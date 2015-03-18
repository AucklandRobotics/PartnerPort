//
//  VexJoystick.cpp
//  PartnerPort
//
//  Created by Matthew Dyer on 2/03/15.
//

#include "VexJoystick.h"


VexJoystick::VexJoystick(){
    for (int i=0;i<NUM_BUTTONS;i++){
        this->buttons[i] = false;
    }
    for (int i=0;i<NUM_ANALOG_CHANNELS;i++){
        this->analogChannels[i] = 127;
    }
}

void VexJoystick::setChannel(AnalogChannels channel,char value){
    analogChannels[channel] = value;
}

void VexJoystick::setChannel(AnalogChannels channel,int value){
    this->setChannel(channel,(char)value);
}

void VexJoystick::setChannel(Buttons b,bool value){
    buttons[b] = value;
}

unsigned char* VexJoystick::getAnalogChannels(){
    return this->analogChannels;
}

bool* VexJoystick::getButtons(){
    return this->buttons;
}