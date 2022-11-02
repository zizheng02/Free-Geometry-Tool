#include "globalDefine.h" 

struct ListNodeSector *sectorhead;

void drawSector()
{
	struct ListNodeSector *p;
	p = sectorhead;
	while(p != NULL){
		if(p == sectorhead){
			p = p->next;
		}else{
			MovePen(p->p->x + p->r * cos(p->t1 / 180 * M_PI) , p->p->y + p->r * sin(p->t1 / 180 * M_PI));
			DrawArc(p->r, p->t1 , p->t2 - p->t1 );
			p = p->next;
		}
	}
}

void CreateSector()
{
	if(DrawFlag == Sectorflag){
		static int CreateSectorPoint1 = 0, CreateSectorPoint2 = 0;
		static struct ListNodePoint *pStart1, *pStart2, *pEnd, *p;
		static double r, theta1, theta2;
		static struct ListNodePoint *q;
		static int uselessflag = 0;
		if(uselessflag == 0){
			q = pointhead;
			uselessflag = 1;
		}
		p = pointfound(mouse_x, mouse_y);
/*find or draw the center*/ 
		if(CreateSectorPoint1 == 0 && CreateSectorPoint2 == 0){
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
						pStart1 = CreatePointNode(mouse_x, mouse_y);
					}else{
						pStart1 = p;
					}
					CreateSectorPoint1 = 1;	
					FinishFlag = 1;
				}
			}
/*find or draw the starting point*/
		}else if(CreateSectorPoint1 == 1 && CreateSectorPoint2 == 0){				
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
						pStart2 = CreatePointNode(mouse_x, mouse_y);
						r = sqrt((pStart2->x - pStart1->x) * (pStart2->x - pStart1->x) + (pStart2->y - pStart1->y) * (pStart2->y - pStart1->y));
						theta1 = atan2((pStart2->y - pStart1->y), (pStart2->x - pStart1->x)) / M_PI * 180;
						CreateSectorPoint2 = 1;
						FinishFlag = 1;
					}else if(p != pStart1){
						pStart2 = p;
						r = sqrt((pStart2->x - pStart1->x) * (pStart2->x - pStart1->x) + (pStart2->y - pStart1->y) * (pStart2->y - pStart1->y));
						theta1 = atan2((pStart2->y - pStart1->y), (pStart2->x - pStart1->x)) / M_PI * 180;
						CreateSectorPoint2 = 1;
						FinishFlag = 1;
					}
				}
			}
/*find the end of sector*/			
		}else if(CreateSectorPoint1 == 1 && CreateSectorPoint2 == 1){
			if(p == NULL){
				q->chosenflag = 0;
				q = pointhead;
				theta2 = atan2((mouse_y - pStart1->y), (mouse_x - pStart1->x)) / M_PI * 180;
				if(pointchosen(mouse_x, mouse_y, pStart1->x + r * cos(theta2 / 180 * M_PI), pStart1->y + r * sin(theta2 / 180 * M_PI)) == TRUE){
	                drawthepoint(pStart1->x + r * cos(theta2 / 180 * M_PI), pStart1->y + r * sin(theta2 / 180 * M_PI), pointsize * 2, 0);
				}else{
					drawthepoint(mouse_x, mouse_y, pointsize, 0);
				}
	            drawthepoint(pStart1->x + r * cos(theta2 / 180 * M_PI), pStart1->y + r * sin(theta2 / 180 * M_PI), pointsize, 0);
				MovePen(pStart2->x, pStart2->y);
				theta2 = atan2((mouse_y - pStart1->y), (mouse_x - pStart1->x)) / M_PI * 180;
				if(theta2 < theta1){
					theta2 = 360 + theta2;
				}
				DrawArc(r, theta1, theta2-theta1);
			}else{
				q = p;
				q->chosenflag = 1;
				theta2 = atan2((p->y - pStart1->y), (p->x - pStart1->x)) / M_PI * 180;
				drawthepoint(p->x, p->y, pointsize * 2, 0);
				if(p == pStart1 || p == pStart2){
					theta2 = 360 + theta1;
					MovePen(pStart2->x, pStart2->y);
					DrawArc(r, theta1, 360);
				}else{
	                drawthepoint(pStart1->x + r * cos(theta2 / 180 * M_PI), pStart1->y + r * sin(theta2 / 180 * M_PI), pointsize, 0);
					MovePen(pStart2->x , pStart2->y);
					if(theta2 < theta1){
						theta2 = 360 + theta2;
					}
					DrawArc(r, theta1, theta2 - theta1);
				}
			}
			if(mouse_Event == BUTTON_DOWN && mouse_button == LEFT_BUTTON){
				if(InCanvas(mouse_x, mouse_y)){
					pEnd = CreatePointNode(pStart1->x + r * cos(theta2 / 180 * M_PI), pStart1->y + r * sin(theta2 / 180 * M_PI));
					CreateSectorPoint1 = 0;
					CreateSectorPoint2 = 0;
					FinishFlag = 0;
					struct ListNodeSector *c;
					c = CreateSectorNode(pStart1, theta1, theta2, r);
				}
			}
		}
	}	
}
	
