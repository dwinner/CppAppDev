; csetToPCset.asm
;
; This function converts a cset value to
; one or two 16-byte strings that can be
; used with the PCMPxSTRy instructions
; to skip over characters in a string
; that are members of the character set.
;
; This function will attempt to create
; a single string containing (up to) 8
; pairs of ranges (two characters per
; range) that represent the character
; set. If the result would require more
; than 16 bytes to represent, then it 
; attempts to extract singletons and
; 2-element pairs from the range string
; to create a second string with individual
; characters from the set. If the resulting
; two strings (EqualRange and EqualAny)
; still require more than 16 bytes each,
; this function fails and stores -1 into
; the anyStr and rangeStr fields of the
; destination pcset object.
;
; On entry:
;
;   RSI-    Points at the source cset value.
;   RDI-    Points at the destination pcset value.
;
; On Exit-
;
;   RDI-    pcset object is filled with either
;           one or two strings (rangeStr and
;           anyStr) or they are disabled
;           by placing -1 values in their first
;           four bytes.
;
; Notes:
;           If the cset can be converted to
;           a single rangeStr, this function
;           stores -1 in the anyStr.
;           If the cset requires both a range
;           and an any string, this function
;           stores the strings in both fields.
;           If the set cannot be represented
;           by a single rangeStr, but it can
;           be represented by a single anyStr,
;           then this function stores -1 in
;           rangeStr and the cset string in
;           anyStr. If the function fails to 
;           create PCMPxSTRy compatible strings, 
;           it stores -1 in both the rangeStr
;           and anyStr fields.
 
            include cset.inc
            include aoalib.inc

            .code
csetToPCset proc
tempStr     textequ <[rbp-8]>       ;Local pointer to string

rdiSave     textequ <[rbp+8]>

_anyTag     textequ <dword ptr [rdi].pcset.pcs.tags.anyTag>
_rangeTag   textequ <dword ptr [rdi].pcset.pcs.tags.rangeTag>
_rangeStr   textequ <qword ptr [rdi].pcset.pcs.pstrs.rangeStr>
_anyStr     textequ <byte ptr [rdi].pcset.pcs.pstrs.anyStr>
_anyStrQ    textequ <qword ptr [rdi].pcset.pcs.pstrs.anyStr>

            push    rax
            push    rbx
            push    rcx
            push    rsi
            push    rdi
            push    rbp
            mov     rbp, rsp

; Create room on the stack to hold a
; 256-charater strObject string and
; initialize that string to the empty
; string (this also allocates storage
; for the tempStr local variable that
; will hold a pointer to the string):

            sub     rsp, 300
            and     rsp, -16
            lea     rax, [rsp+sohs]
            mov     tempStr, rax
            mov     [rax-sohs].strObject.maxLength, 256
            mov     [rax-sohs].strObject.strLength, 0
            mov     byte ptr [rax], 0
            
; Before doing anything else, see if the source cset
; and destination pcset are the same. If they are not,
; then copy the 32 bytes of character set data from
; the cset variable to the pcset variable (skip this
; operation if they are the same variable and this
; call is simply setting up the rangeStr and anyStr
; fields of that pcset variable):

            cmp     rsi, rdi
            je      dontCopyCset
            
; Not the same object; copy the cset data (just use
; RAX- faster than preserving and restoring an XMM
; register):

            mov     rcx, [rsi]
            mov     [rdi], rcx
            mov     rcx, [rsi+8]
            mov     [rdi+8], rcx
            mov     rcx, [rsi+16]
            mov     [rdi+16], rcx
            mov     rcx, [rsi+24]
            mov     [rdi+24], rcx

dontCopyCset:       

; Convert the source cset to a string using the
; csetToRange function. Use the string just allocated
; on the stack. Note that a 256-byte (maxLength) string
; is large enough to hold *any* possible character set.
; Note that RAX still contains the address of the string
; allocated on the stack.

            mov     rdi, rax        ;RDI must point at string
            call    csetToRange
	
            mov     rsi, rdi        ;RSI = temp string
            mov     rdi, rdiSave    ;RDI = pcset object
            
