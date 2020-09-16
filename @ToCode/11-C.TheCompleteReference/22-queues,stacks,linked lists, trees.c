listing 1
#define MAX 100

char *p[MAX];
int spos = 0;
int rpos = 0;

/* Store an appointment. */
void qstore(char *q)
{
  if(spos==MAX) {
    printf("List Full\n");
    return;
  }
  p[spos] = q;
  spos++;
}

/* Retrieve an appointment. */
char *qretrieve()
{
  if(rpos==spos) {
    printf("No more appointments.\n");
    return '\0';
  }
  rpos++;
  return p[rpos-1];
}

listing 2
/* Mini Appointment-Scheduler */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MAX 100

char *p[MAX], *qretrieve(void);
int spos = 0;
int rpos = 0;
void enter(void), qstore(char *q), review(void), delete_ap(void);

int main(void)
{
  char s[80];
  register int t;

  for(t=0; t < MAX; ++t) p[t] = NULL; /* init array to nulls */

  for(;;) {
    printf("Enter, List, Remove, Quit: ");
    gets(s);
    *s = toupper(*s);

    switch(*s) {
      case 'E':
        enter();
        break;
      case 'L':
        review();
        break;
      case 'R':
        delete_ap();
        break;
      case 'Q':
        exit(0);
    }
  }
  return 0;
}

/* Enter appointments in queue. */
void enter(void)
{
  char s[256], *p;

  do {
    printf("Enter appointment %d: ", spos+1);
    gets(s);
    if(*s==0) break; /* no entry */
    p = (char *) malloc(strlen(s)+1);
    if(!p) {
      printf("Out of memory.\n");
      return;
    }
    strcpy(p, s);
    if(*s) qstore(p);
  } while(*s);
}

/* See what's in the queue. */
void review(void)
{
  register int t;

  for(t=rpos; t < spos; ++t)
    printf("%d. %s\n", t+1, p[t]);
}

/* Delete an appointment from the queue. */
void delete_ap(void)
{
  char *p;

  if((p=qretrieve())==NULL) return;
  printf("%s\n", p);
}

/* Store an appointment. */
void qstore(char *q)
{
  if(spos==MAX) {
    printf("List Full\n");
    return;
  }
  p[spos] = q;
  spos++;
}

/* Retrieve an appointment. */
char *qretrieve(void)
{
  if(rpos==spos) {
    printf("No more appointments.\n");
    return NULL;
  }
  rpos++;
  return p[rpos-1];
}

listing 3
void qstore(char *q)
{
  /* The queue is full if either spos is one less than rpos
     or if spos is at the end of the queue array and rpos
     is at the beginning.
  */
  if(spos+1==rpos || (spos+1==MAX && !rpos)) {
    printf("List Full\n");
    return;
  }

  p[spos] = q;
  spos++;
  if(spos==MAX) spos = 0; /* loop back */
}

char *qretrieve(void)
{
  if(rpos==MAX) rpos = 0; /* loop back */
  if(rpos==spos) {
    printf("No events to retrieve.\n");
    return NULL;
  }
  rpos++;
  return p[rpos-1];
}

listing 4
/* A circular queue example using a keyboard buffer. */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define MAX 80

char buf[MAX+1];
int spos = 0;
int rpos = 0;

void qstore(char q);
char qretrieve(void);

int main(void)
{
  register char ch;
  int t;

  buf[80] = '\0';

  /* Input characters until a carriage return is typed. */
  for(ch=' ',t=0; t<32000 && ch!='\r'; ++t) {
    if(_kbhit()) {
      ch = _getch();
      qstore(ch);
    }
    printf("%d ", t);
    if(ch == '\r') {
      /* Display and empty the key buffer. */
      printf("\n");
      while((ch=qretrieve()) != '\0') printf("%c", ch);
      printf("\n");
    }
  }
  return 0;
}

