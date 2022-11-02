#include "globalDefine.h"

double mouse_x, mouse_y;
int mouse_button, mouse_Event;

int DrawFlag = Mouseflag;
int FinishFlag = 0;
int pointnumber = 0;
int PageFlag = Startpageflag;

int solidflag = 0;
int thickflag = 0;
char* colortype = "Red";
int closeflag = 0;
int hideflag = 1; 

struct ListNodePoint *pointhead;
struct ListNodeLine *linehead;
struct ListNodeCircle *circlehead;
struct ListNodePoly *polyhead;

bool pointchosen(double x, double y, double px, double py)
{
	return (x >= px - pointsize && x <= px + pointsize && y >= py - pointsize && y <= py + pointsize);
}

void CreatePoint()
{
	if(DrawFlag == Pointflag){
		static struct ListNodePoint *p;
		static struct ListNodePoint *q;
		static int uselessflag = 0;
		if(uselessflag == 0){
			q = pointhead;
			uselessflag = 1;
		}
		p = pointfound(mouse_x, mouse_y);
		if(p == NULL){
			q->chosenflag = 0;
			q = pointhead;
			drawthepoint(mouse_x, mouse_y, pointsize, 0);
		}else{
			q = p;
			q->chosenflag = 1;
			drawthepoint(p->x, p->y, pointsize * 2, 0);
		}
		if(mouse_Event == BUTTON_DOWN && mouse_button == LEFT_BUTTON){
			if(InCanvas(mouse_x, mouse_y)){
				if(p == NULL){
					CreatePointNode(mouse_x, mouse_y);
				}
			}
		}
	}
}

void drawPoint()
{
	struct ListNodePoint *p;
	p = pointhead;
	while(p != NULL){
		if(p == pointhead){
			p = p->next;
		}else{
			if(p->hidenflag == 0){
				drawthepoint(p->x, p->y, pointsize, p->chosenflag);
			}
			p = p->next;
		}
	}
}

void drawthepoint(double x, double y, double size, int chosenflag)
{
	if(solidflag == 1){
		if(chosenflag == 1){
			SetPenColor(colortype);
		}else{
			SetPenColor("Black");
		}
		StartFilledRegion(1);
		MovePen(x + size, y);
		DrawArc(size, 0, 360);
		EndFilledRegion();
	}else{
		if(chosenflag == 1){
			SetPenColor(colortype);
		}else{
			SetPenColor("Black");
		}
		MovePen(x + size, y);
		DrawArc(size, 0, 360);
	}
	SetPenColor("Black");
}

void choosePoint()
{
	if(DrawFlag == Mouseflag){
		static struct ListNodePoint *p;
		static struct ListNodePoint *q;
		static int uselessflag = 0;
		static int meaninglessflag = 0;
		if(uselessflag == 0){
			q = pointhead;
			uselessflag = 1;
		}
		static int choosingflag = 0;
		p = pointfound(mouse_x, mouse_y);
		if(p == NULL){
			q->chosenflag = choosingflag;
			q = pointhead;
			meaninglessflag = 0;
		}else{
			if(meaninglessflag == 0){
				choosingflag = p->chosenflag;
				meaninglessflag = 1;
			}
			q = p;
			q->chosenflag = 1;
			drawthepoint(p->x, p->y, pointsize * 2, 0);
		}
		if(mouse_Event == BUTTON_DOWN && mouse_button == LEFT_BUTTON){
			if(p != NULL){
				p->chosenflag = 1 - choosingflag;
				choosingflag = p->chosenflag;
			}
		}
	}
}

void ConstructMiddlePoint()
{
	struct ListNodePoint *p = pointhead;
	struct ListNodePoint *point[2];
	int i = 0;
	while(p != NULL){
		if(p == pointhead){
			p = p->next;
		}else{
			if(p->chosenflag == 1){
				i++;
			}
			p = p->next;
		}
	}
	if(i == 2){
		p = pointhead;
		i = 0;
		while(p != NULL){
			if(p == pointhead){
				p = p->next;
			}else{
				if(p->chosenflag == 1){
					point[i] = p;
					i++;
				}
				p = p->next;
			}
		}
		CreatePointNode((point[0]->x + point[1]->x) / 2, (point[0]->y + point[1]->y) / 2);
		ChooseNonePoint();
	}else{
		ChooseNonePoint();
	}
}

