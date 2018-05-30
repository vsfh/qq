
#include "beauty.h"
#include "common.h"
#include "function_get.h"

void setColor(unsigned short ForeColor = 2 | 8, unsigned short BackGroundColor = 0);

int main() {

	setColor();
	atexit(sync);
	Init();
	mainmenu();
	sync();
	return 0;
}
