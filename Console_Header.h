#ifndef SEA_BATTLE_CONSOLE_MENU_HEADER
#define SEA_BATTLE_CONSOLE_MENU_HEADER

#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define MenuCursorSwitches 2
#define SizeField 10
#define LifeShips 11

void Gotoxy(int x, int y);
void Preview();
// ћеню
void ShowMenu(int ActiveMenuItem);
void ControlMenu(bool Exit, int ActiveMenuItem);
void NewGameControlMenu(bool Exit,int ActiveMenuItem);
void Info();
void SearchTheMenu(int ActiveMenuItem);
void ChoiceBoatPlanning(int ActiveMenuItem);
//Ћог≥ка
void AutoBot (int MapBot[SizeField][SizeField], int FogBot[SizeField][SizeField], int *ShipsBot);
void AutoHum (int MapHum[SizeField][SizeField],  int MaskHum[SizeField][SizeField],  int *ShipsHum);
void SetRandShip(int MapHum[SizeField][SizeField], int SizeShip, int NumShip,int *ShipsHum);
void ShowMapShip (int MapHum[SizeField][SizeField], int MaskHum[SizeField][SizeField], bool UseMask);
void Manual(int MapHum[SizeField][SizeField], int MaskHum[SizeField][SizeField], int *ShipsHum, bool Exit);
void ShipShow(int x, int y, int Dir, int SizeShip);
bool BorderMap(int x, int y, int SizeShip ,int Dir);
bool CheckPositionShip(int MapHump[SizeField][SizeField], int x, int y, int Dir,int SizeShip, int *ShipsHum);
int Shot(int MapHum[SizeField][SizeField], int ShotX, int ShotY, int *ShipsHum, int MaskHum[SizeField][SizeField]);
void FightWithBot(int MapHum[SizeField][SizeField], int MapBot[SizeField][SizeField], int MaskHum[SizeField][SizeField],int FogBot[SizeField][SizeField], int *ShipsHum, int *ShipsBot);

#endif
