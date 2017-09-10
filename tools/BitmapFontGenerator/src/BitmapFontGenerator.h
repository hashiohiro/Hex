void StartupValidate(int argc, char** argv);
void OpenFiles(FILE **in, char *inpath, FILE **out, char *outpath);
void CloseFiles(FILE *in, FILE *out);
void RemoveSpecialChars(char *src, int length);

void WriteHeaderComment(FILE *out);
void WritePreProcessors(FILE *out);
void WriteCharArrayExpression(FILE *out, FILE* in, char *bmapName, char *bmapSize);
void WritePreProcessorUndefineExpression(FILE *out);
void WriteCommentoutText(char *str, FILE *out);
void WriteBitmapText(char *str, FILE *out);
void WriteArrayBeginExpression(char *elementType, char *arrayName, char* arraySize, FILE *out);
void WriteArrayEndExpression(FILE *out);
void WriteElementEndExpression(int currentIdx, int length, FILE *out);

