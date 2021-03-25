#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "network.h"
#include "payload.h"
#include "game/Card.h"
#include "gui.h"

SOCKET connection;

int main()
{
    
    //initscr();
    gui_init();
    connection = openconn();
    int flag = 1;
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
            goto TERMINATE;
        }

        payload_check(coming_payload, result);
        free(coming_payload);
    }

    TERMINATE:
    closesocket(connection);
    puts("done");
    return 0;
}