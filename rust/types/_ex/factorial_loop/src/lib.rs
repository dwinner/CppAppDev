pub fn add(left: u64, right: u64) -> u64
{
   left + right
}

// Rewrite the factorial function using a `for` loop.
pub fn factorial(n: u32) -> u32
{
   if n == 0 || n == 1
   {
      return 1;
   }

   let mut result: u32 = 1;
   for i in 1..=n
   {
      result *= i;
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
