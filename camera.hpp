#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "event.hpp"
#include "math.hpp"
#include "object.hpp"
#include "scene.hpp"

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

  Camera(int32_t, int32_t, uint32_t, uint32_t); //: Object(x, y, ""), rows(rows), cols(cols);

  void setPosition(int32_t, int32_t);

  void update(Scene&);


  void render(Scene&);

  std::string str() override;
};
