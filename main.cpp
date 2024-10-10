#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <tuple>

class Vector2D {
public:
  uint32_t x;
  uint32_t y;
  
  Vector2D (uint32_t x, uint32_t y) : x(x), y(y) {} 

  bool operator==(const Vector2D& other) const {
    return x == other.x && y == other.y;
  }
};

class Object {
private:
  std::string str;
  Vector2D position;
  sf::Text text;
  sf::Font font;

public:
  Object(uint32_t x, uint32_t y, std::string str) : position(Vector2D(x,y)), str(str) {
  }

  Object(Vector2D position, std::string str) : position(position), str(str){
  } 

  std::string getText() {
    return str;
  }

  Vector2D getPosition() {
    return position;
  }
};

namespace std {
  template <>
  struct hash<Vector2D> {
    size_t operator()(const Vector2D& key) const {
      return ((hash<uint32_t>()(key.x) ^ (hash<uint32_t>()(key.y) << 1)) >> 1);
    }
  };
}

class Scene {
private:
  std::unordered_map<Vector2D, Object> objects;
 
public:
  Scene() {
    objects = {};
  }


  void addObject(Object object) {
    objects.insert({object.getPosition(), object});
  }
  
  bool isObjectAt(Vector2D pos) {
    auto obj = objects.find(pos);

    if (obj != objects.end()) {
      return true;
    }
    return false;
  }
 
  bool isObjectAt(uint32_t x, uint32_t y) {
    auto obj = objects.find(Vector2D(x,y));

    if (obj != objects.end()) {
      return true;
    }
    return false;
  } 

  std::string getCharAt(uint32_t x, uint32_t y) {
    return objects.at(Vector2D(x,y)).getText();
  }
};



class Camera {
private:
  uint32_t x;
  uint32_t y;
  uint32_t rows;
  uint32_t cols;
  uint32_t width;
  uint32_t height;

  sf::Font font;
  sf::Text text;

public:
  sf::RenderWindow window;

  Camera(uint32_t x, uint32_t y, uint32_t rows, uint32_t cols) : x(x), y(y), rows(rows), cols(cols) {
    height = rows*20;
    width = cols*10;

    window.create(sf::VideoMode(width, height), "window");

    if (!font.loadFromFile("assets/fonts/ubuntu-mono.ttf"))
      std::cout << "could not creat object" << std::endl;

    text.setPosition(0, 0);

    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
  }


  void render(Scene scene) {
    window.clear();
    std::string str;

    str.reserve(rows*cols + rows);

    std::cout << "hi\n";
    for (uint32_t y = 0; y < rows; y++) {
      for (uint32_t x = 0; x < cols; x++) {
        if (scene.isObjectAt(x,y)) {
          str += scene.getCharAt(x,y);
        } else {
          str += " ";
        } 
      }
      str += "\n";
    }

    text.setString(str);
    window.draw(text);
    window.display();
    std::cout << "quit\n";
  } 
};

int main() {
  Scene scene; 
 
  Object object1(0, 0, "H");
  Object object2(1, 0, "i");
  Object object3(79, 39, "!");
  
  scene.addObject(object1);
  scene.addObject(object2);
  scene.addObject(object3);

  Camera camera(0,0, 40, 80);

  //Object object2(10, 0, "World");

  while (camera.window.isOpen()) {
    sf::Event event;

    while (camera.window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        camera.window.close();
      }
    }

    camera.render(scene);
  }
  
  return 0;
}
