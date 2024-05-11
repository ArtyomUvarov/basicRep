#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
  Point    _center; // центр шара
  Velocity _velo;   // скорость шара
  Color   _color;   // цвет шара
  double  _rad;     // радиус шара
  double  _mass;    // масса шара
public:
  Ball( const Point &    center,
        const Velocity & velo,
        const Color  &   color,
              double     rad,
              double     mass );
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
};
