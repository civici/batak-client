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

struct Deck* currentDeck = NULL;

void payload_check(char* payload, unsigned int payloadbytes)
{
    unsigned char opcode = *payload;
    unsigned char dataCount = *++payload;
    printf("opcode %d dataCount %d payloadbytes %d\n", opcode, dataCount, payloadbytes);
    switch (opcode)
    {
        case OPCODE_STRING:
        {
            payload_string(payload);
            break;
        }
        case OPCODE_DECK:
        {
            currentDeck = payload_deck(payload);
            gui_printdeck(currentDeck);
            break;
        }
        case OPCODE_GET_CARD:
        {
            puts("opcode get card");
            int index = gui_selectHandler(currentDeck);
            char outgoingpayload[3] = {4, 1, index};
            send(connection, outgoingpayload, 3, 0);
            puts("card index sent");
            break;
        }
        case OPCODE_SENT_CARD:
        {
            puts("opcode card");
            struct Card* c = malloc(sizeof(struct Card));
            c->koz = *++payload;
            c->val = *++payload;
            printf("card is %d %d\n", c->koz, c->val);
            gui_updatePlayedCardWin(c);
            break;
        }
    }

    switch (opcode)
    {
        case OPCODE_STRING:
        {
            if (dataCount != payloadbytes - 2)
            {
                payload_check(++payload + dataCount, payloadbytes - 2 - dataCount);
            }
            break;
        }
        case OPCODE_DECK:
        {
            if (dataCount * 2 != payloadbytes - 2)
            {
                payload_check(payload + dataCount * 2 + 1, payloadbytes - 2 - dataCount * 2);
            }
            break;
        }
        case OPCODE_GET_CARD:
        {
            if (dataCount != payloadbytes - 2)
            {
                payload_check(++payload, payloadbytes - 2);
            }
            break;
        }
        case OPCODE_SENT_CARD:
        {
            if (dataCount * 2 + 2!= payloadbytes)
            {
                payload_check(++payload, payloadbytes - 4);
            }
        }
    }

}