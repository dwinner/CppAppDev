/*********************************************************************
 *   Closest path                                                    *
 *********************************************************************/
listing 12
/* Find closest "anywhere". */
int find(char *from, char *anywhere)
{
  int pos, dist;

  pos = 0;
  dist = 32000;  /* larger than the longest route */
  find_pos = 0;

  while(find_pos < f_pos) {
    if(!strcmp(flight[find_pos].from, from) &&
      !flight[find_pos].skip) {
        if(flight[find_pos].distance<dist) {
        pos = find_pos;
        dist = flight[find_pos].distance;
      }
    }
    find_pos++;
  }
  if(pos) {
    strcpy(anywhere, flight[pos].to);
    flight[pos].skip = 1;
    return flight[pos].distance;
  }
  return 0;
}