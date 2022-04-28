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
/// ��ǰ���������
/// ��ǰʹ�õķ�����������
/// ��һ�����������
/// ��һ��ʹ�õķ�����������
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
#define BLOCKLENGTH 4 // �����������鳤��

/// <summary>
/// �������ͺ�
/// </summary>
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

// �ȼ���
enum MOVE
{
	LEFTMOVE = 'a',    // ����һ��
	RIGHTMOVE = 'd',   // ����һ��
	DOWNMOVE = ' ',    // ���Ƶ���
	CHANGEMOVE = 'w',  // �������
};

// BOOL���ͺ�
enum myBOOL
{
	NOT,
	YES
};

/// <summary>
/// ��Ϸѭ��
/// </summary>
void GameLoop();


/// <summary>
/// ��ʼ����Ϸ: ��ͼ�ĳ�ʼ��, ��Ϸ�ṹ��ĳ�ʼ������������ȡ��ǰ�������һ������
/// </summary>
/// <param name="arryMap">��Ϸ��ͼ��һά������ʽ</param>
/// <param name="myTetis">��Ϸ�ṹ��</param>
void InitGame(int* arryMap,struct tagTetisPlay* myTetis);

/// <summary>
/// ��������
/// </summary>
/// <param name="arryMap">��Ϸ��ͼ</param>
/// <param name="pMyTetis">��Ϸ�ṹ��</param>
/// <returns>����������鷵�� YES, ���򷵻� NOT</returns>
int TapBlox(int* arryMap, struct tagTetisPlay * pMyTetis);

/// <summary>
/// �����ƶ�����
/// </summary>
/// <param name="arryMap">��ͼ����</param>
/// <param name="nStep">�����ƶ��Ĳ���</param>
/// <param name="pMyTetis">��Ϸ�ṹ��</param>
void MoveDownBlock(int* arryMap, int nStep, struct tagTetisPlay* pMyTetis);

/// <summary>
/// �ƶ���ǰ���飬 �����ƶ����ı䵱ǰ������״
/// </summary>
/// <param name="arryMap">��ͼ����</param>
/// <param name="myTetis">��Ϸ�ṹ��</param>
/// <returns>�����ɹ�����YES, δ��������NOT</returns>
int MoveBlock(int* arryMap, struct tagTetisPlay* myTetis);

/// <summary>
/// ���Ƶ�ǰ��Ϸ����
/// </summary>
/// <param name="arryMap">��ͼ����</param>
/// <param name="myTetis">��Ϸ�ṹ��</param>
/// <returns>����YES</returns>
int DrapGui(int* arryMap, struct tagTetisPlay* myTetis);

/// <summary>
/// ����ײ�, �жϷ����Ƿ񵽴�ײ�
/// </summary>
/// <param name="arryMap">��ͼ����</param>
/// <param name="myTetis">��Ϸ�ṹ��</param>
/// <returns></returns>
int OnButtom(int* arryMap, struct tagTetisPlay* myTetis);


/// <summary>
/// ��ȡһ���·���
/// </summary>
/// <param name="NewBlockCoord">��������������</param>
/// <returns>���ط�������</returns>
int GetBlock(struct tagCoord* NewBlockCoord);

/// <summary>
/// ��ȡ��һ��һ������
/// </summary>
/// <param name="myTetis">��Ϸ�ṹ��</param>
void GetNextBlock(struct tagTetisPlay* myTetis);

/// <summary>
/// ������κ���, ��װ��19�ַ���ı���
/// </summary>
/// <param name="arryMap">��Ϸ��ͼ</param>
/// <param name="pMyTetis">��Ϸ�ṹ��</param>
/// <returns>�ı�ɹ�����YES, δ�ı䷵��NOT</returns>
int ChangeBlock(int* arryMap, struct tagTetisPlay* pMyTetis);



/// <summary>
/// �ж��Ƿ�����Խ��
/// </summary>
/// <param name="nCol"></param>
/// <returns></returns>
int IsInMapCol(int nCol);

/// <summary>
/// �ڵ�ͼ�в�����ǰ��������ĺۼ���һ�������ƶ���������
/// </summary>
/// <param name="arryMap">��ͼ����</param>
/// <param name="pMyTetis">��Ϸ�ṹ��</param>
void NoShowCurBlock(int* arryMap, struct tagTetisPlay* pMyTetis);

/// <summary>
/// ��ͼ��ʾ��ǰ���п�
/// </summary>
/// <param name="arryMap">��ͼ����</param>
/// <param name="pMyTetis">��Ϸ�ṹ��</param>
void ShowCurBlock(int* arryMap, struct tagTetisPlay* pMyTetis);

/// <summary>
/// ��ײ��Խ����
/// </summary>
/// <param name="arryMap">��ͼ����</param>
/// <param name="pMyTetis">��Ϸ�ṹ��</param>
/// <returns>��ײ��Խ�緵��YES, ���򷵻�NOT</returns>
int IsCollisionAndOutMap(int* arryMap, struct tagTetisPlay* pMyTetis);

/// <summary>
/// ��Ϸ�����ж�
/// </summary>
/// <param name="arryMap">��ͼ����</param>
/// <param name="pMyTetis">��Ϸ�ṹ��</param>
/// <returns>��������YES,���򷵻�NOT</returns>
int IsGameOver(int* arryMap, struct tagTetisPlay* pMyTetis);
