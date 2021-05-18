#include "Console_Header.h"

int ShipsID;
int Enter;


void SetRandShip(int MapHum[SizeField][SizeField], int SizeShip, int NumShip,int *ShipsHum) // рандом корабля
{
	int RandomPositionX = 0, RandomPositionY = 0;
	int i;
	int DirRand = 0;
	int CountShip = 0;
	int Tact = 0;

	while (CountShip < NumShip) 
	{
		Tact++;
		if(Tact > 150)break;
		
		RandomPositionX = rand() % SizeField;
		RandomPositionY = rand() % SizeField;	
	
		int TempX = RandomPositionX;
		int TempY = RandomPositionY;
		bool SettingIsPossible = 1; 
		
		DirRand = rand() % 4; 
		
		for (i = 0; i < SizeShip; i++)
		{
			if (RandomPositionX < 0 || RandomPositionY < 0 || RandomPositionX >= SizeField || RandomPositionY >= SizeField) 
			{
				SettingIsPossible = 0;
				break;
			}
			
			if ( MapHum[RandomPositionX][RandomPositionY]        >= 1 ||
			    MapHum[RandomPositionX][RandomPositionY + 1]     >= 1 ||
				MapHum[RandomPositionX][RandomPositionY - 1]     >= 1 ||
				MapHum[RandomPositionX + 1][RandomPositionY]     >= 1 ||
				MapHum[RandomPositionX + 1][RandomPositionY + 1] >= 1 ||
				MapHum[RandomPositionX + 1][RandomPositionY - 1] >= 1 ||
				MapHum[RandomPositionX - 1][RandomPositionY]     >= 1 ||
				MapHum[RandomPositionX - 1][RandomPositionY + 1] >= 1 ||
				MapHum[RandomPositionX - 1][RandomPositionY - 1] >= 1)
			{
				SettingIsPossible = 0;
				break;	
			}
			
			switch (DirRand) 
			{
				case 0: RandomPositionX++; break;
				case 1: RandomPositionY++; break;
				case 2: RandomPositionX--; break;
				case 3: RandomPositionY--; break;
			}	
		}
		if (SettingIsPossible == 1) // Вставка корабля
		{
			RandomPositionX = TempX;
			RandomPositionY = TempY;
				
			for (i = 0; i < SizeShip; i++)
			{
				MapHum[RandomPositionX][RandomPositionY] = ShipsID;
				switch (DirRand)
				{
					case 0: RandomPositionX++; break;
					case 1: RandomPositionY++; break;
					case 2: RandomPositionX--; break;
					case 3: RandomPositionY--; break;
				}		
			}
			ShipsHum[ShipsID] = SizeShip;
			ShipsID++;
			CountShip++;
		}	
	}
}

void ShowMapShip (int MapHum[SizeField][SizeField], int MaskHum[SizeField][SizeField], bool UseMask) // прорисовка поля 
{
	int i,j;
	printf("  ");
	
	for(i=0; i < SizeField; i++)
	{
		printf("%i",i);
	}
	
	printf ("\n");
	printf("  ");
	
	for(i=0; i < SizeField; i++)
	{
		printf("=");
	}
	
	printf ("\n");
	
	for(i=0; i < SizeField; i++)
	{
		printf("%c|",i+65);
		
		for (j = 0; j < SizeField; j++)
		{
			if (MaskHum[j][i] == 1 || UseMask == 0)
			{
				if (MapHum[j][i] == 0)
				{
					printf ("."); 
				}
				else if (MapHum[j][i] == -1)
				{
					printf ("X");
				}
				else if (MapHum[j][i] == -2)
				{
					printf ("*");
				}
				
				else if(MapHum[j][i] > 0 )
				{
					printf("O");
					//printf ("%i", MapHum[j][i]);
				}		
			}
			else 
			{
				printf (".");
			}	
		}
		printf ("\n");
	}	
	printf ("\n");
	
}

