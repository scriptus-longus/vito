#include <SFML/Graphics.hpp>
#include "event.hpp"

Event::KeyEvent Event::convertFromSFML(sf::Event event) {
  if (event.type == sf::Event::KeyReleased) {
    if (event.key.code == sf::Keyboard::A) {
      return Event::KeyEvent::ReleasedKeyA;
    } else if (event.key.code == sf::Keyboard::B) {
      return Event::KeyEvent::ReleasedKeyB;
    } else if (event.key.code == sf::Keyboard::C) {
      return Event::KeyEvent::ReleasedKeyC;
    } else if (event.key.code == sf::Keyboard::D) {
      return Event::KeyEvent::ReleasedKeyD;
    } else if (event.key.code == sf::Keyboard::E) {
      return Event::KeyEvent::ReleasedKeyE;
    } else if (event.key.code == sf::Keyboard::F) {
      return Event::KeyEvent::ReleasedKeyF;
    } else if (event.key.code == sf::Keyboard::G) {
      return Event::KeyEvent::ReleasedKeyG;
    } else if (event.key.code == sf::Keyboard::H) {
      return Event::KeyEvent::ReleasedKeyH;
    } else if (event.key.code == sf::Keyboard::I) {
      return Event::KeyEvent::ReleasedKeyI;
    } else if (event.key.code == sf::Keyboard::J) {
      return Event::KeyEvent::ReleasedKeyJ;
    } else if (event.key.code == sf::Keyboard::K) {
      return Event::KeyEvent::ReleasedKeyK;
    } else if (event.key.code == sf::Keyboard::L) {
      return Event::KeyEvent::ReleasedKeyL;
    } else if (event.key.code == sf::Keyboard::M) {
      return Event::KeyEvent::ReleasedKeyM;
    } else if (event.key.code == sf::Keyboard::N) {
      return Event::KeyEvent::ReleasedKeyN;
    } else if (event.key.code == sf::Keyboard::O) {
      return Event::KeyEvent::ReleasedKeyO;
    } else if (event.key.code == sf::Keyboard::P) {
      return Event::KeyEvent::ReleasedKeyP;
    } else if (event.key.code == sf::Keyboard::Q) {
      return Event::KeyEvent::ReleasedKeyQ;
    } else if (event.key.code == sf::Keyboard::R) {
      return Event::KeyEvent::ReleasedKeyR;
    } else if (event.key.code == sf::Keyboard::S) {
      return Event::KeyEvent::ReleasedKeyS;
    } else if (event.key.code == sf::Keyboard::T) {
      return Event::KeyEvent::ReleasedKeyT;
    } else if (event.key.code == sf::Keyboard::U) {
      return Event::KeyEvent::ReleasedKeyU;
    } else if (event.key.code == sf::Keyboard::V) {
      return Event::KeyEvent::ReleasedKeyV;
    } else if (event.key.code == sf::Keyboard::W) {
      return Event::KeyEvent::ReleasedKeyW;
    } else if (event.key.code == sf::Keyboard::X) {
      return Event::KeyEvent::ReleasedKeyX;
    } else if (event.key.code == sf::Keyboard::Y) {
      return Event::KeyEvent::ReleasedKeyY;
    } else if (event.key.code == sf::Keyboard::Z) {
      return Event::KeyEvent::ReleasedKeyZ;


    } else if (event.key.code == sf::Keyboard::Space) {
      return Event::KeyEvent::ReleasedSpace;
    } else if (event.key.code == sf::Keyboard::Right) {
      return Event::KeyEvent::ReleasedRight;
    } else if (event.key.code == sf::Keyboard::Left) {
      return Event::KeyEvent::ReleasedLeft;
    } else if (event.key.code == sf::Keyboard::Up) {
      return Event::KeyEvent::ReleasedRight;
    } else if (event.key.code == sf::Keyboard::Down) {
      return Event::KeyEvent::ReleasedRight;
    } else {
      return Event::KeyEvent::Unknown;
    }

  } else if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::A) {
      return Event::KeyEvent::PressedKeyA;
    } else if (event.key.code == sf::Keyboard::B) {
      return Event::KeyEvent::PressedKeyB;
    } else if (event.key.code == sf::Keyboard::C) {
      return Event::KeyEvent::PressedKeyC;
    } else if (event.key.code == sf::Keyboard::D) {
      return Event::KeyEvent::PressedKeyD;
    } else if (event.key.code == sf::Keyboard::E) {
      return Event::KeyEvent::PressedKeyE;
    } else if (event.key.code == sf::Keyboard::F) {
      return Event::KeyEvent::PressedKeyF;
    } else if (event.key.code == sf::Keyboard::G) {
      return Event::KeyEvent::PressedKeyG;
    } else if (event.key.code == sf::Keyboard::H) {
      return Event::KeyEvent::PressedKeyH;
    } else if (event.key.code == sf::Keyboard::I) {
      return Event::KeyEvent::PressedKeyI;
    } else if (event.key.code == sf::Keyboard::J) {
      return Event::KeyEvent::PressedKeyJ;
    } else if (event.key.code == sf::Keyboard::K) {
      return Event::KeyEvent::PressedKeyK;
    } else if (event.key.code == sf::Keyboard::L) {
      return Event::KeyEvent::PressedKeyL;
    } else if (event.key.code == sf::Keyboard::M) {
      return Event::KeyEvent::PressedKeyM;
    } else if (event.key.code == sf::Keyboard::N) {
      return Event::KeyEvent::PressedKeyN;
    } else if (event.key.code == sf::Keyboard::O) {
      return Event::KeyEvent::PressedKeyO;
    } else if (event.key.code == sf::Keyboard::P) {
      return Event::KeyEvent::PressedKeyP;
    } else if (event.key.code == sf::Keyboard::Q) {
      return Event::KeyEvent::PressedKeyQ;
    } else if (event.key.code == sf::Keyboard::R) {
      return Event::KeyEvent::PressedKeyR;
    } else if (event.key.code == sf::Keyboard::S) {
      return Event::KeyEvent::PressedKeyS;
    } else if (event.key.code == sf::Keyboard::T) {
      return Event::KeyEvent::PressedKeyT;
    } else if (event.key.code == sf::Keyboard::U) {
      return Event::KeyEvent::PressedKeyU;
    } else if (event.key.code == sf::Keyboard::V) {
      return Event::KeyEvent::PressedKeyV;
    } else if (event.key.code == sf::Keyboard::W) {
      return Event::KeyEvent::PressedKeyW;
    } else if (event.key.code == sf::Keyboard::X) {
      return Event::KeyEvent::PressedKeyX;
    } else if (event.key.code == sf::Keyboard::Y) {
      return Event::KeyEvent::PressedKeyY;
    } else if (event.key.code == sf::Keyboard::Z) {
      return Event::KeyEvent::PressedKeyZ;

    } else if (event.key.code == sf::Keyboard::Space) {
      return Event::KeyEvent::PressedSpace;
    } else if (event.key.code == sf::Keyboard::Right) {
      return Event::KeyEvent::PressedRight;
    } else if (event.key.code == sf::Keyboard::Left) {
      return Event::KeyEvent::PressedLeft;
    } else if (event.key.code == sf::Keyboard::Up) {
      return Event::KeyEvent::PressedRight;
    } else if (event.key.code == sf::Keyboard::Down) {
      return Event::KeyEvent::PressedRight;
    } else {
      return Event::KeyEvent::Unknown;
    }

  } else {
    return Event::KeyEvent::Unknown;
  }
    
}
