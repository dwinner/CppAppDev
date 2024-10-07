; Listing 5-14
;
; Passing a large object by reference

        option  casemap:none

nl          =       10
NumElements =       24

Pt          struct
x           byte    ?
y           byte    ?
Pt          ends



            .const
ttlStr      byte    "Listing 5-14", 0
fmtStr1     byte    "RefArrayParm[%d].x=%d ", 0
fmtStr2     byte    "RefArrayParm[%d].y=%d", nl, 0
        
            .data
index       dword   ?
Pts         Pt      NumElements dup ({})
        
            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp


ptArray     equ     <[rbp+16]> 
RefAryParm  proc
            push    rbp
            mov     rbp, rsp
            
            mov     rdx, ptArray
            xor     rcx, rcx        ;RCX = 0
            
; while ecx < NumElements, initialize each
; array element. x = ecx/8, y=ecx % 8

ForEachEl:  cmp     ecx, NumElements
            jnl     LoopDone
            
            mov     al, cl
            shr     al, 3   ;AL = ecx / 8
            mov     [rdx][rcx*2].Pt.x, al
            
            mov     al, cl
            and     al, 111b ;AL = ecx % 8
            mov     [rdx][rcx*2].Pt.y, al
            inc     ecx
            jmp     ForEachEl
                        
LoopDone:   leave
            ret
RefAryParm  endp

; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbp
            mov     rbp, rsp
            sub     rsp, 40
        
; Initialize the array of points:

            lea     rax, Pts
            mov     [rsp], rax      ;Store address on stack
            call    RefAryParm

; Display the array:
            
            mov     index, 0
dispLp:     cmp     index, NumElements
            jnl     dispDone
            
            lea     rcx, fmtStr1
            mov     edx, index              ;zero extends!
            lea     r8, Pts                 ;Get array base
            movzx   r8, [r8][rdx*2].Pt.x    ;Get x field
            call    printf
            
            lea     rcx, fmtStr2
            mov     edx, index              ;zero extends!
            lea     r8, Pts                 ;Get array base
            movzx   r8, [r8][rdx*2].Pt.y    ;Get y field
            call    printf
            
            inc     index
            jmp     dispLp
            
            
; Clean up, as per Microsoft ABI:

dispDone:
            leave
            ret     ;Returns to caller
        
asmMain     endp
            end