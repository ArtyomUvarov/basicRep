
#include <chrono>
#include <thread>
#include"Menu.h"


int main() {
  Menu();
  MandelParameters param( DERIVE_COLOR, MANDEL_ITER, MANDEL_POW, MANDEL_DIST, WIDTH, HEIGHT, THREADS_COUNT, MAX_ITER, ORIG, ROT_X * M_PI / 180.0, ROT_Z * M_PI / 180.0 );
  Material  ivory( 1.0, Vec4f(0.6, 0.3, 0.1, 0.0), Vec3f(0.4, 0.4, 0.3), 50.);
  Sphere sphere = Sphere( Vec3f(0, 0, 0), 2, ivory );
  std::vector<Light>  lights;
  lights.push_back( Light(Vec3f(-10, 10, 20), 1.6) );
  lights.push_back( Light(Vec3f(30, 50, -25), 1.8) );
  lights.push_back( Light(Vec3f(10, 10, 30), 1.7) );
  
  buffer framebuffer( WIDTH * HEIGHT );
  buffer pointsbuffer( WIDTH * HEIGHT );
  buffer colorbuffer( WIDTH * HEIGHT );
  const int fov = M_PI / 2;
  float coof1 = tan(fov / 2.);
  float coof2 = coof1 * WIDTH / (float)HEIGHT;
  float angleX = ROT_X * M_PI / 180.0;
  float angleZ = ROT_Z * M_PI / 180.0;
  size_t  ind = 0;
 
  auto start = std::chrono::high_resolution_clock::now();
  size_t common = 0;
  std::mutex mtx;

  std::cout <<"Calculate Points" << " \n";
  std::vector<std::thread> threads1;

  for ( size_t i = 1; i <= THREADS_COUNT; ++i )
    threads1.emplace_back( render, param, sphere, lights, coof1, coof2, i, false, std::ref(pointsbuffer), std::ref(framebuffer), std::ref(colorbuffer), std::ref(common), std::ref(mtx) );

  for ( auto & thread : threads1 )
    thread.join();

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed_s = std::chrono::duration_cast<std::chrono::seconds>(end - start);
  std::cout << " \n" << "Build time is " << elapsed_s.count() << " seconds" << " \n";

  start = std::chrono::high_resolution_clock::now();
  std::cout << "Calculate normals" << " \n";
  std::vector<std::thread> threads2;

  common = 0;
  for ( size_t i = 1; i <= THREADS_COUNT; ++i )
    threads2.emplace_back(render, param,  sphere, lights,coof1, coof2, i, true, std::ref(pointsbuffer), std::ref(framebuffer), std::ref(colorbuffer), std::ref(common), std::ref(mtx) );

  for ( auto & thread : threads2 )
    thread.join();

  end = std::chrono::high_resolution_clock::now();
  elapsed_s = std::chrono::duration_cast<std::chrono::seconds>( end - start );
  std::cout << " \n" << "Build time is " << elapsed_s.count() << " seconds" << " \n";
  unsigned char * img = ::FromBufferToChar( framebuffer );
  stbi_write_jpg( "Mandelbulb.jpg", WIDTH, HEIGHT, 3, img, 100 );
  std::cout <<"Resalt saved in file Mandelbulb.jpg ";
  return 0;
}

