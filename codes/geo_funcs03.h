#ifndef _WZZ_H_
#define _WZZ_H_

bool InCanvas(double x, double y);

extern double WindowWidth;
extern double WindowHeight;
extern double canvasRect[4];

void drawpagebutton();

struct ListNodeRec{
	struct ListNodePoint *p1;
	struct ListNodePoint *p2;
	int chosenflag;
	struct ListNodeRec *next;
};

extern struct ListNodeRec *rechead;

void CreateRec();
void drawRec();
void ConstructRec();
struct ListNodeRec* CreateRecNode(struct ListNodePoint *pStart, struct ListNodePoint *pEnd);

void PlayBGM(); 

#endif
