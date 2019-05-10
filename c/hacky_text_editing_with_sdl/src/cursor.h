#ifndef CURSOR_H
#define CURSOR_H


void Cursor_Init(SDL_Rect* c, int w, int h)
{
	c->x = 0;
	c->y = 0;
	c->w = w;
	c->h = h;
}

void Cursor_Locate(SDL_Rect* c, int x, int y)
{
	c->x = x * c->w;
	c->y = y * c->h;
}

#endif