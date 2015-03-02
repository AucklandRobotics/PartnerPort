#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

int main()
{
    
    int fd; /* File descriptor for the port */
    int n;
    int bytes;
    
    char c;
    
    unsigned char buffer[16];
    char *bufptr;
    
    struct termios options;
    
    fd = open("/dev/tty.usbmodem1411", O_RDWR | O_NOCTTY | O_NDELAY);
    
    if (fd == -1) {
        perror("open_port: Unable to open /dev/tty.usbmodem1411 - ");
    }
    else {
        fcntl(fd, F_SETFL, FNDELAY);
    }
    
    tcgetattr( fd, &options );
    
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
    
    if ( tcsetattr( fd, TCSANOW, &options ) == -1 )
        printf ("Error with tcsetattr = %s\n", strerror ( errno ) );
    else
        printf ( "%s\n", "tcsetattr succeed" );
    
    while(true){
        bytes = read(fd, &buffer, sizeof(buffer));
        if (bytes == 14){
            printf("\nnumber of bytes read is %u\n", bytes);
            int i = 0;
            //printf("%02x %02x",buffer[8],buffer[9]);
            for (i=0;i<bytes;i++){
                printf("%02x ",buffer[i]);
            }
        }else{
            
        }
        //perror ("read error:");
    }
    close(fd);
    return 0;
}