; Get the length of the new string. If it's greater than
; 16 characters in length, we have to break it up. If it's
; less than 16 characters, we can use it as the new
; rangeStr field of the pcset object.

            mov     eax, [rsi-sohs].strObject.strLength
            cmp     eax, 16
            ja      mustSplit
            
; The range string is less than 16 characters long.
; Copy the string, with zero filling, to the rangeStr
; field of the destination pcset variable. Begin by
; initializing the rangeStr bytes to zeros and the
; anyTag field to -1

            
            xor     rcx, rcx
            mov     _rangeStr,      rcx
            mov     _rangeStr[8],   rcx
            
            dec     ecx     ;ECX=-1
            mov     [rdi].pcset.pcs.tags.anyTag, ecx
            
; Copy the bytes from the string on the stack to
; the pcset rangeStr field;

            mov     ecx, [rsi-sohs].strObject.strLength
            lea     rdi, _rangeStr
            cld
    rep     movsb
            jmp     allDone
            
; If the range string was too big to fit into 16 bytes,
; then come down here and see if we can convert it to
; an anyStr or a rangeStr/anyStr combination.
;
; The conversion algorithm is as follows:
;
; 1. Scan through the string on the stack searching for
;    ranges of a single char (pairs of bytes with the
;    same ASCII code). Move those ranges (as a single
;    character) to the anyStr. 
; 2. If, during step (1) anyStr's length would exceed 
;    16 characters at any point, see if rangeStr's
;    length as fallen below 16 characters. If so,
;    then return the two (less than 16 characters long)
;    strings as the function result. If both strings
;    would be longer than 16 characters, set the
;    anyTag and rangeTag fields to -1; the original
;    character set cannot be converted to a pair of
;    character set strings.
; 3. Scan through the string on the stack searching
;    for sequential pairs of characters (that is,
;    the second character of a pair has a value that
;    is one greater than the first character of the
;    pair). Move those two characters to the
;    anyStr.
; 4. If, during step (3) anyStr's length would exceed 
;    16 characters at any point, see if rangeStr's
;    length as fallen below 16 characters. If so,
;    then return the two (less than 16 characters long)
;    strings as the function result. If both strings
;    would be longer than 16 characters, set the
;    anyTag and rangeTag fields to -1; the original
;    character set cannot be converted to a pair of
;    character set strings.
;
; 5. If at any point during steps (2) or (4) the
;    rangeStr's length becomes zero, set rangeTag
;    to -1 and return (anyStr contains the whole
;    character set).
;
; 6. At the end of the process, if the rangeStr
;    length is still greater than 16 bytes, store
;    -1 in the anyTag and rangeTag fields and return;
;    if the length is less than 16 characters, then
;    copy the rangeStr data (still on the stack)
;    to the rangeStr field of the destination pcset.

; Begin scan for individual characters.
; Note: at this point, RSI points at the temp string
; and RDI points at the pcset object.

mustSplit:

            xor     rcx, rcx
            xor     rbx, rbx
            
; Initialize the anyStr and rangeStr field2 with zeros 
; before we start writing data to those strings:

            mov     _anyStrQ,      rcx
            mov     _anyStrQ[8],   rcx
            mov     _rangeStr,     rcx
            mov     _rangeStr[8],  rcx

; If the character set is empty, fail by storing
; -1 into the tag fields:

            cmp     ecx, [rsi-sohs].strObject.strLength
            je      failure
            
copySingles:
            mov     al, [rsi][rcx*1] ;*2 for pairs of chars
            cmp     al, [rsi][rcx*1+1]
            jne     dontCopy
            cmp     rbx, 16
            jae     anyTooBig
            mov     _anyStr[rbx*1], al
            inc     rbx
            
; Mark source characters as copied:

            mov     byte ptr [rsi][rcx*1], 0
            mov     byte ptr [rsi][rcx*1+1], 0
            
; See if we've reached the end of the string on the
; stack:

dontCopy:   add     rcx, 2
            cmp     ecx, [rsi-sohs].strObject.strLength
            jb      copySingles
            call    cleanupStr      ;Remove "holes" in string
            
; Now make a second pass checking for pairs of characters
; whose ASCII codes are one apart.

            xor     rcx, rcx

