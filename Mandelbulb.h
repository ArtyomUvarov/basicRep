#pragma once

#include "geometry.h"

// Структура содержит параметры для трассировки множества Мандельбулба.
// 1. Адаптиваня окраска по длине производной (derive_color)
// 2. Чиcло итараций для определения попадания точки во множество (mandel_iter)
// 3. Степень комплексного полинома (mandel_pow)
// 4. Число лучей по горизонтали (width)
// 5. Число лучей по вертикали (height)
// 6. Количество потоков для трассировки (threads_count)
// 7. Количество рандомных нормалей в точке на поверхности (max_iter)
// 8. Позиция камеры (orig)
// 9. Поворот камеры по оси X
// 10. Поворот камеры по оси Y
struct MandelParameters {
  MandelParameters( bool   _derive_color,
                    size_t _mandel_iter,
                    size_t _mandel_pow,
                    float  _mandel_dist,
                    size_t _width,
                    size_t _height,
                    size_t _threads_count,
                    size_t _max_iter,
                    Vec3f  _orig,
                    float  _rot_x,
                    float  _rot_z )
    : derive_color  ( _derive_color  ),
      mandel_iter   ( _mandel_iter   ),
      mandel_pow    ( _mandel_pow    ),
      mandel_dist   ( _mandel_dist   ),
      width         ( _width         ),
      height        ( _height        ),
      threads_count ( _threads_count ),
      max_iter      ( _max_iter      ),
      orig          ( _orig          ),
      rot_x         ( _rot_x         ),
      rot_z         ( _rot_z         )
  {}
  bool   derive_color;
  size_t mandel_iter;
  size_t mandel_pow;
  float  mandel_dist;
  size_t width;
  size_t height;
  size_t threads_count;
  size_t max_iter;
  Vec3f  orig;
  float  rot_x;
  float  rot_z;
};


// Структура определяет кватернион (точнее его проекцию) в виде вектора coor в трехмерном пространстве
struct HyperComplex {
  HyperComplex( const Vec3f & coor ) : coord(coor) {}
  HyperComplex() : coord(0, 0, 0) {}
  HyperComplex & Pow( size_t n ) {
  float & x = coord[0];
  float & y = coord[1];
  float & z = coord[2];
  float r = std::sqrtf( x * x + y * y + z * z );
  float teta = std::atan2( y , x );  
  float r1 = std::sqrtf( x * x + y * y );
  float psi = std::atan2( z , r1 );
  float r_n = std::pow( r, n );
  float n_teta = n * teta;
  float n_psi = n * psi;
  float cos_n_teta = std::cos( n_teta );
  float cos_n_psi = std::cos( n_psi );
  float sin_n_teta = std::sin( n_teta );
  float sin_n_psi = std::sin( n_psi );   
  x = r_n * cos_n_teta * cos_n_psi;
  y = r_n * sin_n_teta * cos_n_psi;
  z = r_n * sin_n_psi;  
  return *this;
  }

  HyperComplex &  operator+( const HyperComplex & second ){
    coord = coord + second.coord;
    return *this;
  }

  Vec3f coord;

};

// Функция вычисляет производную для орбиты точки множества Мандельброта
float mandelDeriv( const HyperComplex & complex,
                        size_t          n, 
                        float           dr ) {
  return n * std::pow( complex.coord.norm(), n - 1 ) * dr + 1.0;
}

// Функция вычисляет цвет точки на множестве по длине производной ее орбиты dr/
Vec3f MandelbulColor( float dr ) 
{
  float c = 1.5 * std::powf( dr, 1.0/20.0 );
  Vec3f color = Vec3f( std::sin(2 * c) + 0.0, std::sin(2 * c) + 1.0, std::sin(2 * c) + 1.0 );
  color.x += 0.5;
  color.y += 0.5;
  color.z += 0.5;

return color * 0.5;
}

// Функция определяет принадлежит ли точка compl множеству. При этом возвращается расстояние до множества dist и цвет точки orb.
bool Mandel( const MandelParameters & param,
             const HyperComplex &     complex,
                   float &            dist,
                   Vec3f &            orb ) {
  bool additColor = param.derive_color;
  size_t mandel_iter = param.mandel_iter;
  float mandel_dist = param.mandel_dist;
  size_t mandel_pow = param.mandel_pow;
  bool inSet = true;
  HyperComplex startPt;
  float dr = 1;
  float r = 0;

  for( size_t i = 0; i < mandel_iter; ++i ) {
    r = startPt.coord.norm();
    if ( r >= mandel_dist ) {
        inSet = false;
        break;
      }
    dr = mandelDeriv( startPt, mandel_pow, dr );
    startPt = startPt.Pow(mandel_pow) + complex;
  }

  float r1 = startPt.coord.norm();

   dist =  0.5*log( r1 ) * r1 / dr;
   
  if ( additColor )
    orb = MandelbulColor( dr );

  return inSet;
};
