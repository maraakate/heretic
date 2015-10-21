;This file is part of the Object to Coff (O2C) package!
;------------------------------------------------------

                p386
                ideal
                model flat,C


                dataseg

extrn           TextjeC: dataptr
TextjeAsm:      db    'hello world from assembler',0


                codeseg

extrn           printf: proc


public PrintTextC
proc            PrintTextC

                push  offset TextjeC
                call  printf
                add   sp,4
                ret

endp            PrintTextC


public PrintTextAsm
proc            PrintTextAsm

                push  offset TextjeAsm
                call  printf
                add   sp,4
                ret

endp            PrintTextAsm


public StrCaseSwap
proc            StrCaseSwap
arg StrPtr: dword

                mov   esi,[dword StrPtr]
                mov   edi,esi
@@lp1:          lodsb
                and   al,al
                jz    @@end
                cmp   al,'A'
                jc    @@skip
                xor   al,20h
@@skip:         stosb
                jmp   @@lp1
@@end:          ret

endp            StrCaseSwap

end

