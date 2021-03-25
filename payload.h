#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Card.h"

#define OPCODE_STRING 2
#define OPCODE_DECK 1

void payload_check(char* payload, unsigned int payloadbytes);