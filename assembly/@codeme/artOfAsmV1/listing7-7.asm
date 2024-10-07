; Listing 7-6
;
; An indirect jump state machine example

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 7-6", 0
fmtStr0     byte    "Calling StateMachine, "
            byte    "state=0, EAX=5, ECX=6", nl, 0
            
fmtStr0b    byte    "Calling StateMachine, "
            byte    "state=0, EAX=1, ECX=2", nl, 0
            
fmtStrx     byte    "Back from StateMachine, "
            byte    "EAX=%d", nl, 0
            
fmtStr1     byte    "Calling StateMachine, "
            byte    "state=1, EAX=50, ECX=60", nl, 0
            
fmtStr2     byte    "Calling StateMachine, "
            byte    "state=2, EAX=10, ECX=20", nl, 0
            
fmtStr3     byte    "Calling StateMachine, "
            byte    "state=3, EAX=50, ECX=5", nl, 0
            
            
             .data
state        qword  state0
           

            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp


; StateMachine version 2.0- using an indirect jump.

             option noscoped        ;statex labels must be global
StateMachine proc
             
             jmp    state
             
             
; State 0: Add ecx to eax and switch to State 1:

state0:      add    eax, ecx
             lea    rcx, state1
             mov    state, rcx
             ret

; State 1: Subtract ecx from eax and switch to state 2:

state1:      sub    eax, ecx
             lea    rcx, state2
             mov    state, rcx
             ret


; If this is State 2, multiply ecx by eax and switch to state 3:

state2:      imul   eax, ecx
             lea    rcx, state3
             mov    state, rcx
             ret

state3:      push   rdx          ; Preserve this 'cause it gets whacked by div.
             xor    edx, edx     ; Zero extend eax into edx.
             div    ecx
             pop    rdx          ; Restore edx's value preserved above.
             lea    rcx, state0
             mov    state, rcx
             ret

StateMachine endp
             option scoped
            
            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbp
            mov     rbp, rsp
            sub     rsp, 48         ;Shadow storage
            
            lea     rcx, state0
            mov     state, rcx        ;Just to be safe
            
; Demonstrate state 0:

            lea     rcx, fmtStr0
            call    printf
            
            mov     eax, 5
            mov     ecx, 6
            call    StateMachine
            
            lea     rcx, fmtStrx
            mov     rdx, rax
            call    printf
            
; Demonstrate state 1:

            lea     rcx, fmtStr1
            call    printf
            
            mov     eax, 50
            mov     ecx, 60
            call    StateMachine
            
            lea     rcx, fmtStrx
            mov     rdx, rax
            call    printf
            
; Demonstrate state 2:

            lea     rcx, fmtStr2
            call    printf
            
            mov     eax, 10
            mov     ecx, 20
            call    StateMachine
            
            lea     rcx, fmtStrx
            mov     rdx, rax
            call    printf
            
; Demonstrate state 3:

            lea     rcx, fmtStr3
            call    printf
            
            mov     eax, 50
            mov     ecx, 5
            call    StateMachine
            
            lea     rcx, fmtStrx
            mov     rdx, rax
            call    printf
            
; Demonstrate back in state 0:

            lea     rcx, fmtStr0b
            call    printf
            
            mov     eax, 1
            mov     ecx, 2
            call    StateMachine
            
            lea     rcx, fmtStrx
            mov     rdx, rax
            call    printf
            
            leave
            ret     ;Returns to caller
        
asmMain     endp
            end