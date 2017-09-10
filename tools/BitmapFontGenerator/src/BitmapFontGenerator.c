#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
  FILE *in, *out;

  if (argc < 4) {
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


  fputs("/*\n  This file was generated by the code generator. \n", out);
  fputs("  Changing the content manually may result in loss of changes. \n", out);
  fputs("  The code generator recommends using auto generation after changing the seed file.\n */ \n\n", out);

  fputs("#define X )*2+1\n", out);
  fputs("#define _ )*2\n", out);
  fputs("#define s ((((((((0\n", out);
  fputs("\n", out);
  fputs("char ", out);
  fputs(argv[3], out);
  fputs("[4096] = {\n", out);

  int i = 1;
  char s[12];
  while (fgets(s, 12, in) != NULL)
  {
    for (int i = 0; i < 12; i++)
    {
      switch (s[i])
      {
        case '\t':
        case '\n':
        case '\r':
        case '\v':
        case '\f':
        s[i] = ' ';
      }
    }
    if (strstr(s, "char") != NULL)
    {
      fputs("\n/*", out);
      fputs(s, out);
      fputs("*/\n", out);
    }
    else if (strlen(s) == 10)
    {
      fputs("s   ", out);
      for (int j = 0; j < 10; j++)
      {
        if (s[j] == '*')
        {
          fputc('X', out);
          fputc(' ', out);
        }
        else if (s[j] == '.')
        {
          fputc('_', out);
          fputc(' ', out);
        }
      }
      if (i != 4096)
      {
        fputs("  ,\n", out);
      }
      else
      {
        fputc('\n', out);
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
