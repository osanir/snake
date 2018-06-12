#include <ncurses.h>
#include <list>
#include <unistd.h>
#include <random>
#include <ctime>
#include <string>

using namespace std;

struct Part{
    int y, x;
    Part(int y, int x);
    Part();
};

class Snake{
    public:
        Snake();
        ~Snake();

        void startGame();
        bool mvSnake();
        int checkCollision();
        void createMeat();
        void updateBoards();
        void createWindows(int windowNumber);
        void gameOver();
    private:
        int yMax, xMax;
        int y, x;
        list<Part> snake;
        Part meat;
        char direction;
        int score;
        WINDOW *gamewin, *scorewin, *menuwin;
        int sizeX, sizeY, begX, begY;   // gamewin borders
        char chBody = 'o', chMeat = '*';
};