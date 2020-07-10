listing 1
#include <math.h>
#include <stdio.h>

int main(void)
{
  double val = -1.0;

  do {
    printf("Arc cosine of %f is %f.\n", val, acos(val));
    val += 0.1;
  } while(val<=1.0);

  return 0;
}

listing 2
#include <math.h>
#include <stdio.h>

int main(void)
{
  double val = -1.0;

  do {
    printf("Arc sine of %f is %f.\n", val, asin(val));
    val += 0.1;
  } while(val<=1.0);

  return 0;
}

listing 3
#include <math.h>
#include <stdio.h>

int main(void) 
{
  double val = -1.0;

  do {
    printf("Arc tangent of %f is %f.\n", val, atan(val));
    val += 0.1;
  } while(val<=1.0);

  return 0;
}

listing 4
#include <math.h>
#include <stdio.h>

int main(void)
{
  double val = -1.0;

  do {
    printf("Atan2 of %f is %f.\n", val, atan2(val,1.0));
    val += 0.1;
  } while(val<=1.0);

  return 0;
}

listing 5
printf("%f", cbrt(8));

listing 6
printf("%f", ceil(9.9));

listing 7
#include <math.h>
#include <stdio.h>

int main(void)
{
  double val = -1.0;

  do {
    printf("Cosine of %f is %f.\n", val, cos(val));
    val += 0.1;
  } while(val<=1.0);

  return 0;
}

listing 8
#include <math.h>
#include <stdio.h>

int main(void)
{
  double val = -1.0;

  do {
    printf("Hyperbolic cosine of %f is %f.\n", val, cosh(val));
    val += 0.1;
  } while(val<=1.0);

  return 0;
}

listing 9
printf("Value of e to the first: %f.", exp(1.0));

listing 10
#include <math.h>
#include <stdio.h>

int main(void)
{
  printf("%1.1f %1.1f", fabs(1.0), fabs(-1.0));

  return 0;
}

listing 11
printf("%f", floor(10.9));

listing 12
#include <math.h>
#include <stdio.h>

int main(void)
{
  printf("%1.1f", fmod(10.0, 3.0));

  return 0;
}

listing 13
int e;
double f;

f = frexp(10.0, &e);
printf("%f %d", f, e);

listing 14
#include <math.h>
#include <stdio.h>

int main(void)
{
  printf("%f", ldexp(1,2));

  return 0;
}

listing 15
#include <math.h>
#include <stdio.h>

int main(void)
{
  double val = 1.0;

  do {
    printf("%f %f\n", val, log(val));
    val++;
  } while (val<11.0);

  return 0;
}

listing 16
#include <math.h>
#include <stdio.h>

int main(void)
{
  double val = 1.0;

  do {
    printf("%f %f\n", val, log10(val));
    val++;
  } while (val<11.0);

  return 0;
}

listing 17
double i;
double f;

f = modf(10.123, &i);
printf("%f %f",i , f);

listing 18
#include <math.h>
#include <stdio.h>

int main(void)
{
  double x = 10.0, y = 0.0;

  do {
    printf("%f\n", pow(x, y));
    y++;
  } while(y<11.0);

  return 0;
}

listing 19
#include <math.h>
#include <stdio.h>

int main(void)
{
  double val = -1.0;

  do {
    printf("Sine of %f is %f.\n", val, sin(val));
    val += 0.1;
  } while(val<=1.0);

  return 0;
}

listing 20
#include <math.h>
#include <stdio.h>

int main(void)
{
  double val = -1.0;

  do {
    printf("Hyperbolic sine of %f is %f.\n", val, sinh(val));
    val += 0.1;
  } while(val<=1.0);

  return 0;
}

listing 21
printf("%f", sqrt(16.0));

listing 22
#include <math.h>
#include <stdio.h>

int main(void)
{
  double val = -1.0;

  do {
    printf("Tangent of %f is %f.\n", val, tan(val));
    val += 0.1;
  } while(val<=1.0);

  return 0;
}

listing 23
#include <math.h>
#include <stdio.h>

int main(void)
{
  double val = -1.0;

  do {
    printf("Hyperbolic tangent of %f is %f.\n", val, tanh(val));
    val += 0.1;
  } while(val<=1.0);

  return 0;
}

