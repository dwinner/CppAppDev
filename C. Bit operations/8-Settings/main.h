#ifndef MAIN_H
#define MAIN_H

#define ID_MASK     0xFF
#define SIZE_MASK   0x7F00
#define LEFT        0x00000
#define CENTER      0x08000
#define RIGHT       0x10000
#define ALIGN_MASK  0x18000
#define REGULAR     0x00000
#define BOLD        0x20000
#define ITALIC      0x40000
#define UNDERLINE   0x80000
#define STYLE_MASK  0xE0000
#define SIZE_SHIFT  8

typedef unsigned long Font;

char doMenu(Font* pFont);
char getChoice(const char* pChoice);
void showFont(Font font);
void getId(Font* pFont);
void getSize(Font* pFont);
void getAlign(Font* pFont);

inline static void eatLine(void)
{
   while (getchar() != '\n')
   {
   }
}

inline static void showMenu(void)
{
   puts("f)change font     s)change size     a)change alignment");
   puts("b)toggle bold     i)toggle italic   u)toggle underline");
}

#endif // MAIN_H
