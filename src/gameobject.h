#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "renderable.h"

class GameObject : public Renderable {
 public:
  virtual ~GameObject() { };  // hur �r det med virtuella destructors nu igen
  
  void Render() const override;

 protected:
  //n�n slags position
  
};

#endif