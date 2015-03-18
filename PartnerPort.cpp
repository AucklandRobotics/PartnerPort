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
    
    this->fd = open(this->portName, O_RDWR | O_NOCTTY | O_NDELAY);
    
    if (this->fd == -1) {
        perror("open_port: Unable to open port");
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

PartnerPort::PartnerPort(const char* name){
    this->portName = name;
    PartnerPort();
}

bool PartnerPort::readToBuffer(){
    int bytes = 0;
    while (bytes < PACKET_LENGTH){
        bytes = read(this->fd, &this->buffer, sizeof(this->buffer));
    }
    
    //This is terrible
    /*
    for (int i=0;i<HEADER_LENGTH;i++){
        if ((int)this->buffer[i] != (int)this->headerBytes[i]){
            //printf("%d %d %d\n",this->buffer[0],this->buffer[1],this->buffer[2]);
            return false;
        }
    }*/
    tcflush(this->fd,TCIOFLUSH);
    return true;
}

unsigned char* PartnerPort::getParnerPortBytes(){
    while(!this->readToBuffer()){}
    return this->buffer;
}

void PartnerPort::writeJoystick(VexJoystick* joy){
    unsigned char* analog = joy->getAnalogChannels();
    bool* button = joy->getButtons();
    //Write header
    for(int i=0;i<HEADER_LENGTH;i++){
        this->writeBuffer[i] = headerBytes[i];
    }
    this->writeBuffer[HEADER_LENGTH] = this->dataLength;
    
    //Write joystick channels
    for (int i=HEADER_LENGTH+1;i<NUM_ANALOG_CHANNELS+HEADER_LENGTH+1;i++){
        this->writeBuffer[i] = *analog;
        analog++;
    }
    
    //Write buttons, there are 2 bytes for buttons
    for (int j=NUM_ANALOG_CHANNELS+HEADER_LENGTH+1;j<NUM_ANALOG_CHANNELS+HEADER_LENGTH+1+2;j++){
        unsigned char buttonByte = 0;
        for (int i=0;i<8;i++){
            if (*button){
                buttonByte += (1 << i);
            }
            button++;
        }
        this->writeBuffer[j] = buttonByte;
    }
    
    //Write Checksum
    this->writeBuffer[PACKET_LENGTH-1] = checksum;
    //Print for debugging
    
    for (int i = 0;i<PACKET_LENGTH;i++){
        printf("%02x ",this->writeBuffer[i]);
    }
    printf("\n");
    write(this->fd,this->writeBuffer,sizeof(this->writeBuffer));
    
}
