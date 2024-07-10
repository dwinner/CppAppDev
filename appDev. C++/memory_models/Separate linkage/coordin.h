#ifndef SEPARATE_LINKAGE_COORDIN_H
#define SEPARATE_LINKAGE_COORDIN_H

struct polar
{
   double distance;    // distance from origin
   double angle;        // direction from origin
};

struct rect
{
   double x;        // horizontal distance from origin
   double y;        // vertical distance from origin
};

// prototypes
polar rect_to_polar(rect xypos);

void show_polar(polar dapos);

#endif //SEPARATE_LINKAGE_COORDIN_H