void AutoBot (int MapBot[SizeField][SizeField], int FogBot[SizeField][SizeField], int *ShipsBot)
{
	ShipsID = 1;
	SetRandShip(MapBot, 4, 1, ShipsBot);
	SetRandShip(MapBot, 3, 2, ShipsBot);	
	SetRandShip(MapBot, 2, 3, ShipsBot);	
	SetRandShip(MapBot, 1, 4, ShipsBot);
}

void AutoHum (int MapHum[SizeField][SizeField],  int MaskHum[SizeField][SizeField],  int *ShipsHum)
{
	ShipsID = 1;
	SetRandShip(MapHum, 4, 1, ShipsHum);
	SetRandShip(MapHum, 3, 2, ShipsHum);	
	SetRandShip(MapHum, 2, 3, ShipsHum);	
	SetRandShip(MapHum, 1, 4, ShipsHum); 	
}

int Shot(int MapHum[SizeField][SizeField], int ShotX, int ShotY, int *ShipsHum, int MaskHum[SizeField][SizeField])
{
	int ResultShot = 0;
	
	if (MapHum[ShotX][ShotY] == -1 || MapHum[ShotX][ShotY] == -2)
	{
		ResultShot = 3; // для бота 
	}
	else if (MapHum[ShotX][ShotY] >= 1)
	{
		ShipsHum[ MapHum[ShotX][ShotY] ]--;
		if (ShipsHum[ MapHum[ShotX][ShotY] ] <= 0)
		{
			ResultShot = 2;		
		}
		else
		{
			ResultShot = 1;	
		}
		MapHum[ShotX][ShotY] = -1;
	}
	else
	{
		MapHum[ShotX][ShotY] = -2;	
	}
	MaskHum[ShotX][ShotY] = 1;
		
	return ResultShot;
}

void Manual(int MapHum[SizeField][SizeField], int MaskHum[SizeField][SizeField], int *ShipsHum, bool Exit)
{
	
	int SizeShipInManual;
	int DirManual = 0;
	int ManualPositionX = 0, ManualPositionY = 0;
	int CountShips = 1;
	
	ShipsID = 1;
	while (true)
	{
		switch(CountShips)
		{
			case 1: SizeShipInManual = 4; break;
			case 2 ... 3: SizeShipInManual = 3; break;
			case 4 ... 6: SizeShipInManual = 2; break;
			case 7 ... 10: SizeShipInManual = 1;
		}
		
		if(CountShips > 10) break;
		
		ShowMapShip( MapHum, MaskHum, 0 );	
		ShipShow( ManualPositionX, ManualPositionY, DirManual, SizeShipInManual );
		
		Gotoxy (16,0);
		printf ("Manual control menu");
		Gotoxy (20,1);
		printf ("Up    - 'w'");
		Gotoxy (20,2);
		printf ("Down  - 's'");
		Gotoxy (20,3);
		printf ("Left  - 'a'");
		Gotoxy (20,4);
		printf ("Rigth - 'd'");
		Gotoxy (20,5);
		printf ("Turn  - 'r'");
		Gotoxy (20,6);
		printf ("Exit  - 'Ecs'");
		
		int TempX = ManualPositionX;
		int TempY = ManualPositionY;
		int TempDir = DirManual;
		
		Enter = getch();
		switch (Enter)
		{
			case 100: ManualPositionX++; break; // вправо
			case 115: ManualPositionY++; break; // вниз
			case 97:  ManualPositionX--; break; // вліво
			case 119: ManualPositionY--; break; // верх
			case 114: DirManual = !DirManual; break; // r - поворот 
			case 27 : return ;
			case 13: 
			if(CheckPositionShip( MapHum, ManualPositionX, ManualPositionY, DirManual, SizeShipInManual, ShipsHum ))
			{
				ManualPositionX = 0;
				ManualPositionY = 0;
				DirManual = 0;
				CountShips++;
			} 
			break;
		}	
		if (!BorderMap( ManualPositionX, ManualPositionY, SizeShipInManual, DirManual ))
		{
			ManualPositionX = TempX;
			ManualPositionY =  TempY;
			DirManual = TempDir;
		}
		system("cls");
	}
}

