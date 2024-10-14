#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>

namespace Math {
class Vector2D {
public:
  float x;
  float y;
  
  Vector2D(float, float);

  std::string str();

  int32_t getX() const;

  int32_t getY() const;

  bool operator==(const Vector2D& other) { 
    return other.x == x && other.y == y;
  }

  friend bool operator==(const Vector2D& lhs, const Vector2D& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }
};

  bool isVectorInside(const Vector2D&, const Vector2D&, const Vector2D&);
}


namespace std {
  template <>
  struct hash<Math::Vector2D> {
    size_t operator()(const Math::Vector2D& key) const {
      return ((hash<int32_t>()(key.x) ^ (hash<int32_t>()(key.y) << 1)) >> 1);
    }
  };
}
