#pragma once

#include "Sphere.h"
#include "Light.h"
#include <mutex>
#include "stb_image_write.h"

typedef std::vector<Vec3f> buffer;

// Функция определяет пересекает ли луч в направлении dir множество Мандельброта и возвращает точку попадания hit, приближенную нормаль N, вычисленную по соседним точкам множества,
// а также материал точки соударения.

bool scene_intersect( const MandelParameters & param,
                      const Vec3f &            dir,        
                      const Sphere &           sphere,
                      const buffer &           pointsbuffer,
                            buffer &           colorbuffer,
                            size_t             i,
                            size_t             j,
                            bool               isShadow,
                            bool               calcNormals,
                            Vec3f &            hit, 
                            Vec3f &            N, 
                            Material &         material )
{
  float spheres_dist = 10000;
  size_t width = param.width;
  size_t height = param.height;
  const Vec3f & orig = param.orig;
  bool  additColor = param.derive_color;
  float dist_i = 0; 
  Vec3f col;
 
  if ( !isShadow ) {
    if ( !calcNormals ) {
      if ( sphere.ray_intersect(param, dir, dist_i, col) && dist_i < spheres_dist ) {
        hit = orig + dir * dist_i;  
        if ( additColor )
          colorbuffer[i + j * width] = col;
      }
      else { 
        hit = Vec3f( 10001,10001,10001 );
        dist_i = 1001;
      }
      spheres_dist = dist_i;
    }
    else {
      hit = pointsbuffer[i + j * width];
      dist_i =(hit-orig).norm();
      if (i > 0 && j > 0 && i<width-1 && j<height-1 && dist_i < spheres_dist ) {
        spheres_dist = dist_i;
        Vec3f hit1 = pointsbuffer[i + 1 + j * width];
        Vec3f hit2 = pointsbuffer[i - 1 + j * width];
        Vec3f hit3 = pointsbuffer[i + (j + 1) * width];
        Vec3f hit4 = pointsbuffer[i + (j - 1) * width];
        Vec3f vec1 = hit1 - hit2;
        Vec3f vec2 = hit3 - hit4;
        vec1.normalize();
        vec2.normalize();
        Vec3f norm = cross(vec1, vec2);
        norm.normalize();
        if (norm * dir >= 0)
          norm = norm * (-1);
        N = norm;
        material = sphere.material;
        if (additColor)
          material.diffuse_color = colorbuffer[i + j * width];
      }
    }
  }
  else 
    if ( sphere.ray_intersect(param, dir, dist_i, col) && dist_i < spheres_dist )
      spheres_dist = dist_i;

  return spheres_dist < 1000;
}

// Функция возвращает вектор повернутый относительно вектора norm по X и по Y на случайный угол в диапазоне  [-h;h]
Vec3f RandomNormal( const Vec3f & norm,
                           size_t h) {
  
  float coof = 2*h * M_PI / 180.0;
  float x = ( rand() / float(RAND_MAX) - 0.5 ) * coof;
  float y = ( rand() / float(RAND_MAX) - 0.5 ) * coof;
  Vec3f newNorm = norm;
  rotX( newNorm, x );
  rotY( newNorm, y);
  return newNorm;  
}