void ShipShow(int x,int y,int Direction,int SizeShip)
{
	int i;
	for ( i = 0; i < SizeShip; i++)
	{
		Gotoxy(x+2,y+2);
		printf ("O");
		
		switch (Direction)
		{
			case 0: x++; break;
			case 1: y++; break;
			case 2: x--; break;
			case 3: y--; break;
		}		
	}
}

bool BorderMap(int ManualPositionX, int ManualPositionY,int SizeShip, int Direction) // границі поля
{
	int i;
	bool InMap = 1;
		
	for (i = 0; i < SizeShip; i++)
	{
		if (ManualPositionX < 0 || ManualPositionY < 0 || ManualPositionX >= SizeField || ManualPositionY >= SizeField)
		{
			InMap = 0;
			break;
		}
		switch (Direction)
		{
			case 0: ManualPositionX++; break;
			case 2: ManualPositionX--; break;
			case 1: ManualPositionY++; break;
			case 3: ManualPositionY--; break;
		}		
	}
	return InMap;	
}

bool CheckPositionShip(int MapHum[SizeField][SizeField], int ManualPositionX, int ManualPositionY, int Direction,int SizeShip, int *ShipsHum) // для ввода корабля на поле 
{
	int i;
	int TempX = ManualPositionX;
	int TempY = ManualPositionY;
	bool SettingIsPossible = 1; 
	
	for (i = 0; i < SizeShip; i++)
	{		
		if (MapHum[ManualPositionX][ManualPositionY]  >= 1)
		{
			SettingIsPossible = 0;
			break;	
		}
			
		if (ManualPositionY < SizeField - 1 )
		if (MapHum[ManualPositionX][ManualPositionY + 1]  >= 1)
		{
			SettingIsPossible = 0;
			break;	
		}
			
		if (ManualPositionY > 0)
		if (MapHum[ManualPositionX][ManualPositionY - 1]  >= 1)
		{
			SettingIsPossible = 0;
			break;	
		}
	
		if (ManualPositionX < SizeField-1)
		if (MapHum[ManualPositionX + 1][ManualPositionY]  >= 1)
		{
			SettingIsPossible = 0;
			break;	
		}
			
		if (ManualPositionX < SizeField - 1 && ManualPositionY < SizeField - 1)
		if (MapHum[ManualPositionX + 1][ManualPositionY + 1]  >= 1)
		{
			SettingIsPossible = 0;
			break;	
		}
			
		if (ManualPositionX < SizeField - 1 && ManualPositionY > 0)
		if (MapHum[ManualPositionX + 1][ManualPositionY - 1]  >= 1)
		{
			SettingIsPossible = 0;
			break;	
		}
			
		if (ManualPositionX > 0)
		if (MapHum[ManualPositionX - 1][ManualPositionY]  >= 1)
		{
			SettingIsPossible = 0;
			break;	
		}
			
		if (ManualPositionX > 0 && ManualPositionY < SizeField - 1)
		if (MapHum[ManualPositionX - 1][ManualPositionY + 1]  >= 1)
		{
			SettingIsPossible = 0;
			break;	
		}
			
		if (ManualPositionX > 0 && ManualPositionY > 0)
		if (MapHum[ManualPositionX - 1][ManualPositionY - 1]  >= 1)
		{
			SettingIsPossible = 0;
			break;	
		}
		
		switch (Direction) 
		{
			case 0: ManualPositionX++; break;
			case 1: ManualPositionY++; break;
			case 2: ManualPositionX--; break;
			case 3: ManualPositionY--; break;
		}	
	}			
				
	if (SettingIsPossible == 1) // Вставка корабля
	{
		ManualPositionX = TempX;
		ManualPositionY = TempY;
					
		for ( i = 0; i < SizeShip; i++)
		{
			MapHum[ManualPositionX][ManualPositionY] = ShipsID;
			switch (Direction)
			{
				case 0: ManualPositionX++; break;
				case 1: ManualPositionY++; break;
				case 2: ManualPositionX--; break;
				case 3: ManualPositionY--; break;
			}		
		}
		ShipsHum[ShipsID] = SizeShip;		 
		ShipsID++;
	}			
	return SettingIsPossible;
}


