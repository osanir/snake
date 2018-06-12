#include "menu.h"

Menu::Menu(){
    initscr();
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr, true);

    getmaxyx(stdscr, yMax, xMax);
    menuwin = newwin(6, xMax-12, yMax-8, 5);
    box(menuwin, 0,0);
    refresh();
    wrefresh(menuwin);
}

void Menu::showMenu(){
    string choices[] = {"Play", "Help", "Exit"};
    int highlight = 0;
    int ch = ' ';
    do {
        switch (ch){
            case KEY_UP:
                highlight--;
                break;
            case KEY_DOWN:
                highlight++;
                break;
            default:
                break;
        }
        highlight += 3;
        highlight %= 3;

        if( ch == 10){
            if( highlight == MENU::PLAY ){
                Snake snake;
                snake.startGame();
                clear();
                box(menuwin, 0,0);
                refresh();
                wrefresh(menuwin);
                
            }
            if( highlight == MENU::HELP ){
                mvwprintw(menuwin, 1,20, "Classic snake game.");
                mvwprintw(menuwin, 2,20, "Just use arrow keys.");
                mvwprintw(menuwin, 3,20, "Eat meats (*), and grow up!");
            }
            if( highlight == MENU::EXIT ){
                endwin();
                return;
            }
        }
        for(int i=0; i<3; i++){
            if( i == highlight)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, 3, "%s", choices[i].c_str() );
            wattroff(menuwin, A_REVERSE);
            wrefresh(menuwin);
        }
    } while( (ch = getch()) != 'q' );
    endwin();
}