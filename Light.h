#pragma once

#include "geometry.h"

//—труктура определ€ет свет как точку p с интенсивностью i.
struct Light {
  Light( const Vec3f& p, const float& i) : position(p), intensity(i) {}
  Vec3f position;
  float intensity;
};

// ‘ункци€ возвращает вектор, отраженный вектору I относительно нормали N.
Vec3f reflect( const Vec3f & I, 
                const Vec3f & N ) {
    return I - N * 2.f * (I * N);
  }