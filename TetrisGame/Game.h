#pragma once

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <conio.h>
#include<Windows.h>

/// <summary>
/// ����ṹ��
/// x Ϊ��
/// y Ϊ��
/// </summary>
struct tagCoord {
	int x;
	int y;
};
/// <summary>
/// ��Ϸ�ṹ��
/// ����
/// ��ǰʹ�õķ�����������
/// ��ǰ���������
/// ��һ�����������
/// </summary>
struct tagTetisPlay
{
	int score;
	int CurBlockType;
	struct tagCoord CurBlockCoord[4];
	int NextBlockType;
	struct tagCoord NextBlockCoord[4];
};

#define MAPCOL 10   // ��Ϸ��ͼ������
#define MAPROW 20   // ��Ϸ��ͼ������
#define BLOCKLENGTH 4

enum BLOCKTYPE
{
	SQUAREBLOCKSQUARE,
	LEFTSHORTBLOCK_LEFT,
	LEFTSHORTBLOCK_UP,
	RIGHTSHORTBLOCK_LEFT,
	RIGHTSHORTBLOCK_UP,
	LONGBLOCK_COL,				// ������
	LONGBLOCK_ROW,				// ������
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
// ������������
#define BLOCKTYPENUM 18

enum MOVE
{
	LEFTMOVE = 'a',    // ����һ��
	RIGHTMOVE = 'd',   // ����һ��
	DOWNMOVE = ' ',    // ���Ƶ���
	CHANGEMOVE = 'w',  // �������
};

enum myBOOL
{
	NOT,
	YES
};

// ��Ϸѭ��
void GameLoop();


// ��ʼ����Ϸ: ��ͼ�ĳ�ʼ��, �ṹ���Ա�ĳ�ʼ������������ȡ��ǰ�������һ������
void InitGame(int* arryMap,struct tagTetisPlay* myTetis);

// ��������
int TapBlox(int* arryMap, tagTetisPlay * pMyTetis);

void MoveDownBlock(tagTetisPlay* pMyTetis);

// �ƶ���ǰͼ��
int MoveBlock(int* arryMap, struct tagTetisPlay* myTetis);

// ���Ƶ�ǰ��Ϸ����
int DrapGui(int* arryMap, struct tagTetisPlay* myTetis);

// ����ײ�
int OnButtom(int* arryMap, struct tagTetisPlay* myTetis);


// ��ȡһ���·���
int GetBlock(tagCoord* NewBlockCoord);

// ��ȡ��һ��һ������
void GetNextBlock(struct tagTetisPlay* myTetis);

// ������κ���
int ChangeBlock(int* arryMap, struct tagTetisPlay* pMyTetis);



// �ж��Ƿ���Խ��
int IsInMapCol(int nCol);

// ��ͼ����ʾ��ǰ���п�
void NoShowCurBlock(int* arryMap, tagTetisPlay* pMyTetis);

// ��ͼ��ʾ��ǰ���п�
void ShowCurBlock(int* arryMap, tagTetisPlay* pMyTetis);

// �����ƶ�����
void MoveDownBlock(int* arryMap, tagTetisPlay* pMyTetis, int nStep);

// ��ײ��Խ����
int IsCollisionAndOutMap(int* arryMap, tagTetisPlay* pMyTetis);

// ��Ϸ�����ж�
int IsGameOver(int* arryMap, tagTetisPlay* pMyTetis);