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


#define PACKET_LENGTH 14 //Number of bytes in a partner port packet


class PartnerPort{
public:
    PartnerPort();
    unsigned char* readToBuffer();
    const int bufferLength = PACKET_LENGTH;
    
private:
    int fd; //File Descriptor
    unsigned char buffer[PACKET_LENGTH];
};


#endif /* defined(__PartnerPort__PartnerPort__) */
