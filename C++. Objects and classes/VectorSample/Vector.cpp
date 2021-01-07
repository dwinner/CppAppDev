#include "Vector.h"
#include <cmath>

using std::sqrt;
using std::sin;
using std::cos;
using std::atan;
using std::atan2;
using std::cout;

namespace math_vector
{
   const double rad_to_deg = 45.0 / atan(1.0);

   /*inline */
   Vector::Vector()
   {
      x_ = y_ = magnitude_ = angle_ = .0;
      mode_ = rectangular_view;
   }

   Vector::Vector(const double n1, const double n2, const mode form)
   {
      reset(n1, n2, form);
   }

   inline double Vector::getX() const
   {
      return x_;
   }

   inline double Vector::getY() const
   {
      return y_;
   }

   /*inline */
   double Vector::getMagnitude() const
   {
      return magnitude_;
   }

   inline double Vector::getAngle() const
   {
      return angle_;
   }

   inline Vector::mode Vector::getMode() const
   {
      return mode_;
   }

   /*inline */
   void Vector::setMode(const mode form)
   {
      mode_ = form;
   }

   void Vector::reset(const double n1, const double n2, const mode form)
   {
      mode_ = form;
      if (form == rectangular_view)
      {
         x_ = n1;
         y_ = n2;
         setMagnitude();
         setAngle();
      }
      else if (form == polar_view)
      {
         magnitude_ = n1;
         angle_ = n2 / rad_to_deg;
         setX();
         setY();
      }
      else
      {
         cout << "Incorrect 3rd argument to Vector() -- vector set to 0\n";
         x_ = y_ = magnitude_ = angle_ = .0;
         mode_ = rectangular_view;
      }
   }

   Vector Vector::operator+(const Vector& vector) const
   {
      return Vector(x_ + vector.x_, y_ + vector.y_);
   }

   Vector Vector::operator-(const Vector& vector) const
   {
      return Vector(x_ - vector.x_, y_ - vector.y_);
   }

   Vector Vector::operator-() const
   {
      return Vector(-x_, -y_);
   }

   Vector Vector::operator*(const double mult) const
   {
      return Vector(mult * x_, mult * y_);
   }

   inline void Vector::setMagnitude()
   {
      magnitude_ = sqrt(x_ * x_ + y_ * y_);
   }

   inline void Vector::setAngle()
   {
      angle_ = x_ == .0 && y_ == .0
                  ? .0
                  : atan2(y_, x_);
   }

   inline void Vector::setX()
   {
      x_ = magnitude_ * cos(angle_);
   }

   inline void Vector::setY()
   {
      y_ = magnitude_ * sin(angle_);
   }

   Vector operator*(const double mult, const Vector& vector)
   {
      return vector * mult;
   }

   std::ostream& operator<<(std::ostream& stream, const Vector& vector)
   {
      if (vector.mode_ == Vector::rectangular_view)
      {
         stream << "(x,y) = (" << vector.x_ << ", " << vector.y_ << ")";
      }
      else if (vector.mode_ == Vector::polar_view)
      {
         stream << "(m,a) = (" << vector.magnitude_ << ", " << vector.angle_ * rad_to_deg << ")";
      }
      else
      {
         stream << "Vector object mode is invalid";
      }

      return stream;
   }
}