/* Store characters in the queue. */
void qstore(char q)
{
  if(spos+1==rpos || (spos+1==MAX && !rpos)) {
    printf("List Full\n");
    return;
  }
  buf[spos] = q;
  spos++;
  if(spos==MAX) spos = 0; /* loop back */
}

/* Retrieve a character. */
char qretrieve(void)
{
  if(rpos==MAX) rpos = 0; /* loop back */
  if(rpos==spos) return '\0';

  rpos++;
  return buf[rpos-1];
}

listing 5
int stack[MAX];
int tos=0;   /* top of stack */

/* Put an element on the stack. */
void push(int i)
{

  if(tos >= MAX) {
    printf("Stack Full\n");
    return;
  }
  stack[tos] = i;
  tos++;
}

/* Retrieve the top element from the stack. */
int pop(void)
{
  tos--;
  if(tos < 0) {
    printf("Stack Underflow\n");
    return 0;
  }
  return stack[tos];
}

listing 6
int *p;   /* will point to a region of free memory */
int *tos; /* points to top of stack */
int *bos; /* points to bottom of stack */

/* Store an element on the stack. */
void push(int i)
{
  if(p > bos) {
    printf("Stack Full\n");
    return;
  }
  *p = i;
  p++;
}

/* Retrieve the top element from the stack. */
int pop(void)
{
  p--;
  if(p < tos) {
    printf("Stack Underflow\n");
    return 0;
  }
  return *p;
}

listing 7
/* A simple four-function calculator. */

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int *p;   /* will point to a region of free memory */
int *tos; /* points to top of stack */
int *bos; /* points to bottom of stack */

void push(int i);
int pop(void);

int main(void)
{
  int a, b;
  char s[80];

  p = (int *) malloc(MAX*sizeof(int)); /* get stack memory */
  if(!p) {
    printf("Allocation Failure\n");
    exit(1);
  }
  tos = p;
  bos = p + MAX-1;

  printf("Four Function Calculator\n");
  printf("Enter 'q' to quit\n");

  do {
    printf(": ");
    gets(s);
    switch(*s) {
      case '+':
        a = pop();
        b = pop();
        printf("%d\n", a+b);
        push(a+b);
        break;
      case '-':
        a = pop();
        b = pop();
        printf("%d\n", b-a);
        push(b-a);
        break;
      case '*':
        a = pop();
        b = pop();
        printf("%d\n", b*a);
        push(b*a);
        break;
      case '/':
        a = pop();
        b = pop();
        if(a==0) {
          printf("Divide by 0.\n");
          break;
        }
        printf("%d\n", b/a);
        push(b/a);
        break;
      case '.': /* show contents of top of stack */
        a = pop();
        push(a);
        printf("Current value on top of stack: %d\n", a);
        break;
      default:
        push(atoi(s));
    }
  } while(*s != 'q');

  return 0;
}

/* Put an element on the stack. */
void push(int i)
{
  if(p > bos) {
    printf("Stack Full\n");
    return;
  }
  *p = i;
  p++;
}

/* Retrieve the top element from the stack. */
int pop(void)
{
  p--;
  if(p < tos) {
    printf("Stack Underflow\n");
    return 0;
  }
  return *p;
}

listing 8
void slstore(struct address *i,
             struct address **last)
{
  if(!*last) *last = i; /* first item in list */
  else (*last)->next = i;
  i->next = NULL;
  *last = i;
}

listing 9
/* Store in sorted order. */
void sls_store(struct address *i, /* new element to store */
               struct address **start, /* start of list */
               struct address **last) /* end of list */
{
  struct address *old, *p;

  p = *start;

  if(!*last) { /* first element in list */
    i->next = NULL;
    *last = i;
    *start = i;
    return;
  }

  old = NULL;
  while(p) {
    if(strcmp(p->name, i->name)<0) {
      old = p;
      p = p->next;
    }
    else {
      if(old) { /* goes in middle */
        old->next = i;
        i->next = p;
        return;
      }
      i->next = p; /* new first element */
      *start = i;
      return;
    }
  }
  (*last)->next = i; /* put on end */
  i->next = NULL;
  *last = i;
}