; If the source string is empty, we've copied all the
; data to the anyStr. Immediately succeed:

            cmp     ecx, [rsi-sohs].strObject.strLength
            je      success
            
copyDoubles:
            mov     al, [rsi][rcx*1]   ;*2 for pairs of chars
            inc     al                 ;Check for values that 
            cmp     al, [rsi][rcx*1+1] ; are 1 apart
            jne     dontCopy2
            
; Have we exceeded the length of the anyStr?

            cmp     rbx, 15         ;15 because we copy 2 bytes
            jae     anyTooBig
            
; Add the two characters to the anyStr:

            mov     _anyStr[rbx*1+1], al
            dec     al
            mov     _anyStr[rbx*1], al
            add     rbx, 2
            
; Mark source characters as copied:

            mov     byte ptr [rsi][rcx*1], 0
            mov     byte ptr [rsi][rcx*1+1], 0
            
; See if we've reached the end of the string on the
; stack:

dontCopy2:  add     rcx, 2
            cmp     ecx, [rsi-sohs].strObject.strLength
            jb      copyDoubles
            call    cleanupStr      ;Remove "holes" in string
            
; If the temporary string on the stack is now less than or
; equal to 16 bytes longs, we've succeeded.

            cmp     [rsi-sohs].strObject.strLength, 16
            ja      failure

; At this point, we've succeeded. If the temporary string
; on the stack is the empty string, store -1 into the
; rangeTag field and return. If the string is not
; empty, copy it to the rangeStr field of the pcset object.
;
; The RBX register contains the length of the anyStr field.
; If it were zero, then there would have been no single or 
; double characters added to the anyStr. However, we only
; get to this point if the source string is empty or if
; it is less than 16 characters in length. Therefore, we
; can assume that RBX is not zero at this point (because
; the source string wouldn't be less than 16 bytes long
; here if we hadn't removed characters from it).
            
success:    cmp     [rsi-sohs].strObject.strLength, 0
            jne     have2Strs
            
; Temp string is empty, so set the rangeTag field to -1:

            mov     _rangeTag, -1
            jmp     allDone
            
; If the temp string was not empty, then we have a rangeStr
; and an anyStr in the pcset object. The anyStr has already
; been filled in. Copy the rangeStr from the temporary string
; on the stack to the rangeStr field of the pcset object.
; (Note: the string on the stack has been cleaned up at this
; point; that is, it has had all the holes removed.)

have2Strs:  mov     ecx, [rsi-sohs].strObject.strLength
            lea     rdi, _rangeStr
            cld
    rep     movsb
            
            
allDone:    leave           ;Deallocate string on stack
            pop     rdi
            pop     rsi
            pop     rcx
            pop     rbx
            pop     rax
            ret
            
; We're about to exceed 16 characters in anyStr. 
; Before failing, see if the size of the range string 
; has dropped below 16 characters (in which case
; we can succeed).

anyTooBig:  call    cleanupStr      ;Remove holes from string
            cmp     [rsi-sohs].strObject.strLength, 16
            jbe     have2Strs

; If we failed, set the anyTag and rangeTag fields to -1:
            
failure:    mov     _rangeTag, -1
            mov     _anyTag, -1
            jmp     allDone
                             
csetToPCset endp


; cleanupStr-
;
; A short utility function that
; scans through the string pointed
; at by RSI (the temporary string
; on the stack) and removes any
; "holes" in the string. "Holes"
; are marked by zero bytes.

cleanupStr  proc
            xor     rcx, rcx
            mov     rbx, rsi
cleanLp:    mov     al, [rsi][rcx*1] ;Look for a "hole" (0 byte)
            cmp     al, 0            ; in the string
            je      skip0            ;If found, don't copy,
            mov     [rbx], al        ; else move byte to
            inc     rbx              ; close up the holes
skip0:      inc     rcx
            cmp     ecx, [rsi-sohs].strObject.strLength
            jb      cleanLp
            
; Compute the new length of the string and
; zero terminate it:

            mov     byte ptr [rbx], 0
            sub     rbx, rsi
            mov     [rsi-sohs].strObject.strLength, ebx
            ret
cleanupStr  endp
            end   
