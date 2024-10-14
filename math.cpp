#include <sstream>
#include "math.hpp"

Math::Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

std::string Math::Vector2D::str() {
  std::stringstream ss;
  ss << "Vector2d(" << x << ", " << y << ")";
  return ss.str();
}

int32_t Math::Vector2D::getX() const {
  return static_cast<int32_t>(x);
}

int32_t Math::Vector2D::getY() const {
  return static_cast<int32_t>(y);
}

bool Math::isVectorInside(const Vector2D& X, const Vector2D& ltop, const Vector2D& rbot) {
  if (X.getX() >= ltop.getX() && X.getX() < rbot.getX() && X.getY() >= ltop.getY() && X.getY() < rbot.getY()) {
    return true;
  }
  return false; 
} 