listing 10
void display(struct address *start)
{
  while(start) {
    printf("%s\n", start->name);
    start = start->next;
  }
}

listing 11
struct address *search(struct address *start, char *n)
{
  while(start) {
    if(!strcmp(n, start->name)) return start;
    start = start->next;
  }
  return NULL;  /* no match */
}

listing 12
void sldelete(
     struct address *p, /* previous item */
     struct address *i, /* item to delete */
     struct address **start, /* start of list */
     struct address **last) /* end of list */
{
  if(p) p->next = i->next;
  else *start = i->next;

  if(i==*last && p) *last = p;
}

listing 13
void dlstore(struct address *i, struct address **last)
{

  if(!*last) *last = i; /* is first item in list */
  else (*last)->next = i;
  i->next = NULL;
  i->prior = *last;
  *last = i;
}

listing 14
/* Create a doubly linked list in sorted order. */
void dls_store(
  struct address *i,   /* new element */
  struct address **start, /* first element in list */
  struct address **last /* last element in list */
)
{
  struct address *old, *p;

  if(*last==NULL) { /* first element in list */
    i->next = NULL;
    i->prior = NULL;
    *last = i;
    *start = i;
    return;
   }

  p = *start; /* start at top of list */

  old = NULL;
  while(p) {
    if(strcmp(p->name, i->name)<0){
      old = p;
      p = p->next;
    }
    else {
      if(p->prior) {
        p->prior->next = i;
        i->next = p;
        i->prior = p->prior;
        p->prior = i;
        return;
      }
      i->next = p; /* new first element */
      i->prior = NULL;
      p->prior = i;
      *start = i;
      return;
    }
  }
  old->next = i; /* put on end */
  i->next = NULL;
  i->prior = old;
  *last = i;
}

listing 15
void dldelete(
  struct address *i, /* item to delete */
  struct address **start,  /* first item */
  struct address **last) /* last item */
{
  if(i->prior) i->prior->next = i->next;
  else { /* new first item */
    *start = i->next;
    if(start) start->prior = NULL;
  }

  if(i->next) i->next->prior = i->prior;
  else   /* deleting last element */
    *last = i->prior;
}

listing 16
/* A simple mailing list program that illustrates the
   use and maintenance of doubly linked lists.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct address {
  char name[30];
  char street[40];
  char city[20];
  char state[3];
  char zip[11]; 
  struct address *next;  /* pointer to next entry */
  struct address *prior;  /* pointer to previous record */
};

struct address *start;  /* pointer to first entry in list */
struct address *last;  /* pointer to last entry */
struct address *find(char *);

void enter(void), search(void), save(void);
void load(void), list(void);
void mldelete(struct address **, struct address **);
void dls_store(struct address *i, struct address **start,
               struct address **last);
void inputs(char *, char *, int), display(struct address *);
int menu_select(void);

int main(void)
{
  start = last = NULL;  /* initialize start and end pointers */

  for(;;) {
    switch(menu_select()) {
      case 1: enter(); /* enter an address */
        break;
      case 2: mldelete(&start, &last); /* remove an address */
        break;
      case 3: list(); /* display the list */
        break;
      case 4: search(); /* find an address */
        break;
      case 5: save();  /* save list to disk */
        break;
      case 6: load();  /* read from disk */
        break;
      case 7: exit(0);
    }
  }
  return 0;
}

/* Select an operation. */
int menu_select(void)
{
  char s[80];
  int c;

  printf("1. Enter a name\n");
  printf("2. Delete a name\n");
  printf("3. List the file\n");
  printf("4. Search\n");
  printf("5. Save the file\n");
  printf("6. Load the file\n");
  printf("7. Quit\n");
  do {
    printf("\nEnter your choice: ");
    gets(s);
    c = atoi(s);
  } while(c<0 || c>7);
  return c;
}

