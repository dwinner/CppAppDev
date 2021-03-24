#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

namespace math_vector
{
   class Vector
   {
   public:
      /**
       * \brief RECT for rectangular, POL for Polar modes
       */
      enum mode
      {
         rectangular_view,
         polar_view
      };

      // Ctor, Dtor

      Vector();

      /**
       * \brief construct vector from rectangular coordinates if form is r (the default)
       *         or else from polar coordinates if form is p
       * \param n1 1st value (mode depending)
       * \param n2 2nd value (mode depending)
       * \param form ctor form
       */
      Vector(double n1, double n2, mode form = rectangular_view);

      ~Vector() = default;

      // Getters

      double getX() const;      

      double getY() const;      

      double getMagnitude() const;      

      double getAngle() const;      

      mode getMode() const;      

      void setMode(mode form);      

      // Methods

      void reset(double n1, double n2, mode form = rectangular_view);

      // operator overloading

      Vector operator+(const Vector& vector) const;

      Vector operator-(const Vector& vector) const;

      Vector operator-() const;

      Vector operator*(double mult) const;

      // friends

      friend Vector operator*(double mult, const Vector& vector);

      friend std::ostream& operator<<(std::ostream& stream, const Vector& vector);

   private:

      // Data
      double x_; // horizontal value
      double y_; // vertical value
      double magnitude_; // length of vector
      double angle_; // direction of vector in degrees
      mode mode_; // RECT or POL

      // Setters

      void setMagnitude();     

      void setAngle();      

      void setX();      

      void setY();      
   };
}

#endif // VECTOR_H
