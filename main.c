#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "network.h"

#undef MOUSE_MOVED

#include <curses.h>

SOCKET connection;


struct Card{

    int koz;
    int val;

};


int main()
{
    
    //initscr();

    connection = openconn();
    puts("test");    

    while (1)
    {
        char* coming_payload = calloc(1024, 1);
        puts("waiting for packet");
        int result = recv(connection, coming_payload, 1024, 0);
        printf("packet received with %d\n", result); 
        if (result < 1)
        {
            puts("exit");
            return 0;
        }

        unsigned int opcode = coming_payload[0];
        if (opcode == 1)
        {
            unsigned int byteCounter = 2;
            unsigned int dataCount = coming_payload[1];
            for (int i = 0; i < dataCount; i++)
            {
                struct Card* c = malloc(sizeof(struct Card));
                c->koz = coming_payload[byteCounter];
                byteCounter++;
                c->val = coming_payload[byteCounter];
                byteCounter++;
                printf("card created with koz %d val %d\n", c->koz, c->val);
            }
        } 
        else if (opcode == 2)
        {
            unsigned int dataCount = coming_payload[1];
            char* string = calloc(dataCount + 1, 1);
            unsigned int byteiterator = 2;
            for (int i = 0; i < dataCount; i++)
            {
                string[i] = coming_payload[byteiterator];
                byteiterator++;
            }
            printf("payload string is %s\n", string);
            free(string);
        } 

        free(coming_payload);
    }

    closesocket(connection);
    puts("done");
    return 0;
}