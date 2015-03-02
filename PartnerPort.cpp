//
//  PartnerPort.cpp
//  PartnerPort
//
//  Created by Matthew Dyer on 2/03/15.
// 
//

#include "PartnerPort.h"
#include <string>

PartnerPort::PartnerPort(){
    struct termios options;
    
    this->fd = open("/dev/tty.usbmodem1411", O_RDWR | O_NOCTTY | O_NDELAY);
    
    if (this->fd == -1) {
        perror("open_port: Unable to open /dev/tty.usbmodem1411");
        _exit(0);
    }
    else {
        fcntl(this->fd, F_SETFL, FNDELAY);
    }
    
    tcgetattr(this->fd, &options );
    
    /* SEt Baud Rate */
    
    cfsetispeed( &options, B115200 );
    cfsetospeed( &options, B115200 );
    
    //I don't know what this is exactly
    
    options.c_cflag |= ( CLOCAL | CREAD );
    
    // Set the Charactor size
    
    options.c_cflag &= ~CSIZE; /* Mask the character size bits */
    options.c_cflag |= CS8;    /* Select 8 data bits */
    
    // Set parity - No Parity (8N1)
    
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    
    
    // Enable Raw Input
    
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    
    // Disable Software Flow control
    
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    
    // Chose raw (not processed) output
    
    options.c_oflag &= ~OPOST;
    
    if ( tcsetattr( this->fd, TCSANOW, &options ) == -1 )
        printf ("Error with tcsetattr = %s\n", strerror ( errno ) );
    else
        printf ( "%s\n", "tcsetattr succeed" );
}

unsigned char* PartnerPort::readToBuffer(){
    int bytes = read(this->fd, this->buffer, sizeof(this->buffer));
    return this->buffer;
}
