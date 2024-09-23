#ifndef INC_3DPOINTSAMPLE_POINT3D_HPP
#define INC_3DPOINTSAMPLE_POINT3D_HPP


#include <cstdint>
#include <ostream>

class Point3D
{
public:
   Point3D(uint32_t x, uint32_t y, uint32_t z);

   friend std::ostream &operator<<(std::ostream &anOStream, const Point3D &aPoint3D);

private:
   uint32_t x_;
   uint32_t y_;
   uint32_t z_;
};


#endif //INC_3DPOINTSAMPLE_POINT3D_HPP
