#include <stdio.h>   /* Standard input/output definitions */
#include "PartnerPort.h"

int main()
{
    PartnerPort port;
    for(;;){
        auto buffer = port.readToBuffer();
        printf("\nnumber of bytes read is %u\n", port.bufferLength);
        for (int i = 0;i<port.bufferLength;i++){
            printf("%02x ",buffer[i]);
        }
    }
    return 0;
}