#pragma once

#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#undef MOUSE_MOVE

#include <curses.h>

#include "game/Deck.h"
#include "game/Card.h"

WINDOW* deckWin;
WINDOW* playedCardWin;

void gui_printdeck(struct Deck* d);

void gui_init();

int gui_selectHandler(struct Deck* d);

void gui_updatePlayedCardWin(struct Card* c);

void gui_createDeckWindow();

void gui_createPlayedCardWin();

char* gui_setUserName();

unsigned long __stdcall gui_blink_wait_players(void* w);
