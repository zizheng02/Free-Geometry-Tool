#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h> 
#include <mmsystem.h>
#include <string.h>
#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"
#include "boolean.h"
#include "geo_funcs01.h"
#include "geo_funcs02.h"
#include "geo_funcs03.h" 
//#include "file.h" 

#define menulistwidth 1.25
#define menulistheight 0.25
#define buttonwidth 2
#define buttonheight 0.8
#define pointsize 0.05
#define length 10
#define canvassize 0.07

#define Mouseflag 1
#define Pointflag 2
#define Segmentflag 4
#define Lineflag 5
#define Rayflag 6
#define Circleflag 7
#define Sectorflag 8
#define Recflag 9
#define Polyflag 10
#define OpenPolyflag 11
#define ClosePolyflag 12

#define Startpageflag 0 
#define Homepageflag 1
#define Drawingpageflag 2

#define PointSolidorHollow 5
#define LineThickorThin 6
#define GridHideorAppear 7
#define Redflag 9
#define Orangeflag 10
#define Blueflag 11

#endif
