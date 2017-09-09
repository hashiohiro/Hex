#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
  FILE *in, *out;

  if (argc < 3) {
    puts("usage>makefont source.txt font.bin");
    return 1;
  }
  in = fopen(argv[1], "rb");
  out = fopen(argv[2], "wb");

  if (in == NULL) {
    puts("can't open input file.");
    return 2;
  }

  if (out == NULL) {
    puts("can't open output file.");
    return 3;
  }

  fputs("#define X )*2+1\n", out);
  fputs("#define _ )*2\n", out);
  fputs("#define  ((((((((0\n", out);
  fputs("\n", out);
  fputs("char fontbody[4096] = {\n", out);

  int i = 1;
  char s[12];
  while (fgets(s, 12, in) != NULL)
  {
    if (strstr(s, "char") != NULL)
    {
      fputs("\n/*", out);
      fputs(s, out);
      fputs("*/\n", out);
    }
    else if (strlen(s) == 10)
    {
      for (int j = 0; j < 10; j++)
      {
        if (s[j] == '*')
        {
          s[j] = 'X';
        } else if (s[j] == '.')
        {
          s[j] = '_';
        }
      }
      fputs("s    ", out);
      fputs(s, out);
      if (i != 4096)
      {
        fputs("    ,\n", out);
      }
      else
      {
        fputs("\n", out);
      }
      i += 1;
    }
  }

  fputs("};\n", out);
  fputs("\n", out);
  fputs("#undef X\n", out);
  fputs("#undef _\n", out);
  fputs("#undef s\n", out);
  fclose(in);
  fclose(out);
  return 0;
}
