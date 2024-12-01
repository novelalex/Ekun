//
// Created by matt on 10/11/2024.
//

#include "InputHandler.h"

bool InputHandler::handle_click_zone(int x, int y, int w, int h, int mx, int my)
{
	if ((mx > x && mx < x + w) && (my > y && my < y + h)) {
		return true;
	}
	return false;
}


