#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "math.hpp"
#include "event.hpp"
#include "object.hpp"
#include "camera.hpp"
#include "scene.hpp"

Camera::Camera(int32_t x, int32_t y, uint32_t rows, uint32_t cols) : Object(x, y, ""), rows(rows), cols(cols) {
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

void Camera::setPosition(int32_t x, int32_t y) {
  this->setX(x);
  this->setY(y);
}

void Camera::update(Scene& scene) {
  sf::Event sf_event;
  std::vector<Event::KeyEvent> events;

  while (window.pollEvent(sf_event)) {
    if (sf_event.type == sf::Event::Closed) {
      window.close();
    }
    events.emplace_back(Event::convertFromSFML(sf_event));
  }
  if (events.size() == 0) {
    return;
  }

  for (const auto& event : events) {
    auto event_fun = reinterpret_cast<void(*)(Object&)>(this->getEvent(event));
    if (event_fun != nullptr) {
      event_fun(*this);
    } 
  } 


  for (auto object_it: scene.getObjects()) {
    Object& object = object_it.get();
    if (object.isInside(this->getX(), this->getY(), cols, rows)) {
      for (const auto& event : events) {
        scene.handleObjectEvent(object, event);
      }
    }
  }
}

void Camera::render(Scene& scene) {
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
            displayStr[rel_position.getY() * cols + rel_position.getY()  + rel_position.getX()] = current_char;
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

std::string Camera::str() {
  std::stringstream ss;
  ss << "Camera at: (" << this->getX() << ", " << this->getY() << ")"; 
  return ss.str();
}
