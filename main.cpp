#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <chrono>
//#include <thread>

#include "event.hpp"
#include "math.hpp"
#include "scene.hpp"
#include "entity.hpp"
#include "object.hpp"
#include "camera.hpp"

void PressedSpace(Object& object) {
  //object.setSprite("+-+\n|*|\n+-+");
  //std::cout << "down" << std::endl;
  std:: cout << "Space" << std::endl;
  //object.setVelocity(Math::Vector2D(8,0));
}

void PressedA(Object& object) {
  //object.setSprite("+-+\n| |\n+-+");
  std::cout << "A" << std::endl;
  //object.setVelocity(Math:Vector2D(0,0));
}

int main() {
  //using namespace std::chrono_literals;

  Scene scene; 
 
  Entity player(0.0, 20.0, "a");
  //player.setVelocity(Math::Vector2D(20.0, 0.0));
  //player.setWidth(3);
  //player.setHeight(3);
  scene.addEntity(player);

  
  void (*press_space)(Object& object) = PressedSpace;
  void (*press_a)(Object& object) = PressedA;

  player.defineOnEvent(Event::KeyEvent::PressedSpace, press_space);
  player.defineOnEvent(Event::KeyEvent::PressedKeyA, press_a);
  

  Camera camera(0,0, 40, 80);

  auto start = std::chrono::high_resolution_clock::now();
  while (camera.window.isOpen()) {
    auto end = std::chrono::high_resolution_clock::now();
    float delta_t = (std::chrono::duration<float>(end - start)).count();
    start = end;
    //std::cout << delta_t << std::endl;
    scene.update(delta_t);

    camera.update(scene);

    camera.render(scene);
  }
  
  return 0;
}
