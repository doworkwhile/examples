#ifndef LINE_LIST
#define LINE_LIST

#include "line.h"

typedef struct {
  Line** store;
  int lines;
  int width;
  int xpos, ypos;
} LineList;

LineList* LineList_Init(int lines, int chars)
{
  LineList* l = (LineList*) calloc(1, sizeof(LineList));
  l->lines = lines;
  l->width = chars;
  l->store = (Line**) calloc(lines, sizeof(Line*));

  for (int i = 0; i < lines; i++) {
    l->store[i] = Line_Init(chars);
    Line_Clear(l->store[i]);
  }

  return l;
}

void LineList_Free(LineList* l)
{
  for (int i = 0; i < l->lines; i++) {
    Line_Free(l->store[i]);
  }
  free(l->store);
  free(l);
}

Line* LineList_CurrentLine(LineList* list)
{
  return list->store[list->ypos];
}


int LineList_CanAdvanceChar(LineList* list)
{
  return !Line_IsFull(LineList_CurrentLine(list));
}

int LineList_CanAdvanceLine(LineList* list)
{
  return list->ypos < list->lines - 1;
}

int LineList_CanBackspaceChar(LineList* list)
{
  return list->xpos > 0;
}

int LineList_CanBackspaceLine(LineList* list)
{
  return list->ypos > 0;
}

int LineList_ShouldBackspaceLine(LineList* list)
{
  return LineList_CanBackspaceLine(list) && !LineList_CanBackspaceChar(list);
}

int LineList_AllFull(LineList* list)
{
  return !LineList_CanAdvanceChar(list) && !LineList_CanAdvanceLine(list);
}

int LineList_Empty(LineList* list)
{
  return list->xpos == 0 && list->ypos == 0;
}

int LineList_GetLastIndexOfCurrentLine(LineList* list) {
  return Line_GetLastIndex(LineList_CurrentLine(list));
}

void LineList_SeekLineEnd(LineList* list)
{
  list->xpos = LineList_GetLastIndexOfCurrentLine(list) + 1;
}

void LineList_AdvanceLine(LineList* list, int shouldSeekEnd)
{
  if (LineList_CanAdvanceLine(list)) {
    list->ypos++;
  }

  if (shouldSeekEnd) {
    LineList_SeekLineEnd(list);
  } else {
    list->xpos = 0;
  }
}

int LineList_ShouldAdvanceLine(LineList* list)
{
  return !LineList_CanAdvanceChar(list) && LineList_CanAdvanceLine(list);
}

void LineList_AddChar(LineList* list, char* c)
{
  LineList_CurrentLine(list)->contents[list->xpos] = *c;
  list->xpos++;
}

void LineList_BackspaceLine(LineList* list)
{
  if (LineList_CanBackspaceLine(list)) {
    list->ypos--;
    LineList_SeekLineEnd(list);
  }
}

void LineList_RemoveChar(LineList* list)
{
  list->xpos--;
  LineList_CurrentLine(list)->contents[list->xpos] = ' ';
}

void LineList_Status(LineList* list)
{
  printf("\ndbg\n");
  printf("all full: %d\n", LineList_AllFull(list));
  printf("can adv char: %d\n", LineList_CanAdvanceChar(list));
  printf("can adv line: %d\n", LineList_CanAdvanceLine(list));
  printf("can bck char: %d\n", LineList_CanBackspaceChar(list));
  printf("can bck line: %d\n", LineList_CanBackspaceLine(list));
  printf("should adv line: %d\n", LineList_ShouldAdvanceLine(list));
}

int LineList_Input(LineList* list, char* c)
{
  // LineList_Status(list);


  if (LineList_AllFull(list)) {
    return 0;
  }

  if (LineList_ShouldAdvanceLine(list)) {
    LineList_AdvanceLine(list, 1);
    LineList_AddChar(list, c);
    return 1;
  }

  LineList_AddChar(list, c);
  return 0;
}

int LineList_Backspace(LineList* list)
{
  if (LineList_Empty(list)){
    return 0;
  }

  if (LineList_ShouldBackspaceLine(list)) {
    LineList_BackspaceLine(list);
    if (!LineList_CanAdvanceChar(list)) {
      LineList_RemoveChar(list);
    }
    return 1;
  }

  LineList_RemoveChar(list);
  return 0;
}

void LineList_AdvanceChar(LineList* list)
{
  if (LineList_AllFull(list)) {
    return;
  }

  int li = LineList_GetLastIndexOfCurrentLine(list);
  if (LineList_ShouldAdvanceLine(list) || li+1 == list->xpos) {
    LineList_AdvanceLine(list, 1);
    return;
  }

  if (LineList_CanAdvanceChar(list)) {
    list->xpos++;
  }
}

void LineList_PreviousChar(LineList* list)
{
  int shouldBack = LineList_ShouldBackspaceLine(list);
  if (shouldBack) {
    LineList_BackspaceLine(list);
    return;
  }

  if (LineList_CanBackspaceChar(list)) {
    list->xpos--;
  }
}

void LineList_AdvanceDown(LineList* list)
{
  if (!LineList_CanAdvanceLine(list)) {
    return;
  }

  int oldx = list->xpos;
  LineList_AdvanceLine(list, 0);
  int xmax = LineList_GetLastIndexOfCurrentLine(list) + 1;

  if (xmax < oldx) {
    list->xpos = xmax;
  } else if (xmax >= oldx) {
    list->xpos = oldx;
  }
}

void LineList_AdvanceUp(LineList* list)
{
  if (!LineList_CanBackspaceLine(list)) {
    return;
  }

  int oldx = list->xpos;
  LineList_BackspaceLine(list);
  int xmax = LineList_GetLastIndexOfCurrentLine(list) + 1;

  if (xmax < oldx) {
    list->xpos = xmax;
  } else if (xmax >= oldx) {
    list->xpos = oldx;
  }
}


#endif