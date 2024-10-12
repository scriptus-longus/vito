#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>

#include "event.hpp"
#include "math.hpp"


class Object {
private:
  Vector2D position;
  std::string sprite;
  std::unordered_map<Event::KeyEvent, void(*)(Object&)> events;
  //std::unordered_map<Event, std::string> events;

public:
  Object(uint32_t x, uint32_t y, std::string str) : position(Vector2D(x,y)), sprite(str) {
    events = {};
  }

  Object(Vector2D position, std::string str) : position(position), sprite(str){
    events = {};
  } 

  void defineOnEvent(Event::KeyEvent event, void (*event_fun)(Object&)) {
    events.insert({event, event_fun});
  }

  auto getEvent(Event::KeyEvent event) {
    void (*ret)(Object&) = nullptr;
    auto event_it = events.find(event);

    if (event_it == events.end()) {
      return ret; 
    }
    ret = event_it->second;
    return ret;
  }


  uint32_t getX() {
    return position.y;
  }

  uint32_t getY() {
    return position.y;
  }

  Vector2D getPosition() {
    return position;
  }

  void setX(uint32_t x) {
    position.x = x;  
  }

  void setY(uint32_t y) {
    position.y = y;  
  }

  void setSprite(std::string sprite) {
    this->sprite = sprite;
  }

  virtual std::string str() {
    std::stringstream ss;
    ss << "Object at: (" << position.x << ", " << position.y << ")";
    return ss.str();
  }
  
  virtual std::string getText() {
    return sprite;
  }

};

class Scene {
private:
  std::unordered_map<Vector2D, Object&> objects;
 
public:
  Scene() {
    objects = {};
  }

  void addObject(Object& object) {
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

  void handleObjectEvent(uint32_t x, uint32_t y, Event::KeyEvent event) {
    //void (*event_fun)(Object&);
    Object& object = objects.at(Vector2D(x,y));

    auto event_fun = object.getEvent(event);

    if (event_fun != nullptr) {
      event_fun(object);
    }
  }

  std::string getCharAt(uint32_t x, uint32_t y) {
    return objects.at(Vector2D(x,y)).getText();
  }
};

class Camera : public Object {
private:
  uint32_t rows;
  uint32_t cols;
  uint32_t width;
  uint32_t height;

  sf::Font font;
  sf::Text text;

public:
  sf::RenderWindow window;

  Camera(uint32_t x, uint32_t y, uint32_t rows, uint32_t cols) : Object(x, y, ""), rows(rows), cols(cols) {
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

  void setPosition(uint32_t x, uint32_t y) {
    this->setX(x);
    this->setY(y);
  }

  void update(Scene& scene) {
    sf::Event sf_event;
    Event::KeyEvent event;

    while (window.pollEvent(sf_event)) {
      if (sf_event.type == sf::Event::Closed) {
        window.close();
      }
      event = Event::convertFromSFML(sf_event);
    }
    if (event == Event::KeyEvent::Unknown) {
      return;
    }

    
    auto event_fun = this->getEvent(event);

    if (event_fun != nullptr) {
      event_fun(*this);
    } 

    for (uint32_t y = 0; y < rows; y++) {
      for (uint32_t x = 0; x < cols; x++) {
        if (scene.isObjectAt(this->getX() + x, this->getY() + y)) {
          scene.handleObjectEvent(this->getX() + x, this->getY() + y, event);
        }
      }
    }
  }

  void render(Scene& scene) {
    window.clear();
    std::string str;

    str.reserve(rows*cols + rows);

    for (uint32_t y = 0; y < rows; y++) {
      for (uint32_t x = 0; x < cols; x++) {
        if (scene.isObjectAt(this->getX() + x, this->getY() + y)) {
          str += scene.getCharAt(this->getX() + x, this->getY() + y);
        } else {
          str += " ";
        } 
      }
      str += "\n";
    }

    text.setString(str);
    window.draw(text);
    window.display();
  } 

  std::string str() override {
    std::stringstream ss;
    ss << "Camera at: (" << this->getX() << ", " << this->getY() << ")"; 
    return ss.str();
  }
};



void PressedSpace(Object& object) {
  object.setSprite("*");
}

void ReleasedSpace(Object& object) {
  object.setSprite("i");
}

int main() {
  Scene scene; 
 
  Object object1(0, 0, "H");
  Object object2(8, 20, "i");
  Object object3(20, 7, "!");
  
  scene.addObject(object1);
  scene.addObject(object2);
  scene.addObject(object3);

  
  void (*press_space)(Object& object) = PressedSpace;
  void (*release_space)(Object& object) = ReleasedSpace;

  object2.defineOnEvent(Event::KeyEvent::PressedSpace, press_space);
  object2.defineOnEvent(Event::KeyEvent::ReleasedSpace, release_space);
  

  Camera camera(0,0, 40, 80);

  //camera.defineOnEvent(Event::KeyEvent::PressedKeyA, event_press_a);
  //camera.defineOnEvent(Event::KeyEvent::ReleasedKeyA, event_release_a);
  //camera.defineOnEvent(Event::KeyEvent::ReleasedSpace, space);


  while (camera.window.isOpen()) {
    camera.update(scene);

    camera.render(scene);
  }
  
  return 0;
}
