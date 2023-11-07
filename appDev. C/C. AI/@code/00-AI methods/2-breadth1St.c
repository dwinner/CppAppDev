/*********************************************************************
 *          Breadth search                                           *
 *********************************************************************/
void isflight(char *from, char *to)
{
  int d, dist;
  char anywhere[20];

  while(dist=find(from, anywhere)) {
    /* breadth-first modification */
    if(d=match(anywhere, to)) {
      push(from, to, dist);
      push(anywhere, to, d);
      return;
    }
  }
  /* try any connection */
  if(dist=find(from, anywhere)) {
    push(from, to, dist);
    isflight(anywhere, to);
  }
  else if(tos>0) {
    pop(from, to, &dist);
    isflight(from, to);
  }
}