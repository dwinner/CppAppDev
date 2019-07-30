listing 4
void deletecell(char *cell_name,
            struct cell **start,
            struct cell **last)
{
  struct cell *info;

  info = find(cell_name, *start);
  if(info) {
    if(*start==info) {
      *start = info->next;
      if(*start) (*start)->prior = NULL;
      else *last = NULL;
    }
    else {
      if(info->prior) info->prior->next = info->next;
      if(info != *last)
          info->next->prior = info->prior;
      else
        *last = info->prior;
    }
    free(info); /* return memory to system */
  }
}

listing 5
struct cell *find(char *cell_name, struct cell *start)
{
  struct cell *info;

  info = start;
  while(info) {
    if(!strcmp(cell_name, info->cell_name)) return info;
    info = info->next; /* get next cell */
  }
  printf("Cell not found.\n");
  return NULL; /* not found */
}

listing 6
struct cell {
  char cell_name[9];  /* cell name e.g., A1, B34 */
  char  formula[128]; /* info e.g., 10/B2 */
  struct cell *left;  /* pointer to left subtree */
  struct cell *right; /* pointer to right subtree */
} list_entry;

listing 7
struct cell *stree(
        struct cell *root,
        struct cell *r,
        struct cell *n)
{
  if(!r) {    /* first node in subtree */
    n->left = NULL;
    n->right = NULL;
    if(!root) return n;  /* first entry in tree */
    if(strcmp(n->cell_name, root->cell_name) < 0)
      root->left = n;
    else
      root->right = n;
    return n;
  }

  if(strcmp(r->cell_name, n->cell_name) <= 0)
    stree(r, r->right, n);
  else
    stree(r, r->left, n);

  return root;
}

listing 8
struct cell *dtree(
        struct cell *root,
        char *key)
{
  struct cell *p, *p2;

  if(!root) return root; /* item not found */

  if(!strcmp(root->cell_name, key)) { /* delete root */
    /* this means an empty tree */
    if(root->left == root->right){
      free(root);
      return NULL;
    }
    /* or if one subtree is null */
    else if(root->left == NULL) {
      p = root->right;
      free(root);
      return p;
    }
    else if(root->right == NULL) {
      p = root->left;
      free(root);
      return p;
    }
    /* or both subtrees present */
    else {
      p2 = root->right;
      p = root->right;
      while(p->left) p = p->left;
      p->left = root->left;
      free(root);
      return p2;
    }
  }
  if(strcmp(root->cell_name, key)<=0)
    root->right = dtree(root->right, key);
  else root->left = dtree(root->left, key);
  return root;
}

listing 9
struct cell *search_tree(
        struct cell *root,
        char *key)
{
  if(!root) return root;  /* empty tree */
  while(strcmp(root->cell_name, key)) {
    if(strcmp(root->cell_name, key) <= 0)
      root = root->right;
    else root = root->left;
    if(root == NULL) break;
  }
  return root;
}

listing 10
struct cell {
  char cell_name[9];
  char  formula[128];
} list_entry[2600];   /* 2,600 cells */

listing 11
struct cell {
  char cell_name[9]; 
  char formula[128];
} list_entry;

struct cell *sheet[2600]; /* array of 2,600 pointers */

listing 12
void init_sheet(void)
{
  register int t;

  for(t=0; t < 2600; ++t) sheet[t] = NULL;
}

listing 13
void store(struct cell *i)
{
  int loc;
  char *p;

  /* compute index given cell name */
  loc = *(i->cell_name) - 'A'; /* column */
  p = &(i->cell_name[1]);
  loc += (atoi(p)-1) * 26; /* number of rows * row width + column */

  if(loc >= 2600) {
    printf("Cell out of bounds.\n");
    return;
  }
  sheet[loc] = i; /* place pointer in the array */
}

listing 14
void deletecell(struct cell *i)
{
  int loc;
  char *p;

  /* compute index given cell name */
  loc = *(i->cell_name) - 'A'; /* column */
  p = &(i->cell_name[1]);
  loc += (atoi(p)-1) * 26; /* number of rows * row width + column */

  if(loc >= 2600) {
    printf("Cell out of bounds.\n");
    return;
  }
  if(!sheet[loc]) return; /* don't free a null pointer */

  free(sheet[loc]);  /* return memory to system */
  sheet[loc] = NULL;
}

listing 15
struct cell *find(char *cell_name)
{
  int loc;
  char *p;

  /* compute index given name */
  loc = *(cell_name) - 'A'; /* column */
  p = &(cell_name[1]);
  loc += (atoi(p)-1) * 26; /* number of rows * row width + column */

  if(loc>=2600 || !sheet[loc]) { /* no entry in that cell */
    printf("Cell not found.\n");
    return NULL;  /* not found */
  }
  else return sheet[loc];
}

listing 16
#define MAX 260

struct htype {
  int index;   /* logical index */
  int val;     /* actual value of the array element */
  struct htype *next; /* pointer to next value with same hash */
} primary[MAX];

listing 17
/* Initialize the hash array. */
void init(void)
{
  register int i;

  for (i=0; i<MAX; i++) {
    primary[i].index = -1;
    primary[i].next = NULL;  /* null chain */
    primary[i].val = 0;
  }
}

listing 18
/* Compute hash and store value. */
void store(char *cell_name, int v)
{
  int h, loc;
  struct htype *p;

  /* produce the hash value */
  loc = *cell_name - 'A'; /* column */
  loc += (atoi(&cell_name[1])-1) * 26; /* rows * width + columns */
  h = loc/10; /* hash */

  /* Store in the location unless full or
     store there if logical indexes agree - i.e., update.
  */
  if(primary[h].index==-1 || primary[h].index==loc) {
    primary[h].index = loc;
    primary[h].val = v;
    return;
  }

  /* otherwise, create or add to collision list */
  p = (struct htype *) malloc(sizeof(struct htype));
  if(!p) {
    printf("Out of Memory\n");
    return;
  }
  p->index = loc;
  p->val = v;
  slstore(p, &primary[h]);
}

/* Add elements to the collision list. */
void slstore(struct htype *i,
             struct htype *start)
{
  struct htype *old, *p;

  old = start;
  /* find end of list */
  while(start) {
    old = start;
    start = start->next;
  }
  /* link in new entry */
  old->next = i;
  i->next = NULL;
}

listing 19
/* Compute hash and return value. */
int find(char *cell_name)
{
  int h, loc;
  struct htype *p;

  /* produce the hash value */
  loc = *cell_name - 'A'; /* column */
  loc += (atoi(&cell_name[1])-1) * 26; /* rows * width + column */
  h = loc/10;

  /* return the value if found */
  if(primary[h].index == loc) return(primary[h].val);
  else { /* look in collision list */
    p = primary[h].next;
    while(p) {
      if(p->index == loc) return p->val;
      p = p->next;
    }
    printf("Not in Array\n");
    return -1;
  }
}

