; Listing 4-6
;
; Calling C Standard Library string functions


          option  casemap:none

nl        =       10
maxLen    =     256

          .const
ttlStr    byte  "Listing 4-6", 0
prompt    byte  "Input a string: ", 0
fmtStr1   byte  "After strncpy, resultStr='%s'", nl, 0
fmtStr2   byte  "After strncat, resultStr='%s'", nl, 0
fmtStr3   byte  "After strcmp (3), eax=%d", nl, 0
fmtStr4   byte  "After strcmp (4), eax=%d", nl, 0
fmtStr5   byte  "After strcmp (5), eax=%d", nl, 0
fmtStr6   byte  "After strchr, rax='%s'", nl, 0
fmtStr7   byte  "After strstr, rax='%s'", nl, 0
fmtStr8   byte  "resultStr length is %d", nl, 0

str1      byte  "Hello, ", 0
str2      byte  "World!", 0
str3      byte  "Hello, World!", 0
str4      byte  "hello, world!", 0      
str5      byte  "HELLO, WORLD!", 0      
        
          .data
strLength dword ?
resultStr byte  maxLen dup (?)

        
        .code
        externdef readLine:proc
        externdef printf:proc
        externdef malloc:proc
        externdef free:proc
        
; Some C standard library string functions:
;
; size_t strlen(char *str)
 
        externdef strlen:proc

; char *strncat(char *dest, const char *src, size_t n)
 
        externdef strncat:proc
        
; char *strchr(const char *str, int c)

        externdef strchr:proc
        
; int strcmp(const char *str1, const char *str2)

        externdef strcmp:proc

; char *strncpy(char *dest, const char *src, size_t n)

        externdef strncpy:proc
        
; char *strstr(const char *inStr, const char *search4)

        externdef strstr:proc
         
        

; Return program title to C++ program:

         public getTitle
getTitle proc
         lea rax, ttlStr
         ret
getTitle endp

; Here is the "asmMain" function.

        
        public  asmMain
asmMain proc

; "Magic" instruction offered without
; explanation at this point:

        sub     rsp, 48


; Demonstrate the strncpy function to copy a
; string from one location to another:

        lea     rcx, resultStr  ; Destination string
        lea     rdx, str1       ; Source string
        mov     r8, maxLen      ; Max number of chars to copy
        call    strncpy
        
        lea     rcx, fmtStr1
        lea     rdx, resultStr
        call    printf
        
; Demonstrate the strncat function to concatenate str2 to
; the end of resultStr:

        lea     rcx, resultStr
        lea     rdx, str2
        mov     r8, maxLen
        call    strncat
        
        lea     rcx, fmtStr2
        lea     rdx, resultStr
        call    printf
        
; Demonstrate the strcmp function to compare resultStr
; with str3, str4, and str5:

        lea     rcx, resultStr
        lea     rdx, str3
        call    strcmp
        
        lea     rcx, fmtStr3
        mov     rdx, rax
        call    printf

        lea     rcx, resultStr
        lea     rdx, str4
        call    strcmp
        
        lea     rcx, fmtStr4
        mov     rdx, rax
        call    printf

        lea     rcx, resultStr
        lea     rdx, str5
        call    strcmp
        
        lea     rcx, fmtStr5
        mov     rdx, rax
        call    printf
        
; Demonstrate the strchr function to search for
; ',' in resultStr

        lea     rcx, resultStr
        mov     rdx, ','
        call    strchr
        
        lea     rcx, fmtStr6
        mov     rdx, rax
        call    printf
        
; Demonstrate the strstr function to search for
; str2 in resultStr

        lea     rcx, resultStr
        lea     rdx, str2
        call    strstr
        
        lea     rcx, fmtStr7
        mov     rdx, rax
        call    printf

; Demonstrate a call to the strlen function

        lea     rcx, resultStr
        call    strlen
        
        lea     rcx, fmtStr8
        mov     rdx, rax
        call    printf
                 

        add     rsp, 48
        ret     ;Returns to caller
asmMain endp
        end