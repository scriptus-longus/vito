#pragma once
#include <cstdint>

#include <unordered_map>

class Vector2D {
public:
  uint32_t x;
  uint32_t y;
  
  Vector2D(uint32_t, uint32_t);

  bool operator==(const Vector2D& other) { 
    return other.x == x && other.y == y;
  }

  friend bool operator==(const Vector2D& lhs, const Vector2D& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }
};



namespace std {
  template <>
  struct hash<Vector2D> {
    size_t operator()(const Vector2D& key) const {
      return ((hash<uint32_t>()(key.x) ^ (hash<uint32_t>()(key.y) << 1)) >> 1);
    }
  };
}
