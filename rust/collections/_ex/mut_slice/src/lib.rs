// TODO: Define a function named `squared` that raises all `i32`s within a slice
// to the power of 2.  The slice should be modified in place.

pub fn squared(slice: &mut [i32])
{
   for item in slice.iter_mut()
   {
      *item *= *item;
   }
}

// TODO: Define a function named `sum` that takes a reference to a slice of
// `u32` and returns the sum of all  elements in the slice.

pub fn sum(slice: &[u32]) -> u32
{
   let mut sum: u32 = 0;
   for item in slice
   {
      sum += item;
   }

   sum
}
