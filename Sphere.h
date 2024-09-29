#pragma once

#include "Mandelbulb.h"
#include "Material.h"

// ��������� ���������� ����� ����� ����� center � ������ radius. ����� ����� ����� �������� material  
struct Sphere {
  Vec3f center;
  float radius;
  Material material;
  Sphere( const Vec3f & c,
          const float & r) 
    : center  ( c ), 
      radius  ( r ), 
      material(  ) 
  {}
  Sphere( const Vec3f &    c,
          const float &    r, 
          const Material & m ) 
    : center ( c ), 
      radius ( r ),
     material( m ) 
  {}

  //������� ���������� ���������� �� ��� dir ��������� ������������ ������ ����� �, ���� ����������, �� ������������ �������� t0 �� ���� � ���� (�� ����� �����������)
  bool ray_intersect( const MandelParameters & param,    
                      const Vec3f &            dir, 
                            float &            t0,
                            Vec3f &            color ) const {
    const Vec3f & orig = param.orig;
    bool    additcolor = param.derive_color;
    Vec3f L = center - orig;
    float tca = L * dir;
    float d2 = L * L - tca * tca;

    if ( d2 > radius * radius ) 
      return false;

    float thc = sqrtf( radius * radius - d2 );
    t0 = tca - thc;
    float t1 = tca + thc;
    bool inSpere = true;

    if ( t0 < 0 ) {
      t0 = t1;
      inSpere = false;
    }

    if ( t0 < 0 ) 
      return false;
      
    if ( !inSpere )
      t0=0;
    
    Vec3f testPt = orig + dir * t0; 
    bool inMand = false;  
    float dist = 0;
    Vec3f deriveColor;

    for ( size_t i = 0; i <= 200; ++i ) {
      if ( ::Mandel(param, HyperComplex(testPt), dist, deriveColor) ) {
        inMand = true;
        color = deriveColor;
        break;
      }
      else {
        t0 += dist;
        testPt = orig + dir * t0;
        if ( t0 >= t1 ) 
          break;   
      }
    }
      
    return inMand;
  } 
};