void CreateSegment()
{
	if(DrawFlag == Segmentflag){
		static int createsegmentpoint = 0;
		static struct ListNodePoint *pStart, *pEnd, *p;
		static struct ListNodePoint *q;
		static int uselessflag = 0;
		if(uselessflag == 0){
			q = pointhead;
			uselessflag = 1;
		}
		p = pointfound(mouse_x, mouse_y);
		if(createsegmentpoint == 0){
/*find or draw the first point*/
			if(p == NULL){
				q->chosenflag = 0;
				q = pointhead;
				drawthepoint(mouse_x, mouse_y, pointsize, 0);
			}else{
				q = p;
				q->chosenflag = 1;
				drawthepoint(p->x, p->y, pointsize * 2, 0);
			}
			if(mouse_Event == BUTTON_DOWN && mouse_button == LEFT_BUTTON){
				if(InCanvas(mouse_x, mouse_y)){
					if(p == NULL){
						pStart = CreatePointNode(mouse_x, mouse_y);
					}else{
						pStart = p;
					}
					createsegmentpoint = 1;
					FinishFlag = 1;
				}
			}
		}else{
/*find or draw the second point*/
			if(p == NULL){
				q->chosenflag = 0;
				q = pointhead;
				drawthepoint(mouse_x, mouse_y, pointsize, 0);
				MovePen(pStart->x, pStart->y);
				DrawLine(mouse_x - pStart->x, mouse_y - pStart->y);
			}else{
				q = p;
				q->chosenflag = 1;
				drawthepoint(p->x, p->y, pointsize * 2, 0);
				MovePen(pStart->x, pStart->y);
				DrawLine(p->x - pStart->x, p->y - pStart->y);
			}
			if(mouse_Event == BUTTON_DOWN && mouse_button == LEFT_BUTTON){
				if(InCanvas(mouse_x, mouse_y)){
					if(p == NULL){
						pEnd = CreatePointNode(mouse_x, mouse_y);
						createsegmentpoint = 0;
						FinishFlag = 0;
						CreateLineNode(pStart, pEnd, Segmentflag);
					}else if(p != pStart){
						pEnd = p;
						createsegmentpoint = 0;
						FinishFlag = 0;
						CreateLineNode(pStart, pEnd, Segmentflag);
					}
					
				}
			}
		}
	}	
}

void ConstructSegment()
{
	struct ListNodePoint *p = pointhead;
	struct ListNodePoint *point[2];
	int i = 0;
	while(p != NULL){
		if(p == pointhead){
			p = p->next;
		}else{
			if(p->chosenflag == 1){
				i++;
			}
			p = p->next;
		}
	}
	if(i == 2){
		p = pointhead;
		i = 0;
		while(p != NULL){
			if(p == pointhead){
				p = p->next;
			}else{
				if(p->chosenflag == 1){
					point[i] = p;
					i++;
				}
				p = p->next;
			}
		}
		struct ListNodeLine *l;
		l = CreateLineNode(point[0], point[1], Segmentflag);
//		l->chosenflag = 1;
		ChooseNonePoint();
	}else{
		ChooseNonePoint();
	}
}

void ConstructLine()
{
	struct ListNodePoint *p = pointhead;
	struct ListNodePoint *point[2];
	int i = 0;
	while(p != NULL){
		if(p == pointhead){
			p = p->next;
		}else{
			if(p->chosenflag == 1){
				i++;
			}
			p = p->next;
		}
	}
	if(i == 2){
		p = pointhead;
		i = 0;
		while(p != NULL){
			if(p == pointhead){
				p = p->next;
			}else{
				if(p->chosenflag == 1){
					point[i] = p;
					i++;
				}
				p = p->next;
			}
		}
		struct ListNodeLine *l;
		l = CreateLineNode(point[0], point[1], Lineflag);
//		l->chosenflag = 1;
		ChooseNonePoint();
	}else{
		ChooseNonePoint();
	}
}