/* Enter names and addresses. */
void enter(void)
{
  struct address *info;

  for(;;) {
    info = (struct address *)malloc(sizeof(struct address));
    if(!info) {
      printf("\nout of memory");
      return;
    }

    inputs("Enter name: ", info->name, 30);
    if(!info->name[0]) break;  /* stop entering */
    inputs("Enter street: ", info->street, 40);
    inputs("Enter city: ", info->city, 20);
    inputs("Enter state: ", info->state, 3);
    inputs("Enter zip: ", info->zip, 10);

    dls_store(info, &start, &last);
  } /* entry loop */
}

/* This function will input a string up to
   the length in count and will prevent
   the string from being overrun.  It will also
   display a prompting message. */
void inputs(char *prompt, char *s, int count)
{
  char p[255];

  do {
    printf(prompt);
    fgets(p, 254, stdin);
    if(strlen(p) > count) printf("\nToo Long\n");
  } while(strlen(p) > count);

  p[strlen(p)-1] = 0; /* remove newline character */
  strcpy(s, p);
}

/* Create a doubly linked list in sorted order. */
void dls_store(
  struct address *i,   /* new element */
  struct address **start, /* first element in list */
  struct address **last /* last element in list */
)
{
  struct address *old, *p;

  if(*last==NULL) {  /* first element in list */
    i->next = NULL;
    i->prior = NULL;
    *last = i;
    *start = i;
    return;
  }
  p = *start; /* start at top of list */

  old = NULL;
  while(p) {
    if(strcmp(p->name, i->name)<0){
      old = p;
      p = p->next;
    }
    else {
      if(p->prior) {
        p->prior->next = i;
        i->next = p;
        i->prior = p->prior;
        p->prior = i;
        return;
      }
      i->next = p; /* new first element */
      i->prior = NULL;
      p->prior = i;
      *start = i;
      return;
    }
  }
  old->next = i; /* put on end */
  i->next = NULL;
  i->prior = old;
  *last = i;
}

/* Remove an element from the list. */
void mldelete(struct address **start, struct address **last)
{
  struct address *info;
  char s[80];

  inputs("Enter name: ", s, 30);
  info = find(s);
  if(info) {
    if(*start==info) {
      *start=info->next;
      if(*start) (*start)->prior = NULL;
      else *last = NULL;
    }
    else {
      info->prior->next = info->next;
      if(info!=*last)
          info->next->prior = info->prior;
      else
        *last = info->prior;
    }
    free(info);  /* return memory to system */
  }
}

/* Find an address. */
struct address *find( char *name)
{
  struct address *info;

  info = start;
  while(info) {
    if(!strcmp(name, info->name)) return info;
    info = info->next;  /* get next address */
  }
  printf("Name not found.\n");
  return NULL;  /* not found */
}

/* Display the entire list. */
void list(void)
{
  struct address *info;

  info = start;
  while(info) {
    display(info);
    info = info->next;  /* get next address */
  }
  printf("\n\n");
}

/* This function actually prints the fields in each address. */
void display(struct address *info)
{
    printf("%s\n", info->name);
    printf("%s\n", info->street);
    printf("%s\n", info->city);
    printf("%s\n", info->state);
    printf("%s\n", info->zip);
    printf("\n\n");
}

/* Look for a name in the list. */
void search(void)
{
  char name[40];
  struct address *info;

  printf("Enter name to find: ");
  gets(name);
  info = find(name);
  if(!info) printf("Not Found\n");
  else display(info);
}

/* Save the file to disk. */
void save(void)
{
  struct address *info;

  FILE *fp;

  fp = fopen("mlist", "wb");
  if(!fp) {
    printf("Cannot open file.\n");
    exit(1);
  }
  printf("\nSaving File\n");

  info = start;
  while(info) {
    fwrite(info, sizeof(struct address), 1, fp);
    info = info->next;  /* get next address */
  }
  fclose(fp);
}

