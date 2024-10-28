#include "Point3D.hpp"

Point3D::Point3D(uint32_t x, uint32_t y, uint32_t z) :
    x_(x),
    y_(y),
    z_(z)
{}

std::ostream &operator<<(std::ostream &anOStream, const Point3D &aPoint3D)
{
   anOStream << "x_: " << aPoint3D.x_ << " y_: " << aPoint3D.y_ << " z_: " << aPoint3D.z_;
   return anOStream;
}
