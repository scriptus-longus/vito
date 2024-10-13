#include <sstream>
#include "math.hpp"

Math::Vector2D::Vector2D(int32_t x, int32_t y) : x(x), y(y) {}

std::string Math::Vector2D::str() {
  std::stringstream ss;
  ss << "Vector2d(" << x << ", " << y << ")" << std::endl;
  return ss.str();
}

bool Math::isVectorInside(const Vector2D& X, const Vector2D& ltop, const Vector2D& rbot) {
  if (X.x >= ltop.x && X.x < rbot.x && X.y >= ltop.y && X.y < rbot.y) {
    return true;
  }
  return false; 
} 
