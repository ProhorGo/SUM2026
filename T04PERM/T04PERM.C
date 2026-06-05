/* PG3, 09-3, 04.06.2026 */

#include <stdio.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>

#define MAX 3
INT P[MAX] = {1, 2, 3};
BOOL IsParity;

VOID Swap( INT *a, INT *b )
{
  INT tmp = *a;
  *a = *b;
  *b = tmp;
}

VOID Store( VOID )
{
  FILE *F;
  INT i;

  F = fopen("PERM.txt", "a");
  if (F == NULL)
    return;
  for (i = 0; i < MAX - 1; i++)
    fprintf(F, "%d, ", P[i]);
  fprintf(F, "%d - parity: %s\n", P[MAX - 1], IsParity ? "even" : "odd");
  fclose(F);
}                                     

VOID Perm( INT n )
{
  INT i;

  if (n >= MAX)
    return;
  for (i = n; i < MAX; i++)
  {
    Swap(&P[n], &P[i]);
    Perm(n + 1);
  }
}

VOID Go( INT Pos )
{
  INT i;

  if (Pos == MAX)
    Store();
  else
  {
    for (i = Pos; i < MAX; i++)
    {
      Swap(&P[Pos], &P[i]);
      Go(Pos + 1);
      Swap(&P[Pos], &P[i]);
    }
  }
}

void main( void )
{
  Go(0);
}