#include "globalDefine.h" 

struct ListNodeRec *rechead;

bool InCanvas(double x, double y)
{  
	return(x >= (canvasRect[0] + canvassize) && x <= (canvasRect[2] - canvassize) && y >= (canvasRect[1] + canvassize) && y <= (canvasRect[3] - canvassize));
}

void CreateRec()
{
	if(DrawFlag == Recflag){
		static int createrecpoint = 0;
		static struct ListNodePoint *pStart, *pEnd, *p;
		static struct ListNodePoint *q;
		static int uselessflag = 0;
		if(uselessflag == 0){
			q = pointhead;
			uselessflag = 1;
		}
		p = pointfound(mouse_x, mouse_y);
		if(createrecpoint == 0){
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
					createrecpoint = 1;
					FinishFlag = 1;
				}
			}
		}else{
/*find or draw the second point*/
			if(p == NULL){
				q->chosenflag = 0;
				q = pointhead;
				drawthepoint(mouse_x, mouse_y, pointsize, 0);
			}else{
				q = p;
				q->chosenflag = 1;
				drawthepoint(p->x, p->y, pointsize * 2, 0);
			}
			MovePen(pStart->x, pStart->y);
			if(p == NULL){
				DrawLine(mouse_x - pStart->x, 0);
				DrawLine(0,mouse_y - pStart->y); 
				DrawLine(-(mouse_x - pStart->x), 0);
				DrawLine(0,-(mouse_y - pStart->y)); 
			}else{
				DrawLine(p->x - pStart->x,0);
				DrawLine(0, p->y - pStart->y); 
				DrawLine(-(p->x - pStart->x),0);
				DrawLine(0, -(p->y - pStart->y)); 
			}
			if(mouse_Event == BUTTON_DOWN && mouse_button == LEFT_BUTTON){
				if(InCanvas(mouse_x, mouse_y)){
					if(p == NULL){
						pEnd = CreatePointNode(mouse_x, mouse_y);
						createrecpoint = 0;
						FinishFlag = 0;
						CreateRecNode(pStart, pEnd);
					}else if(p != pStart){
						pEnd = p;
						createrecpoint = 0;
						FinishFlag = 0;
						CreateRecNode(pStart, pEnd);
					}
					
				}
			}
		}
	}
}

void drawRec()
{
	struct ListNodeRec *p;
	p = rechead;
	while(p != NULL){
		if(p == rechead){
			p = p->next;
		}else{
			MovePen((p->p1)->x, (p->p1)->y);
			DrawLine((p->p2)->x - (p->p1)->x, 0);
			DrawLine(0,(p->p2)->y - (p->p1)->y);
			DrawLine(-((p->p2)->x - (p->p1)->x), 0);
			DrawLine(0,-((p->p2)->y - (p->p1)->y));
			p = p->next;
		}
	}
}

void ConstructRec()
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
		CreateRecNode(point[0], point[1]);
		ChooseNonePoint();
	}else{
		ChooseNonePoint();
	}
}

struct ListNodeRec* CreateRecNode(struct ListNodePoint *pStart, struct ListNodePoint *pEnd)
{
	struct ListNodeRec *p, *q, *s;
	p = (struct ListNodeRec*)malloc(sizeof(struct ListNodeRec));
	q = rechead;
	s = rechead;
	while(q != NULL){
		q = q->next;
		if(q != NULL){
			s = s->next;
		}
	}
	s->next = p;
	p->p1 = pStart;
	p->p2 = pEnd;
	p->next = NULL;
	return (p);
}

void drawpagebutton()
{
	if(PageFlag == Homepageflag){
		if(button(GenUIID(0), WindowWidth / 2 - buttonwidth / 2, 0.5 - buttonheight / 2, buttonwidth, buttonheight, "¿ªÊ¼")){
			PageFlag = Drawingpageflag;
			Display();
		}
	}else if(PageFlag == Drawingpageflag){
		if(button(GenUIID(0), WindowWidth / 2 - buttonwidth / 2, 0.5 - buttonheight / 2, buttonwidth, buttonheight, "½áÊø") && FinishFlag == 0){
			ChooseNonePoint();
			DrawFlag = Mouseflag;
			PageFlag = Homepageflag;
			Display();
		}
		if(DrawFlag == Mouseflag){
			DrawHomePage();
		}
	}
}