void drawLine()
{
	struct ListNodeLine *p;
	p = linehead;
	SetPenColor("Black");
	if(thickflag == 1){
		SetPenSize(3);
	} 
	while(p != NULL){
		if(p == linehead){
			p = p->next;
		}else{
//			if(p->chosenflag == 1){
//				SetPenColor("Red");
//			}
			if(p->linetype == Segmentflag){
				MovePen(p->p1->x, p->p1->y);
				DrawLine(p->p2->x - p->p1->x, p->p2->y - p->p1->y);
			}else if(p->linetype == Lineflag){
				MovePen(p->p1->x - (p->p2->x - p->p1->x) * length, p->p1->y - (p->p2->y - p->p1->y) * length);
				DrawLine((p->p2->x - p->p1->x) * length * 2, (p->p2->y - p->p1->y) * length * 2);
			}else if(p->linetype == Rayflag){
				MovePen(p->p1->x, p->p1->y);
				DrawLine((p->p2->x - p->p1->x) * length, (p->p2->y - p->p1->y) * length);
			}
			SetPenColor("Black");
			p = p->next;
		}
	}
	SetPenSize(1);
}

//void chooseLine()
//{
//	if(DrawFlag == 0){
//		
//	}
//} 

void CreateCircle()
{
	if(DrawFlag == Circleflag){
		static int createcirclepoint = 0;
		static struct ListNodePoint *pStart, *p;
		double r;
		static struct ListNodePoint *q;
		static int uselessflag = 0;
		if(uselessflag == 0){
			q = pointhead;
			uselessflag = 1;
		}
		p = pointfound(mouse_x, mouse_y);
		if(createcirclepoint == 0){
/*find or draw the center of the circle*/ 
			if(p == NULL){
				q->chosenflag = 0;
				q = pointhead;
				drawthepoint(mouse_x, mouse_y, pointsize, 0);
			}else{
				q = p;
				q->chosenflag = 1;
				drawthepoint(p->x, p->y, pointsize * 2, 0);
			}
			if(mouse_Event == BUTTON_DOWN && mouse_button == LEFT_BUTTON){
				if(InCanvas(mouse_x, mouse_y)){	
					if(p == NULL){
						pStart = CreatePointNode(mouse_x, mouse_y);
					}else{
						pStart = p;
					}
					createcirclepoint = 1;
					FinishFlag = 1;
				}
			}
		}else{
			if(p == NULL){
				q->chosenflag = 0;
				q = pointhead;
				drawthepoint(mouse_x, mouse_y, pointsize, 0);
				r = sqrt((mouse_x - pStart->x) * (mouse_x - pStart->x) + (mouse_y - pStart->y) * (mouse_y - pStart->y));
				MovePen(pStart->x + r, pStart->y);
				DrawArc(r, 0, 360);
			}else{
				q = p;
				q->chosenflag = 1;
				drawthepoint(p->x, p->y, pointsize * 2, 0);
				r = sqrt((p->x - pStart->x) * (p->x - pStart->x) + (p->y - pStart->y) * (p->y - pStart->y));
				MovePen(pStart->x + r, pStart->y);
				DrawArc(r, 0, 360);
			}
			if(mouse_Event == BUTTON_DOWN && mouse_button == LEFT_BUTTON){
				if(InCanvas(mouse_x, mouse_y)){	
					if(p == NULL){
						r = sqrt((mouse_x - pStart->x) * (mouse_x - pStart->x) + (mouse_y - pStart->y) * (mouse_y - pStart->y));
						struct ListNodePoint *l;
						l = CreatePointNode(mouse_x, mouse_y);
						createcirclepoint = 0;
						FinishFlag = 0;
						CreateCircleNode(pStart, r);
					}else if(p != pStart){
						r = sqrt((p->x - pStart->x) * (p->x - pStart->x) + (p->y - pStart->y) * (p->y - pStart->y));
						createcirclepoint = 0;
						FinishFlag = 0;
						CreateCircleNode(pStart, r);
					}
				}
			}
		}
	}
}

