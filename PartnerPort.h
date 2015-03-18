//
//  PartnerPort.h
//  PartnerPort
//
//  Created by Matthew Dyer on 2/03/15.
//  
//

#ifndef __PartnerPort__PartnerPort__
#define __PartnerPort__PartnerPort__

#include <stdio.h>
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include "VexJoystick.h"

#define PACKET_LENGTH 14 //Number of bytes in a partner port packet
#define HEADER_LENGTH 3

class PartnerPort{
public:
    PartnerPort();
    PartnerPort(const char* port);
    void writeJoystick(VexJoystick* joy);
    const int bufferLength = PACKET_LENGTH;
    unsigned char* getParnerPortBytes();
private:
    int fd; //File Descriptor
    unsigned char buffer[PACKET_LENGTH];
    unsigned char writeBuffer[PACKET_LENGTH];
    const char *portName = "/dev/cu.wchusbserial1420";
    const int headerBytes[HEADER_LENGTH] = {170,85,57};
    const int dataLength = 10;
    const char checksum = 0x50;
    bool readToBuffer();
};


#endif /* defined(__PartnerPort__PartnerPort__) */
