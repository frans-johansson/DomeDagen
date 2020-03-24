#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

#include "gameobject.hpp"
//#include "sgct/sgct.h"

class Player : public GameObject {
 public:
  Player() = delete;
  Player(const std::string& name /* position, ... fler argument */);
  virtual ~Player();

  // Players should be unique
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;

  // accessors
  int points() const { return mPoints; };
  bool is_alive() const { return mIsAlive; };
  const std::string& name() const { return mName; };

 private:
  // l�gg till n�t id eller ip typ eller b�da

  int mPoints;
  bool mIsAlive;
  const std::string mName;  // vad h�nder om namn ej �r unikt? b�r kanske
                            // hanteras i webbservern
};

#endif