void drawCircle()
{
	struct ListNodeCircle *p;
	p = circlehead;
	while(p != NULL){
		if(p == circlehead){
			p = p->next;
		}else{
			MovePen(p->p->x + p->r, p->p->y);
			DrawArc(p->r, 0, 360);
			p = p->next;
		}
	}
}

void CreatePoly()
{
	if(DrawFlag == Polyflag){
		static int createpolypoint = 0;
		static struct ListNodePoint *pStart, *p, *pPast, *pNow;
		static struct ListNodePoint *q;
		static int uselessflag = 0;
		if(uselessflag == 0){
			q = pointhead;
			uselessflag = 1;
		}
		p = pointfound(mouse_x, mouse_y);
		if(createpolypoint == 0){
/*find or draw the starting point*/
			if(p == NULL){
				q->chosenflag = 0;
				q = pointhead;
				drawthepoint(mouse_x, mouse_y, pointsize, 0);
			}else{
				q = p;
				q->chosenflag = 1;
				drawthepoint(p->x, p->y, pointsize * 2, 0);
			}
			if(mouse_Event == BUTTON_DOWN && mouse_button == LEFT_BUTTON){
				if(InCanvas(mouse_x, mouse_y)){
					if(p == NULL){
						pStart = CreatePointNode(mouse_x, mouse_y);
					}else{
						pStart = p;
					}
					CreatePolyNode(pStart);
					pPast = pStart;
					createpolypoint = 1;
					FinishFlag = 1;
					pStart->chosenflag = 1;
				}
			}
		}else{
/*find or draw the poly point*/
			if(p == NULL){
				q->chosenflag = 0;
				q = pointhead;
				drawthepoint(mouse_x, mouse_y, pointsize, 0);
				MovePen(pPast->x, pPast->y);
				DrawLine(mouse_x - pPast->x, mouse_y - pPast->y);
				if(closeflag == 1){
					MovePen(pStart->x, pStart->y);
					DrawLine(mouse_x - pStart->x, mouse_y - pStart->y);
				}
			}else{
				q = p;
				q->chosenflag = 1;
				if(p == pStart){
					drawthepoint(p->x, p->y, pointsize * 2.5, 0);
				}else{
					drawthepoint(p->x, p->y, pointsize * 2, 0);
					if(closeflag == 1){
						MovePen(pStart->x, pStart->y);
						DrawLine(p->x - pStart->x, p->y - pStart->y);
					}
				}
				MovePen(pPast->x, pPast->y);
				DrawLine(p->x - pPast->x, p->y - pPast->y);
			}
			pStart->chosenflag = 1;
			if(mouse_Event == BUTTON_DOWN && mouse_button == LEFT_BUTTON){
				if(InCanvas(mouse_x,mouse_y)){
					if(p == NULL){
						pNow = CreatePointNode(mouse_x, mouse_y);
						CreateLineNode(pPast, pNow, Segmentflag);
						CreatePolyNode(pNow);
						pPast = pNow;
						createpolypoint = 1;
						FinishFlag = 1;
					}else if(p == pStart){
						CreateLineNode(pPast, pStart, Segmentflag);
						DeletePolyNode();
						createpolypoint = 0;
						FinishFlag = 0;
					}else if(polychosen(p) == FALSE){
						pNow = p;
						CreateLineNode(pPast, pNow, Segmentflag);
						CreatePolyNode(pNow);
						pPast = pNow;
						createpolypoint = 1;
						FinishFlag = 1;
					}else{
						CreateLineNode(pPast, pStart, Segmentflag);
						DeletePolyNode();
						createpolypoint = 0;
						FinishFlag = 0;
					} 
				}
			}
		}
	}
}

bool polychosen(struct ListNodePoint *p)
{
	struct ListNodePoly *q;
	q = polyhead;
    int flag = 1;
    while(q != NULL){
        if(q == polyhead){
            q = q->next;
        }else{
            if(q->p == p){
                flag = 1;
                break;
            }
            q = q->next;
        }
    }
    if(q == NULL){
        flag = 0;
    }
    return flag;
}

