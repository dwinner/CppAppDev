pub fn add(left: u64, right: u64) -> u64
{
   left + right
}

pub fn factorial(n: u32) -> u32
{
   let mut result: u32 = 1;
   for i in 1..=n
   {
      // Use saturating multiplication to stop at the maximum value of u32
      // rather than overflowing and wrapping around
      result = result.saturating_mul(i);
      if result == u32::MAX
      {
         break;
      }
   }

   result
}

#[cfg(test)]
mod tests
{
   use super::*;

   #[test]
   fn it_works()
   {
      let result = add(2, 2);
      assert_eq!(result, 4);
   }
}
