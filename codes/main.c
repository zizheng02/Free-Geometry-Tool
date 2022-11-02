#include "globalDefine.h"
double WindowWidth = 12;
double WindowHeight = 9;
double canvasRect[4]={0, 1, 12, 9 - menulistheight};
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event);
	mouse_x = ScaleXInches(x);
	mouse_y= ScaleYInches(y);
	mouse_button = button;
	mouse_Event = event;
	Display();
}

void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event);
	Display();
}

void CharEventProcess(char ch)
{
	uiGetChar(ch);
	Display();
}

void PlayBGM()
{
	char bgm[30];
	const string bgmName[4]={"music1.wav","music2.wav","music3.wav","music4.wav"};
	char url[100]="../bgm/"; 
	strcpy(bgm,bgmName[rand()%4]);
	strcat(url,bgm);
	PlaySound(url,NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
}

void Main()
{
	SetWindowTitle("Free Geometry Tool"); 
	SetWindowSize(WindowWidth, WindowHeight); 
	InitGraphics(); 
//	InitConsole();
	registerMouseEvent(MouseEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	registerCharEvent(CharEventProcess);
	
	pointhead = (struct ListNodePoint*)malloc(sizeof(struct ListNodePoint));
	pointhead->next = NULL;
	linehead = (struct ListNodeLine*)malloc(sizeof(struct ListNodeLine));
	linehead->next = NULL;
	circlehead = (struct ListNodeCircle*)malloc(sizeof(struct ListNodeCircle));
	circlehead->next = NULL;
	sectorhead = (struct ListNodeSector*)malloc(sizeof(struct ListNodeSector));
	sectorhead->next = NULL;
	rechead = (struct ListNodeRec*)malloc(sizeof(struct ListNodeRec));
	rechead->next = NULL;
	polyhead = (struct ListNodePoly*)malloc(sizeof(struct ListNodePoly));
	polyhead->next = NULL;
	
	SetPenColor("White");
	DefineColor("Cold Color", .32, .4, .5);
	DefineColor("Hot Color", .97, .62, .21);
	setMenuColors("Cold Color", "White", "Hot Color", "White", 1);
	setButtonColors("Cold Color", "White", "Hot Color", "White", 1);
	
	PlayBGM();
	
	Display();
}


void Display()
{
	DisplayClear();
	
	drawgrid();
	
	CreatePoint();
	choosePoint();
	CreateSegment();
	CreateLine();
	CreateRay();
	drawLine();
	CreateCircle();
	drawCircle();
	CreateSector();
	drawSector();
	CreateRec();
	drawRec();
	CreatePoly();
	drawPoint();
	
	DrawPage();
	drawpagebutton();
}
