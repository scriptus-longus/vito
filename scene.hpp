#pragma once
#include <vector>
#include <string>

#include "math.hpp"
#include "object.hpp"
#include "entity.hpp"

class Scene {
private:
  std::vector<std::reference_wrapper<Object>> objects;
  std::vector<std::reference_wrapper<Entity>> entities;
 
public:
  Scene(); //{}
  
  void addObject(Object&);

  void addEntity(Entity&);

  void update(float);

  std::vector<std::reference_wrapper<Object>> getObjects();

  void handleObjectEvent(Object&, Event::KeyEvent);
};

