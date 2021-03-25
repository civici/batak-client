#include "gui.h"

void gui_removeHighlightCardWindow(struct Card* c)
{
    wclear(c->win);
    box(c->win, 0, 0);
    char cardstr[3] = {c->koz + '0', c->val + '0', 0};
    mvwaddstr(c->win, 1, 1, cardstr);
    wrefresh(c->win);
}

void gui_highlightwCardWindow(struct Card* c)
{

    wclear(c->win);
    wattron(c->win, A_STANDOUT);
    box(c->win, 0, 0);
    wattroff(c->win, A_STANDOUT);
    char cardstr[3] = {c->koz + '0', c->val + '0', 0};
    mvwaddstr(c->win, 1, 1, cardstr);
    wrefresh(c->win);

}

int gui_selectHandler(struct Deck* d)
{

    int currentWin = 0;
    gui_highlightwCardWindow(d->data[currentWin]);
    int ch = 0;
    while (ch != 'q')
    {
        ch = getch();
        printf("ch %d\n", ch);
        if (ch == 'q')
        {
            puts("input q");
            continue;
        }
        gui_removeHighlightCardWindow(d->data[currentWin]);
        if (ch == KEY_RIGHT)
        {
            if (currentWin != d->count - 1)
            {
                currentWin++;
            }
        }
        else if (ch == KEY_LEFT)
        {
            if (currentWin != 0)
            {
                currentWin--;
            }
        }
        else if (ch == KEY_ENTER || ch == 0x0D)
        {
            printf("input enter win %d\n", currentWin);
            return currentWin;
        }
        gui_highlightwCardWindow(d->data[currentWin]);
    }

    puts("select Handler returning");
    return 0;

}

void gui_printdeck(struct Deck* d)
{
    for (int i = 0; i < d->count; i++)
    {
        struct Card* currentCard = d->data[i];
        currentCard->win = subwin(stdscr, 3, 3, 5, (i * 3) + 1);
        box(currentCard->win, 0, 0);
        char cardstr[3] = {currentCard->koz + '0', currentCard->val + '0', 0};
        mvwaddstr(currentCard->win, 1, 1, cardstr );
        wrefresh(currentCard->win);
    }

    //gui_selectHandler(d);

}

void gui_updatePlayedCardWin(struct Card* c)
{
    wclear(playedCardWin);
    box(playedCardWin, 0, 0);
    char cardstr[3] = {c->koz + '0', c->val + '0', 0};
    mvwaddstr(playedCardWin, 1, 1, cardstr);
    wrefresh(playedCardWin);

}

void gui_init()
{
    initscr();
    cbreak();
    noecho();
    raw();
    keypad(stdscr, 1);
    refresh();
    playedCardWin = subwin(stdscr, 3, 3, 15, 15);

}