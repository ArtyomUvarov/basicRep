#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
  Point    _center; // ����� ����
  Velocity _velo;   // �������� ����
  Color   _color;   // ���� ����
  double  _rad;     // ������ ����
  double  _mass;    // ����� ����
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
