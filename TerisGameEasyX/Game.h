#pragma once

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <conio.h>
#include<Windows.h>

#include <graphics.h>		// 引用 EasyX 绘图库头文件
#include<tchar.h>

#define for if(1)for   // 兼容性宏

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
/// 当前方块的类型
/// 当前使用的方块坐标数组
/// 下一个方块的类型
/// 下一个使用的方块坐标数组
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
#define BLOCKLENGTH 4 // 方块坐标数组长度
#define BLOCKSPAC 20  // easyX 中方块大小
#define BLOCKINSPAC1 1  
#define BLOCKINSPAC2 2
#define BLOCKINSPAC3 4

#define DRAWWIDTH BLOCKSPAC * 17        // 地图所占像素宽
#define DRAWHEIGHT BLOCKSPAC * MAPROW	// 地图所占像素高


/// <summary>
/// 方块类型宏
/// </summary>
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

// 热键宏
enum MOVE
{
	LEFTMOVE = 'a',			// 左移一步
	LEFTMOVE_UP = 'A',      // 左移一步
	RIGHTMOVE = 'd',		// 右移一步
	RIGHTMOVE_UP = 'D',		// 右移一步
	DOWNMOVE = ' ',			// 下移到底
	CHANGEMOVE = 'w',		// 方块变形
	CHANGEMOVE_UP = 'W',	// 方块变形
	REGAME = 'r',			// 重新开始游戏
	REGAME_UP = 'R',		// 重新开始游戏
	PAUSEGAME = 'p',		// 暂停游戏
	PAUSEGAME_UP = 'P',		// 暂停游戏
	YESOP = 'y',			// 确认
	YESOP_UP = 'Y',			// 确认
};

// BOOL类型宏
enum myBOOL
{
	NOT,
	YES
};

// GUI 修改函数

/// <summary>
/// 游戏循环
/// </summary>
void GameLoop();

/// <summary>
/// 游戏结束处理， 判断是否重开游戏
/// </summary>
void GameOver(int* arryMap, struct tagTetisPlay* pMyTetis);

/// <summary>
/// 暂停游戏
/// </summary>
void PauseGame();

/// <summary>
/// 重新开始游戏
/// </summary>
/// <param name="arryMap">地图数组</param>
/// <param name="pMyTetis">游戏结构体</param>
/// <returns>重开游戏返回YES, 否则返回NOT</returns>
int ReGame(int* arryMap, tagTetisPlay* pMyTetis);

/// <summary>
/// 绘制当前游戏界面
/// </summary>
/// <param name="arryMap">地图数组</param>
/// <param name="myTetis">游戏结构体</param>
/// <returns>返回YES</returns>
int DrapGui(int* arryMap, struct tagTetisPlay* myTetis);


/// <summary>
/// 绘制单独一个方块
/// </summary>
/// <param name="j">x 坐标</param>
/// <param name="i">y 坐标</param>
/// <param name="RGB1">前景色</param>
/// <param name="RGB2">背景色</param>
void DrawBlock(int j, int i, COLORREF RGB1, COLORREF RGB2);


/// <summary>
/// 初始化游戏: 地图的初始化, 游戏结构体的初始化，分数，获取当前方块和下一个方块
/// </summary>
/// <param name="arryMap">游戏地图，一维数组形式</param>
/// <param name="myTetis">游戏结构体</param>
void InitGame(int* arryMap,struct tagTetisPlay* myTetis);


// UI 与逻辑分析
/// <summary>
/// 消除方块
/// </summary>
/// <param name="arryMap">游戏地图</param>
/// <param name="pMyTetis">游戏结构体</param>
/// <returns>如果消除方块返回 YES, 否则返回 NOT</returns>
int TapBlox(int* arryMap, struct tagTetisPlay * pMyTetis);

/// <summary>
/// 向下移动方块
/// </summary>
/// <param name="arryMap">地图数组</param>
/// <param name="nStep">向下移动的步数</param>
/// <param name="pMyTetis">游戏结构体</param>
void MoveDownBlock(int* arryMap, int nStep, struct tagTetisPlay* pMyTetis);

/// <summary>
/// 移动当前方块， 左右移动，改变当前方块形状
/// </summary>
/// <param name="arryMap">地图数组</param>
/// <param name="myTetis">游戏结构体</param>
/// <returns>操作成功返回YES, 未操作返回NOT</returns>
int Control(int* arryMap, struct tagTetisPlay* myTetis);



/// <summary>
/// 处理底部, 判断方块是否到达底部
/// </summary>
/// <param name="arryMap">地图数组</param>
/// <param name="myTetis">游戏结构体</param>
/// <returns></returns>
int OnButtom(int* arryMap, struct tagTetisPlay* myTetis);


/// <summary>
/// 获取一个新方块
/// </summary>
/// <param name="NewBlockCoord">给定的坐标数组</param>
/// <returns>返回方块类型</returns>
int GetBlock(struct tagCoord* NewBlockCoord);

/// <summary>
/// 获取下一个一个方块
/// </summary>
/// <param name="myTetis">游戏结构体</param>
void GetNextBlock(struct tagTetisPlay* myTetis);

/// <summary>
/// 方块变形函数, 封装了19种方块的变形
/// </summary>
/// <param name="arryMap">游戏地图</param>
/// <param name="pMyTetis">游戏结构体</param>
/// <returns>改变成功返回YES, 未改变返回NOT</returns>
int ChangeBlock(int* arryMap, struct tagTetisPlay* pMyTetis);


/// <summary>
/// 判断是否发生行越界
/// </summary>
/// <param name="nCol"></param>
/// <returns></returns>
int IsInMapCol(int nCol);

/// <summary>
/// 在地图中擦除当前操作方块的痕迹，一般用于移动操作方块
/// </summary>
/// <param name="arryMap">地图数组</param>
/// <param name="pMyTetis">游戏结构体</param>
void NoShowCurBlock(int* arryMap, struct tagTetisPlay* pMyTetis);

/// <summary>
/// 地图显示当前运行块
/// </summary>
/// <param name="arryMap">地图数组</param>
/// <param name="pMyTetis">游戏结构体</param>
void ShowCurBlock(int* arryMap, struct tagTetisPlay* pMyTetis);

/// <summary>
/// 碰撞与越界检测
/// </summary>
/// <param name="arryMap">地图数组</param>
/// <param name="pMyTetis">游戏结构体</param>
/// <returns>碰撞或越界返回YES, 否则返回NOT</returns>
int IsCollisionAndOutMap(int* arryMap, struct tagTetisPlay* pMyTetis);

/// <summary>
/// 游戏结束判断
/// </summary>
/// <param name="arryMap">地图数组</param>
/// <param name="pMyTetis">游戏结构体</param>
/// <returns>结束返回YES,否则返回NOT</returns>
int IsGameOver(int* arryMap, struct tagTetisPlay* pMyTetis);


/// <summary>
/// 游戏暂停结束
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int IsPauseGame(void);
