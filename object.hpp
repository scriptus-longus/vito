#pragma once
#include <vector>
#include <string>
#include <unordered_map>

#include "math.hpp"
#include "event.hpp"

//typedef (void(*)(Object&)) eventfunc_t;
//typedef void (*eventfunc_t)(Object&);
//typedef eventfunc_t (*eventfuncptr_t)();

class Object {
private:
  Math::Vector2D position;
  std::string sprite;
  uint32_t W;
  uint32_t H;

  
  std::unordered_map<Event::KeyEvent, void(*)(Object&)> events;
  //void(*collision_f)(Entity&);

public:

  Object(float, float, std::string); //: position(Math::Vector2D(x,y)), sprite(str), W(1), H(1);

  Object(Math::Vector2D, std::string); // : position(position), sprite(str);

  void defineOnEvent(Event::KeyEvent, void (*)(Object&));

  //auto getEvent(Event::KeyEvent);
  void* getEvent(Event::KeyEvent);

  bool isInside(int32_t, int32_t, int32_t, int32_t);

  //auto getCollisionFunction() {
  //  return collision_f;
  //} 
  
  uint32_t getWidth();

  uint32_t getHeight();

  int32_t getX();

  int32_t getY();

  Math::Vector2D getPosition();

  void setX(float);

  void setY(float);

  void setWidth(uint32_t);

  void setHeight(uint32_t);
  

  void setSprite(std::string);

  virtual std::string str();
  
  virtual std::string getText();
};


//eventfunc_t Object::getEvent(Event::KeyEvent);
