#include <ncurses.h>
#include <iostream>
#include <chrono>
//#include <time.h>
//#include <ctime>

static int X_DIM, Y_DIM;

class Vector2D {
public:
  float x;
  float y;

  Vector2D(float x, float y) :  x(x), y(y) {}
};

class Player {
private:
  char *sym;
  Vector2D velocity;
  Vector2D position;

public:
  Player(char *sym, Vector2D X, Vector2D V) : sym(sym), position(X), velocity(V) {}

  void set_velocity(Vector2D V) {
    this->velocity = V;
  }

  void update(float delta_t) {
    position.x = position.x + velocity.x * delta_t;
    position.y = position.y + velocity.y * delta_t;
  }

  void draw() {
    mvprintw(position.y, position.x, sym);
  }
};

int main() {
  initscr();
  curs_set(0);

  cbreak();
  noecho();

  keypad(stdscr, true);
  nodelay(stdscr, true);


  getmaxyx(stdscr, Y_DIM, X_DIM);
 
  Player player("@", Vector2D(5.0, 5.0), Vector2D(0.0, 0.0));
 
  bool quit = false; 
  int c = '\x00';


  auto prev_time = std::chrono::high_resolution_clock::now();

  while (!quit) {
    auto current = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = (current - prev_time);
    prev_time = current;

    clear();
    
    c = getch();
    switch (c) {
      case 'q':
        quit = true;
        break;
      case KEY_RIGHT:
        player.set_velocity(Vector2D(40000, 0.0));
        break;
      case KEY_LEFT:
        player.set_velocity(Vector2D(-40000, 0.0));
        break;
      default:
        player.set_velocity(Vector2D(0,0));
        //mvprintw(0,0, "%f", 5 * duration.count());
        break;
    }

    player.update(duration.count()); 
    player.draw();
    refresh();
  }
  endwin();
}
