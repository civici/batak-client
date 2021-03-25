#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <curses.h>

struct Card{

    int val;
    int koz;
    WINDOW* win;

};

struct Card* card_new(int val, int koz);