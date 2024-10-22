#pragma once
#include <vector>
#include <string>

#include "math.hpp"
#include "object.hpp"

class Entity : public Object {
private:
  Math::Vector2D velocity;

public:
  Entity(float, float, std::string);
 
  void setVelocity(Math::Vector2D);

  Math::Vector2D getVelocity();
 
  std::string str() override;
};
