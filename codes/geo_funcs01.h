#ifndef _SCY_H_
#define _SCY_H_

extern double mouse_x, mouse_y; 
extern int mouse_button, mouse_Event;

extern int DrawFlag;
extern int PageFlag;
extern int FinishFlag;

extern int solidflag;
extern int hideflag;

struct ListNodePoint{
	double x;
	double y;
	int number;
	int chosenflag;
	int hidenflag;
	struct ListNodePoint *next;
};

struct ListNodeLine{
	struct ListNodePoint *p1;
	struct ListNodePoint *p2;
	int chosenflag;
	int linetype;
	struct ListNodeLine *next;
};

struct ListNodeCircle{
	struct ListNodePoint *p;
	double r;
	struct ListNodeCircle *next;
};

struct ListNodePoly{
	struct ListNodePoint *p;
	struct ListNodePoly *next;
};

extern struct ListNodePoint *pointhead;
extern struct ListNodeLine *linehead;
extern struct ListNodeCircle *circlehead;
extern struct ListNodePoly *polyhead;

bool pointchosen(double x, double y, double px, double py); 

void Display(); 
void DrawPage();
void DrawHomePage(); 
void DrawDrawingPage();
//void DrawFreePage();
void drawgrid();

void CreatePoint();
void drawPoint();
void drawthepoint(double x, double y, double size, int chosenflag);
void choosePoint();
void ConstructMiddlePoint();
void CreateSegment();
void ConstructSegment();
void ConstructLine();
void drawLine();
//void chooseLine();
void CreateCircle();
void drawCircle();
void CreatePoly();

void ChooseAllPoint();
void ChooseNonePoint();
void HidePoint();

struct ListNodePoint* CreatePointNode(double x, double y);
struct ListNodeLine* CreateLineNode(struct ListNodePoint *pStart, struct ListNodePoint *pEnd, int linetype);
struct ListNodeCircle* CreateCircleNode(struct ListNodePoint *center, double radius);
struct ListNodePoly* CreatePolyNode(struct ListNodePoint *p);
void DeletePolyNode();

bool polychosen(struct ListNodePoint *p);
struct ListNodePoint* pointfound(double x, double y);

#endif
