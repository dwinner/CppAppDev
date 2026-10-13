pub fn add(left: u64, right: u64) -> u64
{
   left + right
}

// Rewrite the factorial function using a `while` loop.
pub fn factorial(n: u32) -> u32
{
   // The `todo!()` macro is a placeholder that the compiler
   // interprets as "I'll get back to this later", thus
   // suppressing type errors.
   // It panics at runtime.
   if n == 0 || n == 1
   {
      return 1;
   }

   let mut result: u32 = 1;
   let mut i: u32 = 1;
   while i <= n
   {
      result *= i;
      i += 1;
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
