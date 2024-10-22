#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "math.hpp"
#include "object.hpp"
#include "entity.hpp"

Entity::Entity(float x, float y, std::string sprite) : Object(x, y, sprite), velocity(0,0) {}
 
void Entity::setVelocity(Math::Vector2D velocity) {
  this->velocity = velocity;
}
  
Math::Vector2D Entity::getVelocity() {
  return velocity;
}
 
std::string Entity::str() {
  std::stringstream ss;
  ss << "Entity at: (" << this->getX() << ", " << this->getY() << ")";
  return ss.str();
}
