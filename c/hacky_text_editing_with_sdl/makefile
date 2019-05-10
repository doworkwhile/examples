GPP_FLAGS   = -lSDL2 -lSDL2_ttf
FILES       = src/*.c
NAME        = hacky_text_editing_with_sdl
OUT         = bin/$(NAME)

default:
	gcc $(FILES) $(GPP_FLAGS) -o $(OUT)

clean:
	rm $(OUT) 2>/dev/null || true

run: default
	$(OUT)
