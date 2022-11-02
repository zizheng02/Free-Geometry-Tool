#ifndef _SCX_H_
#define _SCX_H_

struct ListNodeSector{
	struct ListNodePoint *p;
	double r, t1, t2;
	struct ListNodeSector *next;
};

extern struct ListNodeSector *sectorhead;

void drawSector();
void CreateSector();
struct ListNodeSector* CreateSectorNode(struct ListNodePoint *start, double theta1, double theta2, double radius);
void CreateLine();
void CreateRay();

#endif

