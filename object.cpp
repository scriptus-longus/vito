#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "event.hpp"
#include "math.hpp"
#include "object.hpp"

Object::Object(float x, float y, std::string str) : position(Math::Vector2D(x,y)), sprite(str), W(1), H(1) {
  events = {};
}

Object::Object(Math::Vector2D position, std::string str) : position(position), sprite(str){
  events = {};
} 

void Object::defineOnEvent(Event::KeyEvent event, void (*event_fun)(Object&)) {
  events.insert({event, event_fun});
}

void* Object::getEvent(Event::KeyEvent event) {
  void (*ret)(Object&) = nullptr;
  auto event_it = events.find(event);

  if (event_it == events.end()) {
    return reinterpret_cast<void *>(ret); 
  }
  ret = event_it->second;
  return reinterpret_cast<void *>(ret);
}

bool Object::isInside(int32_t x, int32_t y, int32_t width, int32_t height) {
  Math::Vector2D top_left(position.getX(),     position.getY());
  Math::Vector2D top_right(position.getX() + W-1, position.getY());
  Math::Vector2D bottom_left(position.getX(),     position.getY() + H-1);
  Math::Vector2D bottom_right(position.getX() + W-1, position.getY() + H-1);

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
  
uint32_t Object::getWidth() {
  return W;
}

uint32_t Object::getHeight() {
  return H;
}

int32_t Object::getX() {
  return position.getX();
}

int32_t Object::getY() {
  return position.getY();
}

Math::Vector2D Object::getPosition() {
  return position;
}

void Object::setX(float x) {
  position.x = x;  
}

void Object::setY(float y) {
  position.y = y;  
}

void Object::setWidth(uint32_t W) {
  this->W = W;
}

void Object::setHeight(uint32_t H) {
  this->H = H;
}
  

void Object::setSprite(std::string sprite) {
  this->sprite = sprite;
}

std::string Object::str() {
  std::stringstream ss;
  ss << "Object at: (" << position.getX() << ", " << position.getY() << ")";
  return ss.str();
}
  
std::string Object::getText() {
  return sprite;
}

