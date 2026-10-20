// Add &mut-setters to the `Ticket` struct for each of its fields.
//   Make sure to enforce the same validation rules you have in `Ticket::new`!
//   Even better, extract that logic and reuse it in both places. You can use
//   private functions or private static methods for that.

pub struct Ticket
{
   title: String,
   description: String,
   status: String,
}

impl Ticket
{
   pub fn new(title: String, description: String, status: String) -> Ticket
   {
      validate_title(&title);
      validate_description(&description);
      validate_status(&status);

      Ticket {
         title,
         description,
         status,
      }
   }

   pub fn title(&self) -> &String
   {
      &self.title
   }

   pub fn description(&self) -> &String
   {
      &self.description
   }

   pub fn status(&self) -> &String
   {
      &self.status
   }

   pub fn set_title(&mut self, new_title: String)
   {
      validate_title(&new_title);
      self.title = new_title;
   }

   pub fn set_description(&mut self, new_description: String)
   {
      validate_description(&new_description);
      self.description = new_description;
   }

   pub fn set_status(&mut self, new_status: String)
   {
      validate_status(&new_status);
      self.status = new_status;
   }
}

fn validate_title(title: &String)
{
   if title.is_empty()
   {
      panic!("Title cannot be empty");
   }

   if title.len() > 50
   {
      panic!("Title cannot be longer than 50 bytes");
   }
}

fn validate_description(description: &String)
{
   if description.is_empty()
   {
      panic!("Description cannot be empty");
   }

   if description.len() > 500
   {
      panic!("Description cannot be longer than 500 bytes");
   }
}

fn validate_status(status: &String)
{
   if status != "To-Do" && status != "In Progress" && status != "Done"
   {
      panic!("Only `To-Do`, `In Progress`, and `Done` statuses are allowed");
   }
}
