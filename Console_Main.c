#include "Console_Header.h"

int main()
{

	int ActiveMenuItem = 0;
	bool Exit = false;
	
	srand(time(NULL));
	Preview();
	ControlMenu(Exit, ActiveMenuItem); 
	
	return 0;
}



