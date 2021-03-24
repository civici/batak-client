#include "payload.h"

void payload_string(char* payload)
{

    unsigned char stringLen = *payload;
    printf("string len %d\n", stringLen);
    char* string = calloc(stringLen + 1, 1);

    memcpy(string, ++payload, stringLen);

    printf("recv string %s\n", string);
    free(string);

}

void payload_check(char* payload)
{
    unsigned char opcode = payload[0];
    printf("opcode %d\n", opcode);
    switch (opcode)
    {
        case 2:
            payload_string(++payload);
            break;
    }
}