void FightWithBot(int MapHum[SizeField][SizeField], int MapBot[SizeField][SizeField], int MaskHum[SizeField][SizeField],int FogBot[SizeField][SizeField], int *ShipsHum, int *ShipsBot)
{
	bool InTurn = 0;

	int ShotBotX = 0;
	int ShotBotY = 0;
	int ShotX = 0; // human
	int ShotY = 0; // human
	
	bool WinHum = 0;
	bool WinBot = 0;
	
	while (WinHum == false && WinBot == false)
	{
		int ResultShot = 0;
		
		do
		{
			char KeyShot;
			
			ShowMapShip(MapHum, MaskHum, 0);
			ShowMapShip(MapBot, FogBot, 1);
			
			if (InTurn == 1)
			{
				printf ("It's your turn to shoot -> \n");		
				printf ("Enter the letter A to J (coordinate x):");
				
				do{
					KeyShot = getch();
				}while(KeyShot < 'a' || KeyShot > 'j');
				
				printf(" %c\n",KeyShot);
				ShotY = KeyShot -'a';
							
				printf ("Enter a number (coordinate y):");
				do{
					KeyShot = getch();
				}while(KeyShot < '0' || KeyShot > '9');
							
				printf(" %c\n",KeyShot);
				ShotX = KeyShot -'0';
				
				ResultShot = Shot(MapBot, ShotX, ShotY, ShipsBot, FogBot);
				
				if (ResultShot == 1)
				{
					printf ("Good shot!");
				}
				else if (ResultShot == 2)
				{
					int i;
					bool Died = 1;
					
					for (i = 1; i <= LifeShips; i++)
					{
						if (ShipsBot[i] != 0)
						{
							Died = 0;
							break; 
						}
					}
					if (Died == 1)
					{
						WinHum = true;
						break;
					}
				
					printf ("Kill ship!");
				}
				else 
				{
					printf ("Miss!");
				}	
			}
			else 
			{
				printf ("\nThe computer's queue to shoot ->");
				Sleep(1300);
				
				
				do{
					ShotBotX = rand() % SizeField;
					ShotBotY = rand() % SizeField;
					ResultShot = Shot(MapHum, ShotBotX, ShotBotY, ShipsHum, MaskHum);
					
				}while (ResultShot == 3);
			
				if (ResultShot == 1)
				{
					printf ("Good shot!");
				}
				else if (ResultShot == 2)
				{
					
					int i;
					bool DiedBot = 1;
					
					for (i = 1; i <= LifeShips; i++)
					{
						if (ShipsHum[i] != 0)
						{
							DiedBot = 0;
							break; 
						}
					}
					if (DiedBot == 1)
					{
						WinBot = true;
						break;
					}
					
					printf ("Kill ship!");
				}
				else 
				{
					printf ("Miss!");
				}			
			}
			
			Sleep(1100);
			system ("cls");	
		}while (ResultShot != 0);
		
		InTurn =!InTurn;
	}
	system ("cls");
	ShowMapShip(MapHum, MaskHum, 0);
	ShowMapShip(MapBot, FogBot, 1);
	
	if (WinHum == true)
	{

		printf ("HUMAN WIN ! ");
	}
	else if (WinBot == true)
	{
	
		printf ("BOT WIN ! ");
	}
	system ("pause");	
}
