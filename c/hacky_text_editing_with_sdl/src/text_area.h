#ifndef TEXTAREA_H
#define TEXTAREA_H

#include "cursor.h"
#include "line_list.h"

typedef struct {
	int lines;
	SDL_Renderer* renderer;
	LineList* list;
	TextSurface** surfaces;
	SDL_Rect cursor;
} TextArea;

TextArea* TextArea_Init(int lines, int chars, int fontWidth, int fontHeight, SDL_Renderer* r)
{
	TextArea* t = (TextArea*) calloc(1, sizeof(TextArea));
	t->lines = lines;
	t->renderer = r;
	t->surfaces = (TextSurface**) calloc(lines, sizeof(TextSurface*));
	t->list = LineList_Init(lines, chars);
	Cursor_Init(&t->cursor, fontWidth, fontHeight);

	for (int i = 0; i < lines; i++) {
		t->surfaces[i] = TextSurface_CreateAt(
			r,
			t->list->store[i]->contents,
			0, i * fontHeight
		);
	}
	return t;
}

void TextArea_CursorRelocate(TextArea* t)
{
	Cursor_Locate(&t->cursor, t->list->xpos, t->list->ypos);
}

void TextArea_Free(TextArea* t)
{
	for (int i = 0; i < t->lines; i++) {
		TextSurface_Free(t->surfaces[i]);
	}
	free(t->surfaces);
	LineList_Free(t->list);
	free(t);
}

void TextArea_Render(TextArea* t)
{
	for (int i = 0; i < t->lines; i++) {
		TextSurface_Render(t->surfaces[i], t->renderer);
	}
	penColor(t->renderer, COLOR_BLACK);
	SDL_RenderDrawRect(t->renderer, &t->cursor);
}

void TextArea_UpdateRender(TextArea* t) {
	for (int i = 0; i < t->lines; i++) {
		TextSurface_Update(t->surfaces[i], t->renderer, t->list->store[i]->contents);
		int contentLen = Line_GetLastIndex(t->list->store[i]);
		if (contentLen > 0) {
			t->list->ypos = i;
			t->list->xpos = LineList_GetLastIndexOfCurrentLine(t->list) + 1;
		}
	}
	TextArea_CursorRelocate(t);
	TextArea_Render(t);
}

void TextArea_Input(TextArea* t, char* c)
{
	int advancedLine = LineList_Input(t->list, c);
	TextSurface* whichSurface;
	Line* whichLine;

	if (advancedLine) {
		whichSurface = t->surfaces[t->list->ypos-1];
		whichLine = t->list->store[t->list->ypos-1];
		TextSurface_Update(whichSurface, t->renderer, whichLine->contents);
	}
	whichSurface = t->surfaces[t->list->ypos];
	whichLine = LineList_CurrentLine(t->list);
	TextSurface_Update(whichSurface, t->renderer, whichLine->contents);
	TextArea_CursorRelocate(t);
}

void TextArea_Backspace(TextArea* t)
{
	int didBackspaceLine = LineList_Backspace(t->list);
	TextSurface* whichSurface = t->surfaces[t->list->ypos];
	Line* whichLine = LineList_CurrentLine(t->list);
	TextSurface_Update(whichSurface, t->renderer, whichLine->contents);
	TextArea_CursorRelocate(t);
}

void TextArea_AdvanceLine(TextArea* t)
{
	LineList_AdvanceLine(t->list, 0);
	TextSurface_Update(
		t->surfaces[t->list->ypos],
		t->renderer,
		LineList_CurrentLine(t->list)->contents
	);
	TextArea_CursorRelocate(t);
}

void TextArea_AdvanceChar(TextArea* t)
{
	LineList_AdvanceChar(t->list);
	TextArea_CursorRelocate(t);
}

void TextArea_PreviousChar(TextArea* t)
{
	LineList_PreviousChar(t->list);
	TextArea_CursorRelocate(t);
}

void TextArea_DeleteLine(TextArea* t)
{
	t->list->xpos = t->list->width;
	while(LineList_CanBackspaceChar(t->list)) {
		LineList_RemoveChar(t->list);
	}
	TextSurface_Update(
		t->surfaces[t->list->ypos],
		t->renderer,
		LineList_CurrentLine(t->list)->contents
	);
	LineList_BackspaceLine(t->list);
	TextArea_CursorRelocate(t);
}

void TextArea_AdvanceDown(TextArea* t)
{
	LineList_AdvanceDown(t->list);
	TextArea_CursorRelocate(t);
}


void TextArea_AdvanceUp(TextArea* t)
{
	LineList_AdvanceUp(t->list);
	TextArea_CursorRelocate(t);
}

#endif