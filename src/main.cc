#include <print>

#include "ncurses.h"
#include "cartridge.h"

int main() {     // 进行刷新，使内容显示到屏幕上
    initscr();
    cbreak();
    noecho();
    mvaddstr(0, 0, "+++++++++++++++++++++++++");
    mvaddstr(LINES - 1, 0, "-------------------------");
    mvaddstr(1, 0, "**********");
    mvaddstr(2, 0, "** ** * **");
    move(3, 0);
    refresh();

    double delayTime = 1.0 / 60;
    for (int i = 0; i < 10000; ++i) {
        usleep((unsigned int)(delayTime * 1000 * 1000));
        auto str = std::to_string(i);

        clear();
        mvaddstr(0, 0, "+++++++++++++++++++++++++");
        mvaddstr(LINES - 1, 0, "-------------------------");
        mvaddstr(1, 0, str.c_str());
        mvaddstr(2, 0, str.c_str());
        move(3, 0);
        refresh();
    }

    usleep(100 * 1000 * 1000);
    endwin();
}