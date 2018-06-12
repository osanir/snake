#include "snake.h"

enum MENU {PLAY = 0, HELP, EXIT  };

class Menu{
    public:
        Menu();

        void showMenu();
        void createWindows(int windowNumber);
    private:
        int xMax, yMax;
        WINDOW *menuwin;
};