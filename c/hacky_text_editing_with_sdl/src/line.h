#ifndef LINE_H
#define LINE_H

typedef struct {
	char* contents;
  int len;
  int max;
} Line;

Line* Line_Init(int chars)
{
  Line* l = (Line*) calloc(1, sizeof(Line));
  l->len = chars;
  l->max = chars - 1;
  l->contents = (char*) calloc(chars, sizeof(char));
  return l;
}

void Line_Free(Line* l)
{
  free(l->contents);
  free(l);
}

void Line_Clear(Line* line)
{
  for (int j = 0; j <= line->max; j++) {
    line->contents[j] = '\0';
  }
}

int Line_GetLastIndex(Line* line)
{
  int last = -1;
  for (int i = 0; i <= line->max; i++) {
    char letter = line->contents[i];
    if (letter != ' ' && letter != '\0') {
      last = i;
    }
  }
  return last;
}

int Line_IsFull(Line* line)
{
  return Line_GetLastIndex(line) >= line->max;
}



#endif
