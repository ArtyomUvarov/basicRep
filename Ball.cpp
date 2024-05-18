#include "Ball.hpp"
#include <cmath>

Ball::Ball( const Point &    center, 
            const Velocity & velo, 
            const Color &    color,
                  double     rad, 
                  double     mass )
  : _center( center ),
    _velo  ( velo   ),
    _color ( color  ),
    _rad   ( rad    ),
    _mass  ( mass   )
  
{
}

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    // TODO: место для доработки
  _velo = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    // TODO: место для доработки
    return _velo;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    // TODO: место для доработки
  painter.draw( _center, _rad, _color );
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    // TODO: место для доработки
  _center = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    // TODO: место для доработки
    return _center;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    // TODO: место для доработки
    return _rad;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    // TODO: место для доработки
    return _mass;
}


std::istream& operator>>(std::istream& stream, Point& point) {
  stream >> point.x >> point.y;
  return stream;
}

std::istream& operator>>(std::istream& stream, Velocity& velo) {
  Point pt;
  stream >> pt;
  velo.setVector( pt );
  return stream;
}

std::istream& operator>>(std::istream& stream, Color& color) {
  stream >> color.r>> color.g >> color.b;
  return stream;
}