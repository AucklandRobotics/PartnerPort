#include <stdio.h>   /* Standard input/output definitions */
#include "PartnerPort.h"
#include "VexJoystick.h"


/* 
 Test application to mimmic the VEX Controller partner port
 
 
 */
int main()
{
    VexJoystick joy;
    joy.setChannel(CH_1,1);
    joy.setChannel(CH_7U,true);
    joy.setChannel(CH_7D,false);
    
    char* name = "/dev/null";
    
    PartnerPort port(&joy,name);
    port.startSending();
    for(;;){
        //auto buffer = port.getParnerPortBytes();
        //printf("\nnumber of bytes read is %u\n", port.bufferLength);
        /*for (int i = 0;i<port.bufferLength;i++){
            printf("%02x ",buffer[i]);
        }*/
    }
    return 0;
}
