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
    HANDLE waitPlayersThread;

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
            puts("printing deck");
            gui_printdeck(currentDeck);
            puts("printed deck");
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
        case OPCODE_GET_NAME:
        {
            puts("opcode name");
            char* name = gui_setUserName();
            printf("name is %s\n", name);

            char* outgoing = calloc(1024, 1);
            outgoing[0] = 7;
            outgoing[1] = strlen(name);
            memcpy(&outgoing[2], name, outgoing[1]);
            free(name); 
            send(connection, outgoing, outgoing[1] + 2, 0);
            break;
        }
        case OPCODE_WAIT_PLAYERS:
        {
            waitPlayersThread = CreateThread(NULL, 0, gui_blink_wait_players, NULL, 0, NULL);
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
            break;
        }
        case OPCODE_GET_NAME:
        {
            if (dataCount != payloadbytes - 2)
            {
                payload_check(++payload, payloadbytes - 2);
            }
            break;
        }
        case OPCODE_WAIT_PLAYERS:
        {
            if (dataCount != payloadbytes - 2)
            {
                payload_check(++payload, payloadbytes - 2);
            }
            break;
        }
    }

}