listing 1
wctype_t x;

x = wctype("space");

if(iswctype(L' ', x))
  printf("Is a space.\n");

listing 2
wctrans_t x;

x = wctrans("tolower");

wchar_t ch = towctrans(L'W', x);
printf("%c", (char) ch);