struct ListNodeSector* CreateSectorNode(struct ListNodePoint *start,  double theta1, double theta2, double radius){
	struct ListNodeSector *t, *q, *s;
	t = (struct ListNodeSector*)malloc(sizeof(struct ListNodeSector));
	q = sectorhead;
	s = sectorhead;
	while(q != NULL){
		q = q->next;
		if(q != NULL){
			s = s->next;
		}
	}
	s->next = t;
	t->p = start;
	t->t1 = theta1;
	t->t2 = theta2;
	t->r = radius;
	t->next = NULL;
	return (t);
}

void CreateLine()
{
	if(DrawFlag == Lineflag){
		static int createlinepoint = 0;
		static struct ListNodePoint *pStart, *pEnd, *p, *pStart1, *pEnd1;
		static struct ListNodePoint *q;
		static int uselessflag = 0;
		if(uselessflag == 0){
			q = pointhead;
			uselessflag = 1;
		}
		p = pointfound(mouse_x, mouse_y);
		if(createlinepoint == 0){
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
					createlinepoint = 1;
					FinishFlag = 1;
				}
			}
		}else{
/*find or draw the second point*/
			if(p == NULL){
				q->chosenflag = 0;
				q = pointhead;
				drawthepoint(mouse_x, mouse_y, pointsize, 0);
				MovePen(pStart->x - (mouse_x - pStart->x) * length, pStart->y - (mouse_y - pStart->y) * length);
				DrawLine((mouse_x - pStart->x) * length * 2, (mouse_y - pStart->y) * length * 2);
			}else{
				q = p;
				q->chosenflag = 1;
				drawthepoint(p->x, p->y, pointsize * 2, 0);
				MovePen(pStart->x - (p->x - pStart->x) * length, pStart->y - (p->y - pStart->y) * length);
				DrawLine((p->x - pStart->x) * length * 2, (p->y - pStart->y) * length * 2);
			}
			if(mouse_Event == BUTTON_DOWN && mouse_button == LEFT_BUTTON){
				if(InCanvas(mouse_x, mouse_y)){
					if(p == NULL){
						pEnd = CreatePointNode(mouse_x,mouse_y);
						createlinepoint = 0;
						FinishFlag = 0;
						CreateLineNode(pStart, pEnd, Lineflag);
					}else if(p != pStart){
						pEnd = p;
						createlinepoint = 0;
						FinishFlag = 0;
						CreateLineNode(pStart, pEnd, Lineflag);
					}
				}
			}
		}
	}
}

void CreateRay()
{
	if(DrawFlag == Rayflag){
		static int createraypoint = 0;
		static struct ListNodePoint *pStart, *pEnd, *p, *pEnd1;
		static struct ListNodePoint *q;
		static int uselessflag = 0;
		if(uselessflag == 0){
			q = pointhead;
			uselessflag = 1;
		}
		p = pointfound(mouse_x, mouse_y);
		if(createraypoint == 0){
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
					createraypoint = 1;
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
				DrawLine((mouse_x - pStart->x) * length, (mouse_y - pStart->y) * length);
			}else{
				q = p;
				q->chosenflag = 1;
				drawthepoint(p->x, p->y, pointsize * 2, 0);
				MovePen(pStart->x, pStart->y);
				DrawLine((p->x - pStart->x) * length, (p->y - pStart->y) * length);
			}
			if(mouse_Event == BUTTON_DOWN && mouse_button == LEFT_BUTTON){
				if(InCanvas(mouse_x, mouse_y)){
					if(p == NULL){
						pEnd = CreatePointNode(mouse_x,mouse_y);
						createraypoint = 0;
						FinishFlag = 0;
						CreateLineNode(pStart, pEnd, Rayflag);
					}
					else if(p != pStart){
						pEnd = p;
						createraypoint = 0;
						FinishFlag = 0;
						CreateLineNode(pStart, pEnd, Rayflag);
					}
				}
			}
		}
	}
}
