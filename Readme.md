# Free Geometry Tool 使用手册

本文旨在帮助用户了解如何正确使用该项目，同时帮助互评同学更方便做出评判。

[TOC]

## 开始

首先介绍的是项目的整体框架与如何开始使用该项目。

### 程序组成

该程序共包含六个文件夹，devs储存工程文件与最终生成的可执行文件，codes储存代码，compile储存编译时产生的链接文件，libgraphics与simpleGUI储存图形库函数，bgm储存程序的背景音乐。同时包含两个文件，Readme是使用手册即本文，日志是开发程序时记录的事件。

### 打开或编译程序

我们一方面提供程序的可执行文件，储存于devs文件夹中，启动该文件即可开始使用。另一方面提供源代码可供编译运行，储存于devs文件夹中，启动工程文件后点击编译即可。如果电脑版本较老可能会出现编译错误，可以换一台电脑或者直接打开可执行文件使用。

## 使用说明

其次介绍运行可执行文件后，该项目的功能与使用说明。

### 启动页面

启动页面有三个按钮：第一个是“新建”，会跳转到画图的主页界面中；第二个是“读取”，会读取本地存放的相关文件；第三个是“退出”，即退出程序。

### 主页页面与绘图页面

主页页面的顶部有四个菜单，分别为绘图、编辑、构造、文件。底部有一个按钮为开始。

绘图页面底部有一个按钮为结束。

#### 绘图菜单

鼠标：绘图方式切换为鼠标，即不做绘图动作，但可以进行点的选择。

点：在页面中绘制点。

线：在页面中绘制线，线分为线段、射线、直线，以两点的位置确定一条线。绘制射线时，第一个点将作为端点。

圆：在页面中绘制圆，第一个点将作为圆心，第二个点将作为圆上的一点用于确定半径。

圆弧：在页面中绘制圆弧，第一个点将作为圆心，第二个点将作为圆弧上的起点用于确定半径与起点的角度，第三个点将用于确定终点的角度。

矩形：在页面中绘制矩形，第一个点将作为矩形的左上角或右下角，第二个点将作为矩形的对角。

多边形：在页面中绘制多边形，第一个点将作为起点，随后的每一个点都将依次作为多边形上的端点并依次连线形成多边形，点击起点将结束绘制。为了绘图形式的区分，分为开放与闭合，选择闭合时，当前绘制的点与起点将连线，表示闭合的多边形，加强视觉效果。

#### 编辑菜单

全选：表示点的全选，可用Ctrl-A代替。

全不选：表示点的全不选。

隐藏：被选中的点将被隐藏，不会作为已有的点对之后的绘图操作有干扰，可用Ctrl-H代替。

全显示：所有点全部取消隐藏。

点型：可选择点为空心或实心。

线型：可选择线为细线或粗线。

网格：可选择网格隐藏或显示。

颜色：可选择被选中的点显示的颜色。

#### 构造菜单

中点：绘制选中的两个点的中点，可用Ctrl-M代替。

线段：绘制选中的两个点的线段，可用Ctrl-L代替。

直线：绘制经过选中的两个点的直线。

矩形：绘制以选中的，两个点作为左上角和右下角的矩形。

#### 文件菜单

保存：将页面中的数据保存于选定的文本文件中，可用Ctrl-S代替。

退出：退出程序，可用Ctrl-Q代替。

#### 开始或结束按钮

开始：将跳转至绘图页面，但顶部菜单保留，会出现画布的界面。

结束：将跳转至主页页面。

## 一些需要注意的地方

- 绘图页面中会出现上下两条线，表示绘图时的界面，所有需要绘制的点不能超过该边框。
- 大多数功能中，点可以绘制，也可以选择已有的点，当选择时鼠标会自动吸附至已有的点。
- 当绘制功能尚未结束时，点击结束按钮不会退出绘图页面。
- 大多数功能中，选择重复的点不会被记录，需要一个真正的点。但对其中的部分功能做出以下说明：点功能当与已有的点重合时不会再次绘制点；圆弧功能当第三个点与第一个点或第二个点重合时，将直接绘制整个圆；多边形功能当随后的点与已有的多边形端点重合时，将结束绘制形成多边形。
- 线功能、多边形功能、颜色选择需要点击下列的二级菜单才是有效选择。
- 点型选择，线型选择，网格选择后的内容均为目前状态。

## 后记

程序中设有一些较为贴心的功能但在此不做介绍，请各位自行探索。在大一一年学到了很多C语言的知识，在此感谢C小程和C大程两位老师和两位助教的指导，朋辈辅学的学长对我大程设计的巨大帮助，组员们的勤劳付出，最终完成了整个项目。由于能力所限，如有使用上的问题或需要继续改进的地方，请您不吝赐教，我们会尽快改进程序，把项目做得更好。