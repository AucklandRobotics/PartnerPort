#include <stdio.h>   /* Standard input/output definitions */
#include "PartnerPort.h"
#include "VexJoystick.h"

int main()
{
    VexJoystick joy;
    joy.setChannel(CH_1,1);

    PartnerPort port;
    for(;;){
        //auto buffer = port.getParnerPortBytes();
        //printf("\nnumber of bytes read is %u\n", port.bufferLength);
        /*for (int i = 0;i<port.bufferLength;i++){
            printf("%02x ",buffer[i]);
        }*/
        VexJoystick joy;
        joy.setChannel(CH_7U,true);
        joy.setChannel(CH_7D,true);
        port.writeJoystick(&joy);
        usleep(22220);
    }
    return 0;
}

//aa 55 39 0a 76 12 c0 5f 06 06 06 06 bf 50