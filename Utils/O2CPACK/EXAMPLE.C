/* This file is part of the Object to Coff (O2C) package!
   ------------------------------------------------------ */

char TextjeC[]="hello world from c";

void main(void)
{
PrintTextAsm();
printf("\n");

PrintTextC();
printf("\n");

StrCaseSwap(&TextjeC);
PrintTextC();
printf("\n");
}

