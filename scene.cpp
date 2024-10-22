#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "math.hpp"
#include "object.hpp"
#include "scene.hpp"
#include "event.hpp"

Scene::Scene() {}
  
void Scene::addObject(Object& object) {
  objects.emplace_back(object);
}

void Scene::addEntity(Entity& entity) {
  objects.emplace_back(entity);
  entities.emplace_back(entity);
}

void Scene::update(float delta_t) {
  for (auto entity_it : entities) {
    Entity& entity = entity_it.get();
 
    auto velocity = entity.getVelocity();
    double x = entity.getPosition().x;
    double y = entity.getPosition().y;

    if (!(velocity == Math::Vector2D(0,0))) {
      entity.setX(x + delta_t * velocity.x); 
      entity.setY(y + delta_t * velocity.y); 
    }
  }

}

std::vector<std::reference_wrapper<Object>> Scene::getObjects() {
  return objects;
}

void Scene::handleObjectEvent(Object& object, Event::KeyEvent event) {
 void(*event_fun)(Object&);
 event_fun = reinterpret_cast<void(*)(Object&)>(object.getEvent(event));

  if (event_fun != nullptr) {
    event_fun(object);
  }
}
