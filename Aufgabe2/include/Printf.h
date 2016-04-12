#ifndef CUSTOM_PRINTF_H
  #define CUSTOM_PRINTF_H

/*
TODO
%d fuer signed int
%u fuer  unsigned int
%c fue ein einzelnes Zeichen
%s fuer eine Zeichenkette
%x fuer die Ausgabe in Hexadezimalform
%b fuer die Ausgabe in Binaerform
*/
char* Printf(char* dst, const void* end, const char* fmt, ...);


#endif // CUSTOM_PRINTF_H
