#include "payload.h"

void payload_string(char* payload)
{

    unsigned char stringLen = *payload;
    char* string = calloc(stringLen + 1, 1);

    memcpy(string, ++payload, stringLen);

    printf("recv string %s\n", string);
    free(string);

}

struct Deck* payload_deck(char* payload)
{
    unsigned int cardCount = *payload;
    
    struct Deck* tempdeck = deck_new();

    for (int i = 0; i < cardCount; i++)
    {
        struct Card* c = malloc(sizeof(struct Card));
        c->koz = *++payload;
        c->val = *++payload;
        //printf("card created with koz %d val %d\n", c->koz, c->val);
        deck_push(tempdeck, c);
    }

    return tempdeck;
    
}

void payload_check(char* payload, unsigned int payloadbytes)
{
    unsigned char opcode = payload[0];
    unsigned char dataCount = *++payload;
    printf("opcode %d dataCount %d payloadbytes %d\n", opcode, dataCount, payloadbytes);
    switch (opcode)
    {
        case OPCODE_STRING:
        {
            payload_string(payload);
            if (dataCount * 2 != payloadbytes - 2)
                payload_check(++payload + dataCount, payloadbytes - 2 - dataCount);
            break;
        }
        case OPCODE_DECK:
        {
            struct Deck* deck = payload_deck(payload);
            gui_printdeck(deck);
            if (dataCount * 2 != payloadbytes - 2)
                payload_check(++payload + dataCount * 2, payloadbytes - 2 - dataCount * 2);
            break;
        }
        
    }
}