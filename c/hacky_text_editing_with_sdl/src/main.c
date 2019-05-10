#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "./game_h/sdl_gameh.h"

#define SCREEN_W 640
#define SCREEN_H 480

#define FONT_WIDTH 12
#define FONT_HEIGHT 20

#define MAX_LINES (SCREEN_H / FONT_HEIGHT)
#define RECORD_LEN MAX_LINES - 1
#define STATUS_Y (FONT_HEIGHT * MAX_LINES) - FONT_HEIGHT
#define LINE_LEN (SCREEN_W / FONT_WIDTH)

#include "text_area.h"
#include "line_list_file_ops.h"

TextArea* t;
char* statusStr;
TextSurface* status;
char* readFilename;
char* defaultFilename = "/tmp/main.c";

void Status_Render()
{
	TextSurface_Update(status, engine.renderer, status->text);
}

void Status_Set(char* c)
{
	strcpy(statusStr, c);
	Status_Render();
}


void gameSetup()
{
	t = TextArea_Init(RECORD_LEN, LINE_LEN - 1, FONT_WIDTH, FONT_HEIGHT, engine.renderer);
	statusStr = (char*) calloc(LINE_LEN, sizeof(char));
	strcpy(statusStr, "Hello World");
	status = TextSurface_CreateAt(engine.renderer, statusStr, 0, STATUS_Y);

	if (readFilename) {
		LineListFileOps_Load(t->list, readFilename);
		TextArea_UpdateRender(t);
	}
};

void gameEventing() {
	int mod = engine.event.key.keysym.mod;
	if (engine.event.type == SDL_KEYDOWN) {
		switch(engine.event.key.keysym.sym){
		case SDLK_BACKSPACE:
			TextArea_Backspace(t);
			Status_Set("(BS)");
			break;
		case SDLK_RETURN:
			TextArea_AdvanceLine(t);
			Status_Set("(NL)");
			break;
		case SDLK_UP:
			TextArea_AdvanceUp(t);
			break;
		case SDLK_RIGHT:
			TextArea_AdvanceChar(t);
			Status_Set("\273");
			break;
		case SDLK_DOWN:
			TextArea_AdvanceDown(t);
			break;
		case SDLK_LEFT:
			TextArea_PreviousChar(t);
			Status_Set("\253");
			break;
		case SDLK_s:
			if (mod & KMOD_CTRL) {
				if (readFilename) {
					LineListFileOps_Write(t->list, readFilename);
				} else {
					LineListFileOps_Write(t->list, defaultFilename);
				}
				Status_Set("saved");
			}
			break;
		case SDLK_k:
			if (mod & KMOD_CTRL && mod & KMOD_SHIFT) {
				TextArea_DeleteLine(t);
				Status_Set("delete line");
			}
			break;
		}
	} else if (engine.event.type == SDL_TEXTINPUT) {
		char* input = engine.event.text.text;
		TextArea_Input(t, input);

		strcpy(statusStr, "added: ");
		strcat(statusStr, input);
		Status_Render();
	}
};

void gameUpdating() {};

void gameRendering()
{
	TextArea_Render(t);
	TextSurface_Render(status, engine.renderer);
};
void gameFree()
{
	TextArea_Free(t);
	free(status);
};

int main(int argc, char* argv[])
{
	if (argc >= 2) {
		readFilename = argv[1];
		printf("loading file: %s\n", readFilename);
	}
	start(SCREEN_W, SCREEN_H, -1, -1);
	return 0;
}