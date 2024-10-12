#pragma once
namespace Event {
  enum KeyEvent {
    Unknown,
    PressedKeyA, PressedKeyB, PressedKeyC, PressedKeyD,
    PressedKeyE, PressedKeyF, PressedKeyG, PressedKeyH,
    PressedKeyI, PressedKeyJ, PressedKeyK, PressedKeyL,
    PressedKeyM, PressedKeyN, PressedKeyO, PressedKeyP, 
    PressedKeyQ, PressedKeyR, PressedKeyS, PressedKeyT, 
    PressedKeyU, PressedKeyV, PressedKeyW, PressedKeyX, 
    PressedKeyY, PressedKeyZ,

    PressedSpace,
    PressedLeft,
    PressedRight,
    PressedUp,
    PressedDown,

    ReleasedKeyA, ReleasedKeyB, ReleasedKeyC, ReleasedKeyD,
    ReleasedKeyE, ReleasedKeyF, ReleasedKeyG, ReleasedKeyH,
    ReleasedKeyI, ReleasedKeyJ, ReleasedKeyK, ReleasedKeyL,
    ReleasedKeyM, ReleasedKeyN, ReleasedKeyO, ReleasedKeyP, 
    ReleasedKeyQ, ReleasedKeyR, ReleasedKeyS, ReleasedKeyT, 
    ReleasedKeyU, ReleasedKeyV, ReleasedKeyW, ReleasedKeyX, 
    ReleasedKeyY, ReleasedKeyZ,

    ReleasedSpace,
    ReleasedLeft,
    ReleasedRight,
    ReleasedUp,
    ReleasedDown
  };

  KeyEvent convertFromSFML(sf::Event);
} 
