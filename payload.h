#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "network.h"
#include "game/Deck.h"
#include "game/Card.h"
#include "gui.h"

#define OPCODE_WAIT_PLAYERS_END 9
#define OPCODE_WAIT_PLAYERS     8
#define OPCODE_GET_NAME         6
#define OPCODE_SENT_CARD        5
#define OPCODE_GET_CARD         3
#define OPCODE_STRING           2
#define OPCODE_DECK             1

void payload_check(char* payload, unsigned int payloadbytes);