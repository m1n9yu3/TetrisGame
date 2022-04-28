#pragma once

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <conio.h>
#include<Windows.h>

/// <summary>
/// 坐标结构体
/// x 为行
/// y 为列
/// </summary>
struct tagCoord {
	int x;
	int y;
};
/// <summary>
/// 游戏结构体
/// 分数
/// 当前使用的方块坐标数组
/// 当前方块的类型
/// 下一个方块的类型
/// </summary>
struct tagTetisPlay
{
	int score;
	int CurBlockType;
	struct tagCoord CurBlockCoord[4];
	int NextBlockType;
	struct tagCoord NextBlockCoord[4];
};

#define MAPCOL 10   // 游戏地图多少列
#define MAPROW 20   // 游戏地图多少行
#define BLOCKLENGTH 4

enum BLOCKTYPE
{
	SQUAREBLOCKSQUARE,
	LEFTSHORTBLOCK_LEFT,
	LEFTSHORTBLOCK_UP,
	RIGHTSHORTBLOCK_LEFT,
	RIGHTSHORTBLOCK_UP,
	LONGBLOCK_COL,				// 长条列
	LONGBLOCK_ROW,				// 长条行
	LEFTLONGBLOCK_LEFT,
	LEFTLONGBLOCK_UP,
	LEFTLONGBLOCK_RIGHT,
	LEFTLONGBLOCK_DOWN,
	RIGHTLONGBLOCK_RIGHT,
	RIGHTLONGBLOCK_UP,
	RIGHTLONGBLOCK_LEFT,
	RIGHTLONGBLOCK_DOWN,
	UNIVEBLOCK_UP,
	UNIVEBLOCK_RIGHT,
	UNIVEBLOCK_DOWN,
	UNIVEBLOCK_LEFT
};
// 方块类型数量
#define BLOCKTYPENUM 18

enum MOVE
{
	LEFTMOVE = 'a',    // 左移一步
	RIGHTMOVE = 'd',   // 右移一步
	DOWNMOVE = ' ',    // 下移到底
	CHANGEMOVE = 'w',  // 方块变形
};

enum myBOOL
{
	NOT,
	YES
};

// 游戏循环
void GameLoop();


// 初始化游戏: 地图的初始化, 结构体成员的初始化，分数，获取当前方块和下一个方块
void InitGame(int* arryMap,struct tagTetisPlay* myTetis);

// 消除方块
int TapBlox(int* arryMap, tagTetisPlay * pMyTetis);

void MoveDownBlock(tagTetisPlay* pMyTetis);

// 移动当前图形
int MoveBlock(int* arryMap, struct tagTetisPlay* myTetis);

// 绘制当前游戏界面
int DrapGui(int* arryMap, struct tagTetisPlay* myTetis);

// 处理底部
int OnButtom(int* arryMap, struct tagTetisPlay* myTetis);


// 获取一个新方块
int GetBlock(tagCoord* NewBlockCoord);

// 获取下一个一个方块
void GetNextBlock(struct tagTetisPlay* myTetis);

// 方块变形函数
int ChangeBlock(int* arryMap, struct tagTetisPlay* pMyTetis);



// 判断是否行越界
int IsInMapCol(int nCol);

// 地图不显示当前运行块
void NoShowCurBlock(int* arryMap, tagTetisPlay* pMyTetis);

// 地图显示当前运行块
void ShowCurBlock(int* arryMap, tagTetisPlay* pMyTetis);

// 向下移动方块
void MoveDownBlock(int* arryMap, tagTetisPlay* pMyTetis, int nStep);

// 碰撞与越界检测
int IsCollisionAndOutMap(int* arryMap, tagTetisPlay* pMyTetis);

// 游戏结束判断
int IsGameOver(int* arryMap, tagTetisPlay* pMyTetis);