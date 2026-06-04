/* Goncharov Prohor, 09-3, 01.06.2026 */

#include <stdio.h>
#include <windows.h>
#include <string.h>

void main( void )
{
  int a = 0, b = 100, m = (a + b) / 2, run = 1;
  char s[100], str[100];

  if (MessageBox(NULL, "Zagaday number", "IGRA", MB_OKCANCEL))
  {
    while (run)
    {
      m = (a + b) / 2;
      sprintf(str, "Number bolshe %i", m);
      strcpy(s, MessageBox(NULL, str, "IGRA", MB_YESNOCANCEL));
      if (s == IDYES)
        a = m;
      else if (s == IDNO)
        b = m;
      else if (s == IDCANCEL)
        run = 0;
    }
  }
}