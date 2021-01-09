// atomic_compare_exchange_ex.c : atomic_compare_exchange() example
// -------------------------------------------------------------

#include <stdatomic.h>
// _Bool atomic_compare_exchange_strong( volatile A *object,
//       C *expected, C desired);
// _Bool atomic_compare_exchange_strong_explicit( volatile A *object,
//       C *expected, C desired,
//       memory_order success, memory_order failure);
// _Bool atomic_compare_exchange_weak( volatile A *object,
//       C *expected, C desired);
// _Bool atomic_compare_exchange_weak_explicit( volatile A *object,
//       C *expected, C desired,
//       memory_order success, memory_order failure);

long mulwith( volatile atomic_long *alPtr, long val)    // *=
{
   long old = *alPtr, new;

   do { new = old * val; }
   while (!atomic_compare_exchange_weak(alPtr, &old, new));

   return new;
}

#include <stdio.h>

int main()
{
    atomic_long a_value = 12L;
    mulwith( &a_value, 5L);

    printf("12 * 5 = %ld\n", a_value);
    return 0;
}
