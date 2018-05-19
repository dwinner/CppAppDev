// Example 2-2. Illustrating the precision of type float  
// precision.c

#include <stdio.h>
#include <float.h>

int main()
{
   puts("\nCharacteristics of the type float\n");

   printf("Storage size: %d bytes\n"
          "Smallest positive value: %E\n"
          "Greatest positive value: %E\n"
          "Precision: %d decimal digits\n",
          sizeof(float), FLT_MIN, FLT_MAX, FLT_DIG);

   puts("\nAn example of float precision:\n");
   double d_var = 12345.6;          // A variable of type double.
   float f_var = (float)d_var;      // Initializes the float
                                    // variable with the value of d_var.
   printf("The floating-point number    "
          "%18.10f\n", d_var);
   printf("has been stored in a variable\n"
          "of type float as the value   "
          "%18.10f\n", f_var);
   printf("The rounding error is        "
          "%18.10f\n", d_var - f_var);

   return 0;
}

/*
int main()
{
   puts("Charakteristika des Typs float\n");

   printf("Groesse (Byte):           %d\n"
          "Kleinster positiver Wert: %E\n"
          "Groesster positiver Wert: %E\n"
          "Genauigkeit (dezimal)   : %d\n",
          sizeof(float), FLT_MIN, FLT_MAX, FLT_DIG);
/ *
   puts("----------------------------------------------------\n"
        "Charakteristika des Typs double\n");

   printf("Groesse (Byte):           %d\n"
          "Kleinster positiver Wert: %E\n"
          "Groesster positiver Wert: %E\n"
          "Genauigkeit (dezimal)   : %d\n",
          sizeof(double), DBL_MIN, DBL_MAX, DBL_DIG);

   puts("----------------------------------------------------\n"
        "Charakteristika des Typs long double\n");

   printf("Groesse (Byte):           %d\n"
          "Kleinster positiver Wert: %E\n"
          "Groesster positiver Wert: %E\n"
          "Genauigkeit (dezimal)   : %d\n",
          sizeof(long double), LDBL_MIN, LDBL_MAX, LDBL_DIG);
* /
   puts("\nEin Beispiel zur Genauigkeit von float:");
   {
   double d_var = 12345.6;
   float  f_var = (float)d_var;

   printf("Die Gleitpunktzahl\n"
          "%.10f\n", d_var);
   printf("wird in einer float-Variable mit dem Wert\n"
          "%.10f gespeichert.\n", f_var); 
   printf("Die Ungenauigkeit betraegt %.10f\n", d_var - f_var);
   }
/ *
   printf("float-Werte: ");
   scanf("%f", &f_var);

   printf("%.10f : %A", f_var, f_var);

   union floatBits
   {
     float f;
     struct
     {
       unsigned m : 23;
       unsigned e : 8;
       unsigned v : 1;
     };
   } x;
   
   x.f = f_var;
   cout << x.f << " : " << hex << endl;
   cout << "Vorzeichen:  " << x.v << endl
        << "Exponent:    " << x.e << endl
        << "Mantisse:    " << x.m << endl;
   
   char vz = (x.v) ? '-' : ' ';
   double mDec = x.m/8388608.0;       // 2 hoch 23 = 8388608
   
   cout << x.f << " = " << dec;
   cout << vz << (1.0 + mDec) << " * 2 hoch " << ((int)x.e - 127) 
        << " = " << vz << (1.0 + mDec) * pow( 2.0,((int)x.e - 127)) << endl;
* /
  return 0;
}
*/
/*
Groesse, Wertebereiche und Genauigkeit des Typs float

Groesse (Byte):           4
Kleinster positiver Wert: 1.175494E-038
Groesster positiver Wert: 3.402823E+038
Genauigkeit (dezimal)   : 6

Ein Beispiel zur Genauigkeit von float:
Die Gleitpunktzahl
12345.6000000000
wird in einer float-Variable mit dem Wert
12345.5996093750 gespeichert.
Die Ungenauigkeit betraegt 0.0003906250
*/
