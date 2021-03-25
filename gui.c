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
        currentCard->win = subwin(deckWin, 3, 3, deckWin->_begy + 1, deckWin->_begx + (i * 3) + 1);
        box(currentCard->win, 0, 0);
        char cardstr[3] = {currentCard->koz + '0', currentCard->val + '0', 0};
        mvwaddstr(currentCard->win, 1, 1, cardstr );
        wrefresh(currentCard->win);
    }
}

void gui_updatePlayedCardWin(struct Card* c)
{
    wclear(playedCardWin);
    box(playedCardWin, 0, 0);
    char cardstr[3] = {c->koz + '0', c->val + '0', 0};
    mvwaddstr(playedCardWin, 1, 1, cardstr);
    wrefresh(playedCardWin);

}

void gui_createDeckWindow()
{
    puts("creating deckwin");
    deckWin = subwin(stdscr, 5, getmaxx(stdscr) - 2, 15, 1);
    box(deckWin, 0, 0);
    wrefresh(deckWin);
}

void gui_createPlayedCardWin()
{
    playedCardWin = subwin(stdscr, 3, 3, 5, 15);
    box(playedCardWin, 0, 0);
    wrefresh(playedCardWin);
}

char* gui_setUserName()
{
    WINDOW* nameInputField = subwin(stdscr, 5, 20, 1, 1);
    box(nameInputField, 0, 0);
    wrefresh(nameInputField);
    char* buf = calloc(1024, 1);
    int counter = 0;
    while (1)
    {
        int ch = getch();
        if (ch == 13)
        {
            wclear(nameInputField);
            wrefresh(nameInputField);
            delwin(nameInputField);
            return buf;
        }

        if (ch == 8 && counter > 0)
        {
            counter--;
            buf[counter] = 0;
            wclear(nameInputField);
            box(nameInputField, 0, 0);
            mvwaddstr(nameInputField, 1, 1, buf);
            wrefresh(nameInputField);
        }

        if (ch >= '0' && ch <= 'z')
        {
            buf[counter] = ch;
            counter++;
            wclear(nameInputField);
            box(nameInputField, 0, 0);
            mvwaddstr(nameInputField, 1, 1, buf);
            wrefresh(nameInputField);
        }
    }
}

unsigned long __stdcall gui_blink_wait_players(void* w)
{
    WINDOW* win = subwin(stdscr, 3, 21, 4, 4);
    while (1)
    {
        wclear(win);
        wattron(win, A_STANDOUT);
        box(win, 0, 0);
        wattroff(win, A_STANDOUT);
        mvwaddstr(win, 1, 1, "waiting for players");
        wrefresh(win);
        Sleep(500);
        wclear(win);
        box(win, 0, 0);
        mvwaddstr(win, 1, 1, "waiting for players");
        wrefresh(win);
        Sleep(500);
    }
}

void gui_init()
{
    initscr();
    cbreak();
    noecho();
    raw();
    keypad(stdscr, 1);
    refresh();
    //gui_createDeckWindow();
    //gui_createPlayedCardWin();
}