// Функция возвращает цвет пикселя испущенного из камеры в направлении dir. Если луч соударяется с множеством, то вычисляется освещенность по Фонгу точки соударения, иначе
// возвращается цвет фона.
Vec3f cast_ray( const MandelParameters &   param,
                const Vec3f &              dir,
                const Sphere &             sphere, 
                const std::vector<Light> & lights,
                const buffer &             pointsbuffer,
                      buffer &             colorbuffer,
                      size_t               i,
                      size_t               j,
                      bool                 calcNormals ) {
  const Vec3f & orig = param.orig;
  size_t maxIter = param.max_iter;
  size_t width = param.width;
  size_t height = param.height;
  bool  additColor = param.derive_color;
  Vec3f point, N;
  Material material;
  Vec3f color( 0.2, 0.7, 0.8 );

  if ( !scene_intersect(param, dir, sphere,pointsbuffer, colorbuffer, i, j, false, calcNormals,  point, N, material) ) {
    if ( !calcNormals ) { 
      colorbuffer[i + j * width]=color;
      color =point;
    }
    return color; 
  }
  else
    color=Vec3f (0,0,0 );

  if ( calcNormals ) {
    for ( size_t h=0; h< maxIter; ++h ) {
      Vec3f newNorm = RandomNormal( N, maxIter );    
      Vec3f reflect_color;
      Vec3f refract_color;     
      float diffuse_light_intensity = 0;
      float specular_light_intensity = 0;
      for ( size_t i = 0; i < lights.size(); i++ ) {
        Vec3f light_dir = (lights[i].position - point).normalize();
        float light_distance = (lights[i].position - point).norm();
        Vec3f shadow_orig = light_dir * newNorm < 0 ? point - newNorm * 0.05 : point + newNorm * 0.05;
        Vec3f shadow_pt, shadow_N;
        Material tmpmaterial;
        MandelParameters shadowParam( false, param.mandel_iter, param.mandel_pow, param.mandel_dist, width, height, param.threads_count, maxIter, shadow_orig, param.rot_x,param.rot_z);
       if ( scene_intersect(shadowParam, light_dir, sphere, pointsbuffer, colorbuffer, i, j, true, false, shadow_pt, shadow_N, tmpmaterial) && (shadow_pt - shadow_orig).norm() < light_distance )
         continue;  
        diffuse_light_intensity += lights[i].intensity * std::max( 0.f, light_dir * newNorm );
        specular_light_intensity += powf(std::max(0.f, -reflect(-light_dir, newNorm) * dir), material.specular_exponent) * lights[i].intensity;
      }
      color =color+ material.diffuse_color * diffuse_light_intensity * material.albedo[0] + Vec3f(1., 1., 1.) * specular_light_intensity * material.albedo[1];
      
     
      if ( h == maxIter - 1 ) {
        float ever = 1 / float(maxIter);
        color = color * ever;
        float max = std::max( color[0], std::max(color[1], color[2]) );   
        if ( max > 1 ) 
          color = color * ( 1. / max );
      }       
    }
  }
  else 
   color = point;

  return color;
}

// Функция пробегает полосу пекселей на экране и для каждого пикселя вычисляет точку соударения, которую кладет в массив pointsbuffer, также адаптивный цвет точки (при вклучении флага),
// кладет его в массив colorbuffer. Затем для каждой точки из массива pointsbuffer вычисляется освещенность и цвет соответствующего пикселя кладется в массив framebuffer.
void render ( const MandelParameters &   param,
              const Sphere&              sphere,
              const std::vector<Light> & lights,
                    float                coof1,
                    float                coof2,
                    size_t               ind,
                    bool                 calcNormal,
                    buffer &             pointsbuffer,
                    buffer &             framebuffer,
                    buffer &             colorbuffer,
                    size_t &             common,
                    std::mutex &          mtx)
{
  size_t height = param.height;
  size_t width = param.width;
  float  angleX = param.rot_x;
  float  angleZ = param.rot_z;
  const Vec3f& orig = param.orig;
  size_t maxIter = param.max_iter;
  bool additColor = param.derive_color;
  size_t n = param.threads_count;
  size_t hPart = height / n;
  size_t begInd = (ind - 1) * hPart;
  size_t endInd = (ind)*hPart;

  for (size_t j = begInd; j < endInd; j++) {
    for (size_t i = 0; i < width; i++) {
      float x = (2 * (i + 0.5) / (float)width - 1) * coof2;
      float y = -(2 * (j + 0.5) / (float)height - 1) * coof1;
      Vec3f dir = Vec3f(x, -1, y).normalize();
      rotX(dir, -angleX);
      rotZ(dir, angleZ);
      if (calcNormal)
        framebuffer[i + j * width] = framebuffer[i + j * width] + cast_ray( param, dir, sphere, lights, pointsbuffer, colorbuffer, i, j, calcNormal );
      else
        pointsbuffer[i + j * width] = cast_ray( param, dir, sphere, lights, pointsbuffer, colorbuffer, i, j, false );
    }
  }

  const std::lock_guard<std::mutex> lock( mtx );
  common++;
  std::cout << "\r" << 100 * common / n << " %";
}


//Функция умножает каждую компоненту цвета на 255.
unsigned char * FromBufferToChar( const buffer & buff ) 
{
  size_t size = buff.size();
  size_t img_size = size * 3;
  unsigned char * img = ( unsigned char* )malloc( img_size );

  auto it = buff.begin();

  for ( unsigned char * pg = img; it != buff.end(); it += 1, pg += 1 ) {
    //unsigned char p = rand();
    *pg = ( uint8_t)(255*it->x );
    pg += 1;
    *pg = ( uint8_t)(255* it->y );
    pg += 1;
    *pg = ( uint8_t)(255* it->z );
  }

  return img;
}