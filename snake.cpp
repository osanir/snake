#include "snake.h"

Part::Part(){
    Part(0, 0);
}

Part::Part(int yPos, int xPos){
    y = yPos;
    x = xPos;
}

Snake::Snake(){
    initscr();
    noecho();
    curs_set(0);
    cbreak();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    srand(time(NULL));

    getmaxyx(stdscr, yMax, xMax);
    y = yMax/2;
    x = xMax/2;
    
    direction = 'l';
    score = 0;
    
    snake.clear();
    // creating snake
    for(int i=0; i<6; i++){
        Part part;
        part = { yMax/2, xMax/2 };
        snake.push_back(part);
    }


}

Snake::~Snake(){
    snake.clear();
    endwin();
}

void Snake::startGame(){
    clear();
    createWindows(1);
    createWindows(2);
    createMeat();

    while( mvSnake() ){
        refresh();
        updateBoards();
        wrefresh(gamewin);
        wrefresh(scorewin);
    };

    gameOver();
}

bool Snake::mvSnake(){
    int ch;
    ch = getch();
    switch(ch){
        case KEY_UP:
            if( direction != 'd')
                direction = 'u';
            break;
        case KEY_DOWN:
            if( direction != 'u')
                direction = 'd';
            break;
        case KEY_LEFT:
            if( direction != 'r')
                direction = 'l';
            break;
        case KEY_RIGHT:
            if( direction != 'l')
                direction = 'r';
            break;
        case 'q':
            return 0;
            break; // meanless
        default:
            break;
    }

    switch(direction){
        case 'u':
            y--;
            break;
        case 'd':
            y++;
            break;
        case 'l':
            x--;
            break;
        case 'r':
            x++;
            break;
    }

    if( checkCollision() == 0){
        return 0;
    }

    snake.push_front({y, x});

    mvaddch(snake.back().y, snake.back().x, ' ');
    snake.pop_back();

    list<Part>::iterator i;
    for(i = snake.begin(); i != snake.end(); i++){
        mvaddch(i->y, i->x, chBody);
    }    
    usleep(110000);
    return 1;
}

int Snake::checkCollision(){
    list<Part>::iterator i;
    for(i = snake.begin(); i != snake.end(); i++){
        // collision with meat
        if( i->x == meat.x && i->y == meat.y ){
            Part tail;
            tail.y = snake.back().y;
            tail.x = snake.back().x;
            snake.push_back(tail);
            createMeat();
            score += 10;
            return 1;
        }

        // collision with tail
        if( i->x == x && i->y == y){
            return 0;
        }

        // collision with border
        if( i->x > (begX+sizeX)-2 || i->x <= begX || i->y > (begY+sizeY)-2   || i->y <= begY){
            return 0;
        }
    }
}

void Snake::createMeat(){
    meat.y = rand() % (begY+sizeY-2) +1;
    meat.x = rand() % (begX+sizeX-2) +1;
    mvaddch(meat.y, meat.x, chMeat);
}

void Snake::updateBoards(){
    mvwprintw(scorewin, 1, 1, "Score: %8d ", snake.size()*8);
    mvwprintw(scorewin, 2, 1, "Size : %8d byte", snake.size());
    mvwprintw(scorewin, 3, 80, "Press 'q' to quit...");
}

void Snake::createWindows(int windowNumber=3){
    switch(windowNumber){
        case 1:{
            gamewin = newwin( yMax-6, xMax-1, 0, 0);
            refresh();
            box(gamewin, 0, 0);
            wrefresh(gamewin);
            getmaxyx(gamewin, sizeY, sizeX);
            getbegyx(gamewin, begY, begX);
            }
            break;
        case 2:{
            scorewin = newwin( 5, xMax-1, yMax-6, 0);
            refresh();
            box(scorewin, 0, 0);
            wrefresh(scorewin);
            break;
            }
        default:
            break;
    }

}

void Snake::gameOver(){
    mvwprintw(gamewin, sizeY/2, sizeX/2-8, "GAME IS OVER!!!");
    wrefresh(gamewin);
    usleep(2000000);

    delwin(gamewin);
    delwin(scorewin);
    endwin();
}
