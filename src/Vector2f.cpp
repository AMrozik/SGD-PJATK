#include "Vector2f.hpp"

Vector2f::Vector2f(double x, double y){
  this->x = x;
  this->y = y;
}

void Vector2f::reverse_X(){
  this->x = -this->x;
}

void Vector2f::reverse_Y(){
  this->y = -this->y;
}