/* Load the address file. */
void load()
{
  struct address *info;
  FILE *fp;

  fp = fopen("mlist", "rb");
  if(!fp) {
    printf("Cannot open file.\n");
    exit(1);
  }

  /* free any previously allocated memory */
  while(start) {
    info = start->next;
    free(info);
    start = info;
  }

  /* reset top and bottom pointers */
  start = last = NULL;

  printf("\nLoading File\n");
  while(!feof(fp)) {
    info = (struct address *) malloc(sizeof(struct address));
    if(!info) {
      printf("Out of Memory");
      return;
    }
    if(1 != fread(info, sizeof(struct address), 1, fp)) break;
    dls_store(info, &start, &last);
  }
  fclose(fp);
}

listing 17
struct tree {
  char info;
  struct tree *left;
  struct tree *right;
};

struct tree *stree(
  struct tree *root,
  struct tree *r,
  char info)
{
  if(!r) {
    r = (struct tree *) malloc(sizeof(struct tree));
    if(!r) {
      printf("Out of Memory\n");
      exit(0);
    }
    r->left = NULL;
    r->right = NULL;
    r->info = info;
    if(!root) return r; /* first entry */
    if(info < root->info) root->left = r;
    else root->right = r;
    return r;
  }
  if(info < r->info)
    stree(r,r->left,info);
  else
    stree(r,r->right,info);

  return root; 
}

listing 18
void inorder(struct tree *root)
{
  if(!root) return;

  inorder(root->left);
  if(root->info) printf("%c ", root->info);
  inorder(root->right);
}

listing 19
void preorder(struct tree *root)
{
  if(!root) return;

  if(root->info) printf("%c ", root->info);
  preorder(root->left);
  preorder(root->right);
}

void postorder(struct tree *root)
{
  if(!root) return;

  postorder(root->left);
  postorder(root->right);
  if(root->info) printf("%c ", root->info);
}

listing 20
void print_tree(struct tree *r, int l)
{
  int i;

  if(r == NULL) return;

  print_tree(r->right, l+1);
  for(i=0; i<l; ++i) printf(" ");
  printf("%c\n", r->info);
  print_tree(r->left, l+1);
}

listing 21
/* This program displays a binary tree. */

#include <stdlib.h>
#include <stdio.h>

struct tree {
  char info;
  struct tree *left;
  struct tree *right;
};

struct tree *root; /* first node in tree */
struct tree *stree(struct tree *root,
                   struct tree *r, char info);
void print_tree(struct tree *root, int l);

int main(void)
{
  char s[80];

  root = NULL;  /* initialize the root */

  do {
    printf("Enter a letter: ");
    gets(s);
    root = stree(root, root, *s);
  } while(*s);

  print_tree(root, 0);

  return 0;
}

struct tree *stree(
  struct tree *root,
  struct tree *r,
  char info)
{

  if(!r) {
    r = (struct tree *) malloc(sizeof(struct tree));
    if(!r) {
      printf("Out of Memory\n");
      exit(0);
    }
    r->left = NULL;
    r->right = NULL;
    r->info = info;
    if(!root) return r; /* first entry */
    if(info < root->info) root->left = r;
    else root->right = r;
    return r;
  }

  if(info < r->info)
    stree(r, r->left, info);
  else
    stree(r, r->right, info);

  return root;
}

void print_tree(struct tree *r, int l)
{
  int i;

  if(!r) return;

  print_tree(r->right, l+1);
  for(i=0; i<l; ++i) printf(" ");
  printf("%c\n", r->info);
  print_tree(r->left, l+1);
}

listing 22
struct tree *search_tree(struct tree *root, char key)
{
  if(!root) return root;  /* empty tree */
  while(root->info != key) {
    if(key<root->info) root = root->left;
    else root = root->right;
    if(root == NULL) break;
  }
  return root;
}

listing 23
struct tree *dtree(struct tree *root, char key)
{
  struct tree *p,*p2;

  if(!root) return root; /* not found */

  if(root->info == key) { /* delete root */
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
  if(root->info < key) root->right = dtree(root->right, key);
  else root->left = dtree(root->left, key);
  return root;
}