void DeletePolyNode()
{
	struct ListNodePoly *p, *q;
    p = polyhead;
    q = polyhead;
    while(p != NULL){
        if(p == polyhead){
            p = p->next;
            q = q->next;
        }else{
            if(p != NULL){
                q = p->next;
                free(p);
                p = q;
            }
        }
    }
    polyhead->next = NULL;
}

void ChooseAllPoint()
{
	struct ListNodePoint *p = pointhead;
	while(p != NULL){
		if(p == pointhead){
			p = p->next;
		}else{
			p->chosenflag = 1;
			p = p->next;
		}
	}
}

void ChooseNonePoint()
{
	struct ListNodePoint *p = pointhead;
	while(p != NULL){
		if(p == pointhead){
			p = p->next;
		}else{
			p->chosenflag = 0;
			p = p->next;
		}
	}
}

void HidePoint()
{
	struct ListNodePoint *p;
	p = pointhead;
	while(p != NULL){
		if(p == pointhead){
			p = p->next;
		}else{
			if(p->chosenflag == 1){
				p->hidenflag = 1;
				p->chosenflag = 0;
			}
			p = p->next;
		}
	}
}

void AppearAllPoint()
{
	struct ListNodePoint *p;
	p = pointhead;
	while(p != NULL){
		if(p == pointhead){
			p = p->next;
		}else{
			p->hidenflag = 0;
			p = p->next;
		}
	}
}

struct ListNodePoint* CreatePointNode(double x, double y)
{
	struct ListNodePoint *p, *q, *s;
	p = (struct ListNodePoint*)malloc(sizeof(struct ListNodePoint));
	q = pointhead;
	s = pointhead;
	while(q != NULL){
		q = q->next;
		if(q != NULL){
			s = s->next;
		}
	}
	s->next = p;
	pointnumber++;
	p->x = x;
	p->y = y;
	p->number = pointnumber;
	p->chosenflag = 0;
	p->hidenflag = 0;
	p->next = NULL;
	return (p);
}

struct ListNodeLine* CreateLineNode(struct ListNodePoint *pStart, struct ListNodePoint *pEnd, int linetype)
{
	struct ListNodeLine *p, *q, *s;
	p = (struct ListNodeLine*)malloc(sizeof(struct ListNodeLine));
	q = linehead;
	s = linehead;
	while(q != NULL){
		q = q->next;
		if(q != NULL){
			s = s->next;
		}
	}
	s->next = p;
	p->p1 = pStart;
	p->p2 = pEnd;
	p->linetype = linetype;
	p->next = NULL;
	return (p);
}

struct ListNodeCircle* CreateCircleNode(struct ListNodePoint *center, double radius)
{
	struct ListNodeCircle *p, *q, *s;
	p = (struct ListNodeCircle*)malloc(sizeof(struct ListNodeCircle));
	q = circlehead;
	s = circlehead;
	while(q != NULL){
		q = q->next;
		if(q != NULL){
			s = s->next;
		}
	}
	s->next = p;
	p->p = center;
	p->r = radius;
	p->next = NULL;
	return (p);
}

struct ListNodePoly* CreatePolyNode(struct ListNodePoint *p)
{
	struct ListNodePoly *t, *q, *s;
	t = (struct ListNodePoly*)malloc(sizeof(struct ListNodePoly));
	q = polyhead;
	s = polyhead;
	while(q != NULL){
		q = q->next;
		if(q != NULL){
			s = s->next;
		}
	}
	s->next = t;
	t->p = p;
	t->next = NULL;
	return (t);
}

struct ListNodePoint* pointfound(double x, double y)
{
	struct ListNodePoint *p;
	p = pointhead;
	while(p != NULL){
		if(p == pointhead){
			p = p->next;
		}else{
			if(pointchosen(x, y, p->x, p->y) == TRUE && p->hidenflag == 0){
				break;
			}else{
				p = p->next;
			}
		}			
	}
	if(p != NULL){
		return p;
	}else{
		return NULL;
	}
}

