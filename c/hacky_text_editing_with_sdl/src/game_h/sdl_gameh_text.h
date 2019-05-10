#ifdef SDL_gameh_h_
#ifndef SDL_gameh_text_h_
#define SDL_gameh_text_h_

#include "sdl_gameh_quitflag.h"
#include <SDL2/SDL_ttf.h>

char* defaultFontPath;
SDL_Color defaultColor = {0, 0, 0};;
TTF_Font* defaultFont;

typedef struct TextSurface {
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Color color;
	TTF_Font* font;
	char* text;
	SDL_Rect locator;
} TextSurface;

TTF_Font* enableText(int fontSize)
{
	TTF_Init();
  defaultFontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf";
	defaultFont = TTF_OpenFont(defaultFontPath, fontSize);
	if (defaultFont == NULL) {
		printf("error: font not found\n");
		setQuitFlag();
	}
	return defaultFont;
}

void disableText()
{
	TTF_CloseFont(defaultFont);
	TTF_Quit();
}

void TextSurface_Recycle(TextSurface* ts)
{
	SDL_FreeSurface(ts->surface);
	SDL_DestroyTexture(ts->texture);
}

void TextSurface_Free(TextSurface* ts)
{
	TextSurface_Recycle(ts);
	free(ts);
}

TextSurface* TextSurface_Update(TextSurface* t, SDL_Renderer* r, char* text)
{
	TextSurface_Recycle(t);
	t->text = text;
	t->surface = TTF_RenderText_Solid(t->font, t->text, t->color);
	t->texture = SDL_CreateTextureFromSurface(r, t->surface);
	SDL_QueryTexture(t->texture, NULL, NULL, &t->locator.w, &t->locator.h);
}

TextSurface* TextSurface_Create(TextSurface* t, SDL_Renderer* r, char* text)
{
	t->color = defaultColor;
	t->font = defaultFont;
	return TextSurface_Update(t, r, text);
}

void TextSurface_Locate(TextSurface* ts, int x, int y)
{
	ts->locator.x = x;
	ts->locator.y = y;
}

TextSurface* TextSurface_CreateAt(SDL_Renderer* r, char* text, int x, int y)
{
	TextSurface* t = (TextSurface*) calloc(1, sizeof(TextSurface));
	TextSurface_Create(t, r, text);
	TextSurface_Locate(t, x, y);
	return t;
}

void TextSurface_Render(TextSurface* ts, SDL_Renderer* r)
{
	SDL_RenderCopy(r, ts->texture, NULL, &ts->locator);
}

#endif
#endif
