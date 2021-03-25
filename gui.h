#pragma once

#include <stdlib.h>
#include <string.h>
#include <curses.h>

#include "game/Deck.h"
#include "game/Card.h"

void gui_printdeck(struct Deck* d);

void gui_init();