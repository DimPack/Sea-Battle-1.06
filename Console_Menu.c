#include "Console_Header.h"

extern int Enter;

void Preview()
{
	printf("<=== Battle Ships ===>\n");
	
	system("pause");
}

void ControlMenu(bool Exit, int ActiveMenuItem)
{
	while (!Exit)
	{
		ShowMenu(ActiveMenuItem);
		SearchTheMenu(ActiveMenuItem);
			
		switch (Enter)
		{	
			case 27: Exit = true;          break;
			case 72: ActiveMenuItem--;   break;
			case 80: ActiveMenuItem++;   break;
			case 13:
			
			if (ActiveMenuItem == 0)
			{
				NewGameControlMenu(Exit,ActiveMenuItem);
			}
			else if (ActiveMenuItem == 1)
			{
				Info();
			}
			else if (ActiveMenuItem == 2)
			{
				Exit = true;
			}
			break;
		}
		if (ActiveMenuItem < 0) ActiveMenuItem = 0;
		if (ActiveMenuItem > MenuCursorSwitches - 1) ActiveMenuItem = MenuCursorSwitches;
	}
	system("cls");
}

void ShowMenu(int ActiveMenuItem)
{
	system("cls");
	if (ActiveMenuItem == 0)
	{
		printf("  ");
	}
	printf(" New game\n");
	
	if (ActiveMenuItem == 1)
	{
		printf("  ");
	}		
	printf(" Info\n");
	
	if (ActiveMenuItem == 2)
	{
		printf("  ");
	}
	printf(" Exit");
	
	printf ("\n\n\n");

	printf ("^ - down, v - up");
}

void SearchTheMenu(int ActiveMenuItem)
{
	Gotoxy(0, ActiveMenuItem);
	Enter = _getch();
	if (Enter == 224)
	Enter = _getch();	
}

void Gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Info()
{
	char info[]=
	{
		"Sea Battle - game for two participants, in which\n" 
		"players take turns naming the coordinates on an unknown\n"
		"map of the opponent. If the opponent has a ship in that\n"
		"place (the coordinates are occupied), then the ship or \n"
		"part of it sinks, and the one who hit, gets the right\n"
		"to make another move.\n"
	};
	system("cls");
	
	printf("Battle Ships ver 1.06\n");
	puts(info);
	printf("Prostopchuk Dima\n");

	system("pause");
}

void ChoiceBoatPlanning(int ActiveMenuItem)
{
	system("cls");
	if (ActiveMenuItem == 0)
	{
		printf("  ");
	}
	printf (" Auto\n");
	
	if (ActiveMenuItem == 1)
	{
		printf("  ");
	}
	printf (" Manual\n");
	
	if (ActiveMenuItem == 2)
	{
		printf("  ");
	}
	printf (" Back\n\n\n");	
	printf ("^ - down, v - up");
}

void NewGameControlMenu(bool Exit,int ActiveMenuItem)
{
	int MapHum[SizeField][SizeField]  = {}; 
	int MapBot[SizeField][SizeField]  = {};
	
	int MaskHum[SizeField][SizeField] = {};
	int FogBot[SizeField][SizeField] = {};

	int ShipsHum[LifeShips]   = {0 ,4 ,3 ,3 ,2 ,2 ,2 ,1 ,1 ,1 ,1};
	int ShipsBot[LifeShips]   = {0 ,4 ,3 ,3 ,2 ,2 ,2 ,1 ,1 ,1 ,1};

	while (!Exit)
	{
		ChoiceBoatPlanning(ActiveMenuItem);
		SearchTheMenu(ActiveMenuItem);
			
			switch (Enter)
		{
			case 27: Exit = true;          break;
			case 72: ActiveMenuItem--;   break;
			case 80: ActiveMenuItem++;   break;
			case 13:
				
			if (ActiveMenuItem == 0)
			{
				system("cls");
				memset(MapHum,0,sizeof(MapHum));
				
				AutoHum(MapHum, MaskHum, ShipsHum);
				AutoBot(MapBot, FogBot, ShipsBot);
				FightWithBot(MapHum, MapBot, MaskHum, FogBot, ShipsHum, ShipsBot);
			}
			else if (ActiveMenuItem == 1)
			{
				system("cls");
				memset(MapHum,0,sizeof(MapHum));
				
				Manual(MapHum, MaskHum, ShipsHum, Exit);
				AutoBot(MapBot, FogBot, ShipsBot);
				FightWithBot(MapHum, MapBot, MaskHum, FogBot, ShipsHum, ShipsBot);
			}
			else if (ActiveMenuItem == 2)
			{
				Exit = true;	
			}
			break;
		}
		
		if (ActiveMenuItem < 0) ActiveMenuItem = 0;
		if (ActiveMenuItem > MenuCursorSwitches - 1) ActiveMenuItem = MenuCursorSwitches;
	}
}
