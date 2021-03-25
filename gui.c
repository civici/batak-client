#include "gui.h"


void gui_printdeck(struct Deck* d)
{
    for (int i = 0; i < d->count; i++)
    {
        struct Card* currentCard = d->data[i];
        WINDOW* cardwin = subwin(stdscr, 3, 3, 5, (i * 3) + 1);
        box(cardwin, 0, 0);
        char cardstr[3] = {currentCard->koz + '0', currentCard->val + '0', 0};
        mvwaddstr(cardwin, 1, 1, cardstr );
        wrefresh(cardwin);
    }
    while (getch() != 'q')
    {
        
    }
}


void gui_init()
{
    initscr();
    refresh();

}