#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <SDL.h>
#include "Font.h"

class TextBox {
public:
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect rect;
	int initial_width;

	TextBox();
	TextBox(int x, int y, int w, int h);
	~TextBox();

	void Draw(SDL_Renderer* renderer, int x, int y);
	void Draw(SDL_Renderer* renderer);
	void Update(const char* text, Font* font, SDL_Renderer* renderer);
	void Free();
};

#endif // TEXT_BOX_H

