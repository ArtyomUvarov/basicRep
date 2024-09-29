#pragma once

#include"Shader.h"

bool DERIVE_COLOR = false;
size_t MANDEL_ITER = 6;
size_t MANDEL_POW = 8;
float  MANDEL_DIST = 2;
size_t WIDTH = 1920;
size_t HEIGHT = 1080;
size_t THREADS_COUNT = 128;
size_t MAX_ITER = 1;
Vec3f ORIG = Vec3f( 0, 1.6, 1.6 );
float ROT_X = 45.0;
float ROT_Z = 0.0;



void Menu() {
  std::cout << "1.  Width =  "<< WIDTH << "\n";
  std::cout << "2.  Height = " << HEIGHT << "\n";
  std::cout << "3.  Origin = " << ORIG << "\n";
  std::cout << "4.  X rotation = " << ROT_X << "\n";
  std::cout << "5.  Z rotation = " << ROT_Z << "\n";
  std::cout << "6.  Max random normal = " << MAX_ITER << "\n";
  std::cout << "6.  Threads count = " << THREADS_COUNT << "\n";
  std::cout << "7.  Advanced color = " << DERIVE_COLOR << "\n";
  std::cout << "8.  Mandelbulb iteration = " << MANDEL_ITER << "\n";
  std::cout << "9.  Mandelbulb degree =" << MANDEL_POW << "\n";
  std::cout << "10. Mandelbulb distance = " << MANDEL_DIST << "\n";
  std::cout << "Select menu item" << "\n";
  size_t item = 0;
  bool render = false;

  while ( render == false ) {
    std::cin>> item;
  
    switch ( item ) {
    case 1:{ 
      std::cout << "Width =  ";
      std::cin >> WIDTH;
      break;
    }
    case 2: {
      std::cout << "Height =  ";
      std::cin >> HEIGHT;
      break;
    }
    case 3: {
      std::cout << "Origin =  ";
      std::cin >> ORIG;
      break;
    }
    case 4: {
      std::cout << "X rotation  =  ";
      std::cin >> ROT_X;
      break;
    }
    case 5: {
      std::cout << "Z rotation =  ";
      std::cin >> ROT_Z;
      break;
    }
    case 6: {
      std::cout << "Max random normal =  ";
      std::cin >> MAX_ITER;
      break;
    }
    case 7: {
      std::cout << "Advanced color =  ";
      std::cin >> DERIVE_COLOR;
      break;
    }
    case 8: {
      std::cout << "Mandelbulb iteration =  ";
      std::cin >> MANDEL_ITER;
      break;
    }
    case 9: {
      std::cout << "Mandelbulb degree =  ";
      std::cin >> MANDEL_POW;
      break;
    }
    case 10: {
      std::cout << "Mandelbulb distance =  ";
      std::cin >> MANDEL_DIST;
      break;
    }
    default:
      break;
    }
    char yes;
    std::cout << "Render ? (Y/N)";
    std::cin >> yes;
    if ( yes == 'y' )
      render = true;
  }  
}