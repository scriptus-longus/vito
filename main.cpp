#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>

#include "event.hpp"
#include "math.hpp"


class Object {
private:
  Math::Vector2D position;
  std::string sprite;
  uint32_t W;
  uint32_t H;

  std::unordered_map<Event::KeyEvent, void(*)(Object&)> events;

public:

  Object(int32_t x, int32_t y, std::string str) : position(Math::Vector2D(x,y)), sprite(str), W(1), H(1) {
    events = {};
  }

  Object(Math::Vector2D position, std::string str) : position(position), sprite(str){
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

  bool isInside(int32_t x, int32_t y, int32_t width, int32_t height) {
    Math::Vector2D top_left(position.x,     position.y);
    Math::Vector2D top_right(position.x + W-1, position.y);
    Math::Vector2D bottom_left(position.x,     position.y + H-1);
    Math::Vector2D bottom_right(position.x + W-1, position.y + H-1);

    Math::Vector2D frame_top(x, y);
    Math::Vector2D frame_bottom(x + width, y + height);

    if (Math::isVectorInside(top_left,     frame_top, frame_bottom) ||
        Math::isVectorInside(top_right,    frame_top, frame_bottom) ||
        Math::isVectorInside(bottom_left,  frame_top, frame_bottom) ||
        Math::isVectorInside(bottom_right, frame_top, frame_bottom)) {
      return true;
    }
  
    return false;
  }

  uint32_t getWidth() {
    return W;
  }

  uint32_t getHeight() {
    return H;
  }

  int32_t getX() {
    return position.x;
  }

  int32_t getY() {
    return position.y;
  }

  Math::Vector2D getPosition() {
    return position;
  }

  void setX(int32_t x) {
    position.x = x;  
  }

  void setY(int32_t y) {
    position.y = y;  
  }

  void setWidth(uint32_t W) {
    this->W = W;
  }

  void setHeight(uint32_t H) {
    this->H = H;
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
  std::vector<std::reference_wrapper<Object>> objects;
 
public:
  Scene() {}
  
  
  void addObject(Object& object) {
    objects.emplace_back(object);
  }

  std::vector<std::reference_wrapper<Object>> getObjects() {
    return objects;
  }

  void handleObjectEvent(Object& object, Event::KeyEvent event) {
    auto event_fun = object.getEvent(event);

    if (event_fun != nullptr) {
      event_fun(object);
    }
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

  Camera(int32_t x, int32_t y, uint32_t rows, uint32_t cols) : Object(x, y, ""), rows(rows), cols(cols) {
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

  void setPosition(int32_t x, int32_t y) {
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

    for (auto object_it: scene.getObjects()) {
      Object& object = object_it.get();
      if (object.isInside(this->getX(), this->getY(), cols, rows)) {
        scene.handleObjectEvent(object, event);
      }
    }
  }

  void render(Scene& scene) {
    window.clear();
    auto row = std::string(cols, ' ') + "\n";
    std::string displayStr;

    for (uint32_t i = 0; i < rows; i++) {
      displayStr += row;
    }

    for (auto object_it: scene.getObjects()) {
      Object& object = object_it.get();

      if (object.isInside(this->getX(), this->getY(), cols, rows)) {
        uint32_t obj_W = object.getWidth();
        uint32_t obj_H = object.getHeight();

        auto cam_X = object.getX() - this->getX();
        auto cam_Y = object.getY() - this->getY();

        if (obj_W == 1 && obj_H == 1) {
          displayStr[cam_Y * cols + cam_Y + cam_X] = object.getText().c_str()[0];
        } else {
          Math::Vector2D rel_position(cam_X, cam_Y);
          Math::Vector2D frame_top(0,0);
          Math::Vector2D frame_bottom(cols, rows);

          for (const auto current_char : object.getText()) {
            if (!Math::isVectorInside(rel_position, 
                                     Math::Vector2D(0,0), 
                                     Math::Vector2D(cols, rows))) {

              if (current_char != '\n') {
                rel_position.x++;
              } else {
                rel_position.y++;
                rel_position.x = cam_X;
              }

              continue;
            }

            if (current_char != '\n') {
              displayStr[rel_position.y * cols + rel_position.y  + rel_position.x] = current_char;
              rel_position.x++;
            } else {
              rel_position.y++;
              rel_position.x = cam_X;
            }
          }
        }
      }
    }

    text.setString(displayStr);
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
  object.setSprite("+-+\n|*|\n+-+");
}

void ReleasedSpace(Object& object) {
  object.setSprite("+-+\n| |\n+-+");
}

int main() {
  Scene scene; 
 
  Object object1(20, 20, "+-+\n| |\n+-+");

  object1.setWidth(3);
  object1.setHeight(3);

  scene.addObject(object1);

  
  void (*press_space)(Object& object) = PressedSpace;
  void (*release_space)(Object& object) = ReleasedSpace;

  object1.defineOnEvent(Event::KeyEvent::PressedSpace, press_space);
  object1.defineOnEvent(Event::KeyEvent::ReleasedSpace, release_space);
  

  Camera camera(-2,-2, 40, 80);

  while (camera.window.isOpen()) {
    camera.update(scene);

    camera.render(scene);
  }
  
  return 0;
}