void DrawPage()
{
	if(PageFlag == Homepageflag){
		DrawHomePage();
	}else if(PageFlag == Drawingpageflag){
		DrawDrawingPage();
	}else if(PageFlag == Startpageflag){
		DrawStartPage();
	}
}

void DrawHomePage()
{
	static char* solidflagstring = "点型    空心 >";
	static char* thickflagstring = "线型    细线 >";
	static char* hideflagstring = "网格    隐藏 >";
	drawMenuBar(0, WindowHeight - menulistheight, menulistwidth * 3, menulistheight);
	char *menuListDraw[] = {"绘图    >", "鼠标", "点", "线    >", "    线段", "    直线", "    射线", "圆", "圆弧", "矩形", "多边形    >", "    开放", "    闭合"};
	char *menuListEdit[] = {"编辑    >", "全选 | Ctrl-A", "全不选", "隐藏 | Ctrl-H", "全显示", solidflagstring, thickflagstring, hideflagstring, "颜色    >", "    红色", "    橙色", "    蓝色"};
	char *menuListConstruct[] = {"构造    >", "中点 | Ctrl-M", "线段 | Ctrl-L", "直线", "矩形"};
	char *menuListFile[] = {"文件    >", "使用手册", "保存 | Ctrl-S", "退出 | Ctrl-Q"};
	int selectionDraw = menuList(GenUIID(0), menulistwidth * 0, WindowHeight - menulistheight, menulistwidth, menulistwidth, menulistheight, menuListDraw, sizeof(menuListDraw) / sizeof(menuListDraw[0]));
	int selectionEdit = menuList(GenUIID(1), menulistwidth * 1, WindowHeight - menulistheight, menulistwidth, menulistwidth, menulistheight, menuListEdit, sizeof(menuListEdit) / sizeof(menuListEdit[0]));
	int selectionConstruct = menuList(GenUIID(2), menulistwidth * 2, WindowHeight - menulistheight, menulistwidth, menulistwidth, menulistheight, menuListConstruct, sizeof(menuListConstruct) / sizeof(menuListConstruct[0]));
	int selectionFile = menuList(GenUIID(3), menulistwidth * 3, WindowHeight - menulistheight, menulistwidth, menulistwidth, menulistheight, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	switch(selectionDraw){
		case Mouseflag:
			ChooseNonePoint();
			DrawFlag = Mouseflag;
			Display();
			break;
		case Pointflag:
			ChooseNonePoint();
			DrawFlag = Pointflag;
			PageFlag = Drawingpageflag;
			Display();
			break;
		case Segmentflag:
			ChooseNonePoint();
			DrawFlag = Segmentflag;
			PageFlag = Drawingpageflag;
			Display();
			break;
		case Rayflag:
			ChooseNonePoint();
			DrawFlag = Rayflag;
			PageFlag = Drawingpageflag;
			Display();
			break;
		case Lineflag:
			ChooseNonePoint();
			DrawFlag = Lineflag;
			PageFlag = Drawingpageflag;
			Display();
			break;
		case Circleflag:
			ChooseNonePoint();
			DrawFlag = Circleflag;
			PageFlag = Drawingpageflag;
			Display();
			break;
		case Sectorflag:
			ChooseNonePoint();
			DrawFlag = Sectorflag;
			PageFlag = Drawingpageflag;
			Display();
			break;
		case Recflag:
			ChooseNonePoint();
			DrawFlag = Recflag;
			PageFlag = Drawingpageflag;
			Display();
			break;
		case OpenPolyflag:
			ChooseNonePoint();
			DrawFlag = Polyflag;
			PageFlag = Drawingpageflag;
			closeflag = 0;
			Display();
			break;
		case ClosePolyflag:
			ChooseNonePoint();
			DrawFlag = Polyflag;
			PageFlag = Drawingpageflag;
			closeflag = 1;
			Display();
			break;
		default:
			break;	
	}
	switch(selectionEdit){
		case 1:
			ChooseAllPoint();
			Display();
			break;
		case 2:
			ChooseNonePoint();
			Display();
			break;
		case 3:
			HidePoint();
			Display();
			break;
		case 4:
			AppearAllPoint();
			Display();
			break;
		case PointSolidorHollow:
			if(solidflag == 0){
				solidflagstring = "点型    实心 >";
				solidflag = 1;
				Display();
				break;
			}else if(solidflag == 1){
				solidflagstring = "点型    空心 >";
				solidflag = 0;
				Display();
				break;
			}
		case LineThickorThin:
			if(thickflag == 0){
				thickflagstring = "线型    粗线 >";
				thickflag = 1;
				Display();
				break;
			}else if(thickflag == 1){
				thickflagstring = "线型    细线 >";
				thickflag = 0;
				Display();
				break;
			}
		case GridHideorAppear:
			if(hideflag == 0){
				hideflagstring = "网格    隐藏 >";
				hideflag = 1;
				Display();
				break;
			}else if(hideflag == 1){
				hideflagstring = "网格    显示 >";
				hideflag = 0;
				Display();
				break;
			}
		case Redflag:
			colortype = "Red";
			Display();
			break;
		case Orangeflag:
			colortype = "Orange";
			Display();
			break;
		case Blueflag:
			colortype = "Blue";
			Display();
			break;
		default:
			break;
	}
	switch(selectionConstruct){
		case 1:
			ConstructMiddlePoint();
			Display();
			break;
		case 2:
			ConstructSegment();
			Display();
			break;
		case 3:
			ConstructLine();
			Display();
			break;
		case 4:
			ConstructRec();
			Display();
			break;
		default:
			break;
	}
	switch(selectionFile){
		case 1:
			system("..\\Readme.pdf");
			break;
		case 3:
			exit(-1);
			break;
		default:
			break;
	}
}

void DrawDrawingPage()
{
	SetPenColor("Light Gray");
	MovePen(canvasRect[0], canvasRect[1]);
	DrawLine(canvasRect[2] - canvasRect[0], 0);
	MovePen(canvasRect[0], canvasRect[3]);
	DrawLine(canvasRect[2] - canvasRect[0], 0);
}

void DrawStartPage()
{
	SetPenSize(3);
	SetPenColor("Black");
	SetPointSize(64);
	SetFont("Calibri");
	drawLabel(WindowWidth / 2 - TextStringWidth("Free Geometry Tool") / 2, 7, "Free Geometry Tool");
	SetPointSize(25);
	SetFont("宋体");
	if (PageFlag == Startpageflag && button(GenUIID(0), WindowWidth / 2 - buttonwidth / 2, WindowHeight / 2 - buttonheight / 2 + 1 * buttonheight * 1.5, buttonwidth, buttonheight, "新建")){
		PageFlag = Homepageflag;
		SetPointSize(15);
		Display();
	}
	if (PageFlag == Startpageflag && button(GenUIID(0), WindowWidth / 2 - buttonwidth / 2, WindowHeight / 2 - buttonheight / 2 + 0 * buttonheight * 1.5, buttonwidth, buttonheight, "打开")){
//		readFromFile();
	}
	if (PageFlag == Startpageflag && button(GenUIID(0), WindowWidth / 2 - buttonwidth / 2, WindowHeight / 2 - buttonheight / 2 - 1 * buttonheight * 1.5, buttonwidth, buttonheight, "退出")){
		exit(-1);
	}
}

void drawgrid()
{
	if(hideflag == 0 && PageFlag != Startpageflag){
		SetPenColor("Light Gray");
		MovePen(canvasRect[0], canvasRect[1]);
		DrawLine(canvasRect[2] - canvasRect[0], 0);
		MovePen(canvasRect[0], canvasRect[3]);
		DrawLine(canvasRect[2] - canvasRect[0], 0);
		double i;
		for(i = canvasRect[1]; i < canvasRect[3]; ){
			MovePen(canvasRect[0], i);
			DrawLine(WindowWidth, 0);
			i += 0.6;
		} 
		for(i = canvasRect[0]; i < canvasRect[2]; ){
			MovePen(i, canvasRect[1]);
			DrawLine(0, canvasRect[3] - canvasRect[1]);
			i += 0.6;
		}
		SetPenColor("Black");
	}
}
