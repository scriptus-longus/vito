#include <ncurses.h>

static int X_DIM, Y_DIM;

int main() {
  initscr();
  curs_set(0);

  cbreak();
  noecho();

  keypad(stdscr, true);
  nodelay(stdscr, true);

  getmaxyx(stdscr, Y_DIM, X_DIM);
  
  bool quit = false; 
  char c = '\x00';
 
  while (!quit) {
    clear();
    c = getch();
    switch (c) {
      case 'q':
        quit = true;
        break;
      default:
        break;
    }

    mvprintw(0,0, "hi");
    refresh();
  }
  endwin();
}
