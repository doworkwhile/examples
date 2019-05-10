#ifdef SDL_gameh_h_
#ifndef SDL_gameh_colors_h_
#define SDL_gameh_colors_h_

enum ColorCode {
	COLOR_BLACK, COLOR_WHITE
};

void penColor(SDL_Renderer *renderer, enum ColorCode c) {
	switch (c) {
	case COLOR_BLACK:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		break;
	case COLOR_WHITE:
	default:
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}
}

#endif
#endif