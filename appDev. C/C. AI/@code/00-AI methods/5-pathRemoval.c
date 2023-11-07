/*********************************************************************
 *   Path removal                                                    *
 *********************************************************************/
int main(void)
{
  char from[20], to[20];

  setup();

  printf("From? ");
  gets(from);
  printf("To? ");
  gets(to);
  do {
    isflight(from, to);
    route(to);
    tos = 0;  /* reset the backtrack stack */
  } while(getchar() != 'q');

  return 0;
}