enum TicketNewError
{
   TitleError(String),
   DescriptionError(String),
}

pub fn easy_ticket(title: String, description: String, status: Status) -> Ticket
{
   let result = Ticket::new(title.clone(), description, status.clone());
   result.unwrap_or_else(|error| match error
   {
      TicketNewError::TitleError(error_msg) =>
      {
         panic!("{}", error_msg);
      }
      TicketNewError::DescriptionError(_error_msg) => Ticket {
         title,
         description: "Description not provided".to_string(),
         status,
      },
   })
}

#[derive(Debug, PartialEq)]
pub struct Ticket
{
   title: String,
   description: String,
   status: Status,
}

#[derive(Debug, PartialEq, Clone)]
pub enum Status
{
   ToDo,
   InProgress
   {
      assigned_to: String,
   },
   Done,
}

impl Ticket
{
   pub(crate) fn new(title: String, description: String, status: Status) -> Result<Ticket, TicketNewError>
   {
      if title.is_empty()
      {
         return Err(TicketNewError::TitleError("Title cannot be empty".to_string()));
      }

      if title.len() > 50
      {
         return Err(TicketNewError::TitleError(
            "Title cannot be longer than 50 bytes".to_string(),
         ));
      }

      if description.is_empty()
      {
         return Err(TicketNewError::DescriptionError(
            "Description cannot be empty".to_string(),
         ));
      }

      if description.len() > 500
      {
         return Err(TicketNewError::DescriptionError(
            "Description cannot be longer than 500 bytes".to_string(),
         ));
      }

      Ok(Ticket {
         title,
         description,
         status,
      })
   }

   pub fn title(&self) -> &str
   {
      &self.title
   }

   pub fn description(&self) -> &str
   {
      &self.description
   }

   pub fn status(&self) -> &Status
   {
      &self.status
   }
}
