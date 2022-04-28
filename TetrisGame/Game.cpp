#include"Game.h"

int aryMap[MAPROW][MAPCOL] = { 0 };

int GetMapPointer(int* arryMap, int nX, int nY)
{
	return arryMap[nY * MAPCOL + nX];
}

int SetMapPointer(int* arryMap, int nX, int nY, int nValue)
{
	arryMap[nY * MAPCOL + nX] = nValue;
	return YES;
}

void GameLoop()
{
	srand((unsigned int)time(NULL));


	struct tagTetisPlay myTetis;
	InitGame((int*)aryMap, &myTetis);
	time_t startTime = time(NULL);
	time_t endTime = startTime;

	DrapGui((int*)aryMap, &myTetis);

	while (true)
	{
		endTime = time(NULL);

		if (endTime - startTime >= 1)
		{
			startTime = endTime;
			MoveDownBlock((int*)aryMap, &myTetis, 1);
			DrapGui((int*)aryMap, &myTetis);
		}
		if (MoveBlock((int*)aryMap, &myTetis) == YES)
		{
			DrapGui((int*)aryMap, &myTetis);
		}


		//DrapGui((int*)aryMap, &myTetis);

		if (OnButtom((int*)aryMap, &myTetis) == YES)
		{
			TapBlox((int*)aryMap, &myTetis);
			DrapGui((int*)aryMap, &myTetis);

			if (IsGameOver((int*)aryMap, &myTetis))
			{
				printf("游戏结束!\r\n");
				break;
			}

			GetNextBlock(&myTetis);


	
		}
	}


}

void InitGame(int* arryMap, struct tagTetisPlay* pMyTetis)
{
	// 初始化分数 当前块 下一个块
	pMyTetis->score = 0;
	pMyTetis->CurBlockType = GetBlock(pMyTetis->CurBlockCoord);
	pMyTetis->NextBlockType = GetBlock(pMyTetis->NextBlockCoord);

	for (int i = 0; i < MAPCOL; i++)
	{
		for (int j = 0; j < MAPROW; j++)
		{
			arryMap[MAPCOL * i + j] = 0;
		}
	}


}

int TapBlox(int* arryMap, tagTetisPlay * pMyTetis)
{
	int retMsg = NOT;
	//NoShowCurBlock(arryMap, pMyTetis);

	for (int nCurRow = 0; nCurRow < MAPROW; nCurRow++)
	{
		int nFullBlock = 0;
		for (int nCurCol = 0; nCurCol < MAPCOL; nCurCol++)
		{
			if (GetMapPointer(arryMap, nCurCol, nCurRow) == 1)
			{
				nFullBlock += 1;
			}
		}

		// 如果一行都是满状态，则开始消除方块
		if (nFullBlock == MAPCOL)
		{
			retMsg = YES;
			for (int i = nCurRow; i > 1; i--)
			{
				for (int j = 0; j < MAPCOL; j++)
				{
					SetMapPointer(arryMap, j, i, GetMapPointer(arryMap, j, i - 1));
				}
			}
			// 第 0 行填充 空方块
			for (int i = 0; i < MAPCOL; i++)
			{
				SetMapPointer(arryMap, i, 0, 0);
			}

			pMyTetis->score += 10;
		}
	}

	//ShowCurBlock(arryMap, pMyTetis);
	return retMsg;
}

void MoveDownBlock(int* arryMap, tagTetisPlay* pMyTetis, int nStep)
{
	NoShowCurBlock(arryMap, pMyTetis);
	for (int i = 0; i < BLOCKLENGTH; i++)
	{
		pMyTetis->CurBlockCoord[i].y = pMyTetis->CurBlockCoord[i].y + nStep;
	}
	ShowCurBlock(arryMap, pMyTetis);
}

int MoveBlock(int* arryMap, tagTetisPlay* pMyTetis)
{
	tagTetisPlay tmpMyTetis = *pMyTetis;
	int retMsg = YES;
	// 取消地图显示
	NoShowCurBlock(arryMap, pMyTetis);

	if (!_kbhit())
	{
		return NOT;
		
	}
	else
	{
		char cDirection = ' ';
		cDirection = _getch();

		switch (cDirection)
		{
		case LEFTMOVE:
		{
			// 检查边界
			for (int i = 0; i < BLOCKLENGTH; i++)
			{
				tmpMyTetis.CurBlockCoord[i].x = tmpMyTetis.CurBlockCoord[i].x - 1;
			}
			if (IsCollisionAndOutMap(arryMap, &tmpMyTetis) == YES)
			{
				retMsg = NOT;
			}

		}break;
		case RIGHTMOVE:
		{
			for (int i = 0; i < BLOCKLENGTH; i++)
			{
				tmpMyTetis.CurBlockCoord[i].x = tmpMyTetis.CurBlockCoord[i].x + 1;
			}
			if (IsCollisionAndOutMap(arryMap, &tmpMyTetis) == YES)
			{
				retMsg = NOT;
			}

		}break;
		case DOWNMOVE:
		{
			// 检查边界
			for (int i = 0; i < MAPROW; i++)
			{
				for (int j = 0; j < BLOCKLENGTH; j++)
				{
					tmpMyTetis.CurBlockCoord[j].y = tmpMyTetis.CurBlockCoord[j].y + 1;
				}
				if (IsCollisionAndOutMap(arryMap, &tmpMyTetis) == YES)
				{
					for (int k = 0; k < BLOCKLENGTH; k++)
					{
						tmpMyTetis.CurBlockCoord[k].y = tmpMyTetis.CurBlockCoord[k].y - 1;
					}
					break;
				}
			}

		}break;
		case CHANGEMOVE:
		{
			retMsg = ChangeBlock(arryMap, &tmpMyTetis);

		}break;
		// 默认逻辑向下一步
		default:
		break;
		}
	}

	if (retMsg == YES)
	{
		*pMyTetis = tmpMyTetis;
	}

	rewind(stdin);
	// 使用新的标记
	ShowCurBlock(arryMap, pMyTetis);
	return YES;
}

int DrapGui(int* arryMap, tagTetisPlay* pMyTetis)
{
	system("cls");
	for (int i = 0; i < MAPROW; i++)
	{
		for (int j = 0; j < MAPCOL; j++)
		{
			if (arryMap[i * MAPCOL + j] == 0)
			{
				printf("□ ");
			}
			else
			{
				printf("■ ");
			}


		}
		printf("\n");
	}

	printf("当前分数: %d\r\n", pMyTetis->score);
	// 打印下一个 方块

	int nextBlockMap[BLOCKLENGTH][BLOCKLENGTH] = { 0 };
	for (int i = 0; i < BLOCKLENGTH; i++)
	{
		int nX = pMyTetis->NextBlockCoord[i].x - 4;
		int nY = pMyTetis->NextBlockCoord[i].y + 4;
		nextBlockMap[nX][nY] = 1;
	}

	for (int i = 0; i < BLOCKLENGTH; i++)
	{
		for (int j = 0; j < BLOCKLENGTH; j++)
		{

			if (nextBlockMap[j][i] == 0)
			{
				printf("□ ");
			}
			else
			{
				printf("■ ");
			}

		}
		printf("\n");
	}

	return 0;
}

int GetBlock(tagCoord* NewBlockCoord)
{

	int curSelectBlockType = rand() % BLOCKTYPENUM;

	switch (curSelectBlockType)
	{
	case SQUAREBLOCKSQUARE:
	{
		NewBlockCoord[0].x = 4;
		NewBlockCoord[0].y = -2;
		NewBlockCoord[1].x = 5;
		NewBlockCoord[1].y = -2;

		NewBlockCoord[2].x = 4;
		NewBlockCoord[2].y = -1;
		NewBlockCoord[3].x = 5;
		NewBlockCoord[3].y = -1;
	}break;
	case LEFTSHORTBLOCK_LEFT:
	{
		NewBlockCoord[0].x = 4;
		NewBlockCoord[0].y = -2;
		NewBlockCoord[1].x = 5;
		NewBlockCoord[1].y = -2;

		NewBlockCoord[2].x = 5;
		NewBlockCoord[2].y = -1;
		NewBlockCoord[3].x = 6;
		NewBlockCoord[3].y = -1;
	}break;
	case LEFTSHORTBLOCK_UP:
	{
		NewBlockCoord[0].x = 4;
		NewBlockCoord[0].y = -2;
		NewBlockCoord[1].x = 5;
		NewBlockCoord[1].y = -2;

		NewBlockCoord[2].x = 5;
		NewBlockCoord[2].y = -3;
		NewBlockCoord[3].x = 4;
		NewBlockCoord[3].y = -1;
	}break;


	case RIGHTSHORTBLOCK_LEFT:
	{
		NewBlockCoord[0].x = 5;
		NewBlockCoord[0].y = -2;
		NewBlockCoord[1].x = 6;
		NewBlockCoord[1].y = -2;

		NewBlockCoord[2].x = 4;
		NewBlockCoord[2].y = -1;
		NewBlockCoord[3].x = 5;
		NewBlockCoord[3].y = -1;
	}break;
	case RIGHTSHORTBLOCK_UP:
	{
		NewBlockCoord[0].x = 5;
		NewBlockCoord[0].y = -2;
		NewBlockCoord[1].x = 6;
		NewBlockCoord[1].y = -2;

		NewBlockCoord[2].x = 6;
		NewBlockCoord[2].y = -1;
		NewBlockCoord[3].x = 5;
		NewBlockCoord[3].y = -3;
	}break;


	case LONGBLOCK_COL:
	{
		NewBlockCoord[0].x = 4;
		NewBlockCoord[0].y = -1;
		NewBlockCoord[1].x = 4;
		NewBlockCoord[1].y = -2;

		NewBlockCoord[2].x = 4;
		NewBlockCoord[2].y = -3;
		NewBlockCoord[3].x = 4;
		NewBlockCoord[3].y = -4;
	}break;
	case LONGBLOCK_ROW:
	{
		NewBlockCoord[0].x = 4;
		NewBlockCoord[0].y = -1;
		NewBlockCoord[1].x = 5;
		NewBlockCoord[1].y = -1;

		NewBlockCoord[2].x = 6;
		NewBlockCoord[2].y = -1;
		NewBlockCoord[3].x = 7;
		NewBlockCoord[3].y = -1;
	}break;


	case LEFTLONGBLOCK_LEFT:
	{
		NewBlockCoord[0].x = 4;
		NewBlockCoord[0].y = -1;
		NewBlockCoord[1].x = 5;
		NewBlockCoord[1].y = -1;

		NewBlockCoord[2].x = 5;
		NewBlockCoord[2].y = -2;
		NewBlockCoord[3].x = 5;
		NewBlockCoord[3].y = -3;
	}break;
	case LEFTLONGBLOCK_UP:
	{
		NewBlockCoord[0].x = 4;
		NewBlockCoord[0].y = -2;
		NewBlockCoord[1].x = 4;
		NewBlockCoord[1].y = -1;

		NewBlockCoord[2].x = 5;
		NewBlockCoord[2].y = -1;
		NewBlockCoord[3].x = 6;
		NewBlockCoord[3].y = -1;
	}break;
	case LEFTLONGBLOCK_RIGHT:
	{
		NewBlockCoord[0].x = 6;
		NewBlockCoord[0].y = -3;
		NewBlockCoord[1].x = 5;
		NewBlockCoord[1].y = -3;

		NewBlockCoord[2].x = 5;
		NewBlockCoord[2].y = -2;
		NewBlockCoord[3].x = 5;
		NewBlockCoord[3].y = -1;
	}break;
	case LEFTLONGBLOCK_DOWN:
	{
		NewBlockCoord[0].x = 6;
		NewBlockCoord[0].y = -1;
		NewBlockCoord[1].x = 6;
		NewBlockCoord[1].y = -2;

		NewBlockCoord[2].x = 5;
		NewBlockCoord[2].y = -2;
		NewBlockCoord[3].x = 4;
		NewBlockCoord[3].y = -2;
	}break;


	case RIGHTLONGBLOCK_RIGHT:
	{
		NewBlockCoord[0].x = 4;
		NewBlockCoord[0].y = -1;
		NewBlockCoord[1].x = 5;
		NewBlockCoord[1].y = -1;

		NewBlockCoord[2].x = 4;
		NewBlockCoord[2].y = -2;
		NewBlockCoord[3].x = 4;
		NewBlockCoord[3].y = -3;
	}break;
	case RIGHTLONGBLOCK_UP:
	{
		NewBlockCoord[0].x = 4;
		NewBlockCoord[0].y = -1;
		NewBlockCoord[1].x = 5;
		NewBlockCoord[1].y = -1;

		NewBlockCoord[2].x = 6;
		NewBlockCoord[2].y = -1;
		NewBlockCoord[3].x = 6;
		NewBlockCoord[3].y = -2;
	}break;
	case RIGHTLONGBLOCK_LEFT:
	{
		NewBlockCoord[0].x = 5;
		NewBlockCoord[0].y = -2;
		NewBlockCoord[1].x = 5;
		NewBlockCoord[1].y = -1;

		NewBlockCoord[2].x = 5;
		NewBlockCoord[2].y = -3;
		NewBlockCoord[3].x = 4;
		NewBlockCoord[3].y = -3;
	}break;
	case RIGHTLONGBLOCK_DOWN:
	{
		NewBlockCoord[0].x = 5;
		NewBlockCoord[0].y = -2;
		NewBlockCoord[1].x = 6;
		NewBlockCoord[1].y = -2;

		NewBlockCoord[2].x = 4;
		NewBlockCoord[2].y = -2;
		NewBlockCoord[3].x = 4;
		NewBlockCoord[3].y = -1;
	}break;


	case UNIVEBLOCK_UP:
	{
		NewBlockCoord[0].x = 5;
		NewBlockCoord[0].y = -2;
		NewBlockCoord[1].x = 5;
		NewBlockCoord[1].y = -1;

		NewBlockCoord[2].x = 6;
		NewBlockCoord[2].y = -1;
		NewBlockCoord[3].x = 4;
		NewBlockCoord[3].y = -1;
	}break;
	case UNIVEBLOCK_RIGHT:
	{
		NewBlockCoord[0].x = 5;
		NewBlockCoord[0].y = -2;
		NewBlockCoord[1].x = 5;
		NewBlockCoord[1].y = -1;

		NewBlockCoord[2].x = 6;
		NewBlockCoord[2].y = -2;
		NewBlockCoord[3].x = 5;
		NewBlockCoord[3].y = -3;
	}break;
	case UNIVEBLOCK_DOWN:
	{
		NewBlockCoord[0].x = 5;
		NewBlockCoord[0].y = -2;
		NewBlockCoord[1].x = 5;
		NewBlockCoord[1].y = -1;

		NewBlockCoord[2].x = 6;
		NewBlockCoord[2].y = -2;
		NewBlockCoord[3].x = 4;
		NewBlockCoord[3].y = -2;
	}break;
	case UNIVEBLOCK_LEFT:
	{
		NewBlockCoord[0].x = 5;
		NewBlockCoord[0].y = -2;
		NewBlockCoord[1].x = 5;
		NewBlockCoord[1].y = -1;

		NewBlockCoord[2].x = 4;
		NewBlockCoord[2].y = -2;
		NewBlockCoord[3].x = 5;
		NewBlockCoord[3].y = -3;
	}break;
	default:
		break;
	}

	return curSelectBlockType;
}

void GetNextBlock(struct tagTetisPlay* pMyTetis)
{
	// 下一个节点置换前一个节点
	for (int i = 0; i < BLOCKLENGTH; i++)
	{
		pMyTetis->CurBlockCoord[i].x = pMyTetis->NextBlockCoord[i].x;
		pMyTetis->CurBlockCoord[i].y = pMyTetis->NextBlockCoord[i].y;
	}
	pMyTetis->CurBlockType = pMyTetis->NextBlockType;

	pMyTetis->NextBlockType = GetBlock(pMyTetis->NextBlockCoord);
}

int ChangeBlock(int* arryMap, struct tagTetisPlay* pMyTetis)
{

	tagTetisPlay tmpMyTetis = *pMyTetis;

	switch (pMyTetis->CurBlockType)
	{
	case SQUAREBLOCKSQUARE:
	{
		// 不处理 正方形
	}break;


	case LEFTSHORTBLOCK_LEFT:
	{
		tmpMyTetis.CurBlockCoord[2].y -= 2;
		tmpMyTetis.CurBlockCoord[3].x -= 2;
		tmpMyTetis.CurBlockType = LEFTSHORTBLOCK_UP;

	}break;
	case LEFTSHORTBLOCK_UP:
	{
		tmpMyTetis.CurBlockCoord[2].y += 2;
		tmpMyTetis.CurBlockCoord[3].x += 2;
		tmpMyTetis.CurBlockType = LEFTSHORTBLOCK_LEFT;
	}break;



	case RIGHTSHORTBLOCK_LEFT:
	{
		tmpMyTetis.CurBlockCoord[2].x += 2;
		tmpMyTetis.CurBlockCoord[3].y -= 2;
		tmpMyTetis.CurBlockType = RIGHTSHORTBLOCK_UP;

	}break;
	case RIGHTSHORTBLOCK_UP:
	{
		tmpMyTetis.CurBlockCoord[2].x -= 2;
		tmpMyTetis.CurBlockCoord[3].y += 2;
		tmpMyTetis.CurBlockType = RIGHTSHORTBLOCK_LEFT;

	}break;


	case LONGBLOCK_COL:
	{
		tmpMyTetis.CurBlockCoord[1].x += 1;
		tmpMyTetis.CurBlockCoord[1].y += 1;
		tmpMyTetis.CurBlockCoord[2].x += 2;
		tmpMyTetis.CurBlockCoord[2].y += 2;
		tmpMyTetis.CurBlockCoord[3].x += 3;
		tmpMyTetis.CurBlockCoord[3].y += 3;
		tmpMyTetis.CurBlockType = LONGBLOCK_ROW;
	}break;
	case LONGBLOCK_ROW:
	{
		tmpMyTetis.CurBlockCoord[1].x -= 1;
		tmpMyTetis.CurBlockCoord[1].y -= 1;
		tmpMyTetis.CurBlockCoord[2].x -= 2;
		tmpMyTetis.CurBlockCoord[2].y -= 2;
		tmpMyTetis.CurBlockCoord[3].x -= 3;
		tmpMyTetis.CurBlockCoord[3].y -= 3;
		tmpMyTetis.CurBlockType = LONGBLOCK_COL;
	}break;

	//tmpMyTetis.CurBlockCoord[0].x += 1;
	//tmpMyTetis.CurBlockCoord[0].y += 1;
	//tmpMyTetis.CurBlockCoord[1].x += 1;
	//tmpMyTetis.CurBlockCoord[1].y += 1;

	//tmpMyTetis.CurBlockCoord[2].x += 1;
	//tmpMyTetis.CurBlockCoord[2].y += 1;
	//tmpMyTetis.CurBlockCoord[3].x += 1;
	//tmpMyTetis.CurBlockCoord[3].y += 1;

	case LEFTLONGBLOCK_LEFT:
	{
		tmpMyTetis.CurBlockCoord[0].y -= 1;
		tmpMyTetis.CurBlockCoord[1].x -= 1;
		tmpMyTetis.CurBlockCoord[2].y += 1;
		tmpMyTetis.CurBlockCoord[3].x += 1;
		tmpMyTetis.CurBlockCoord[3].y += 2;

		tmpMyTetis.CurBlockType = LEFTLONGBLOCK_UP;

	}break;
	case LEFTLONGBLOCK_UP:
	{
		tmpMyTetis.CurBlockCoord[0].x += 2;
		tmpMyTetis.CurBlockCoord[0].y -= 1;

		tmpMyTetis.CurBlockCoord[1].x += 1;
		tmpMyTetis.CurBlockCoord[1].y -= 2;
		tmpMyTetis.CurBlockCoord[2].y -= 1;
		tmpMyTetis.CurBlockCoord[3].x -= 1;

		tmpMyTetis.CurBlockType = LEFTLONGBLOCK_RIGHT;

	}break;
	case LEFTLONGBLOCK_RIGHT:
	{
		tmpMyTetis.CurBlockCoord[0].y += 2;
		tmpMyTetis.CurBlockCoord[1].x += 1;
		tmpMyTetis.CurBlockCoord[1].y += 1;
		tmpMyTetis.CurBlockCoord[3].x -= 1;
		tmpMyTetis.CurBlockCoord[3].y -= 1;

		tmpMyTetis.CurBlockType = LEFTLONGBLOCK_DOWN;
	}break;
	case LEFTLONGBLOCK_DOWN:
	{
		tmpMyTetis.CurBlockCoord[0].x -= 2;
		tmpMyTetis.CurBlockCoord[1].x -= 1;
		tmpMyTetis.CurBlockCoord[1].y += 1;
		tmpMyTetis.CurBlockCoord[3].x += 1;
		tmpMyTetis.CurBlockCoord[3].y -= 1;

		tmpMyTetis.CurBlockType = LEFTLONGBLOCK_LEFT;
	}break;


	case RIGHTLONGBLOCK_RIGHT:
	{
		tmpMyTetis.CurBlockCoord[2].x += 2;
		tmpMyTetis.CurBlockCoord[2].y += 1;
		tmpMyTetis.CurBlockCoord[3].x += 2;
		tmpMyTetis.CurBlockCoord[3].y += 1;
		tmpMyTetis.CurBlockType = RIGHTLONGBLOCK_UP;

	}break;
	case RIGHTLONGBLOCK_UP:
	{
		tmpMyTetis.CurBlockCoord[0].x += 1;
		tmpMyTetis.CurBlockCoord[0].y -= 1;
		tmpMyTetis.CurBlockCoord[2].x -= 1;
		tmpMyTetis.CurBlockCoord[2].y -= 2;
		tmpMyTetis.CurBlockCoord[3].x -= 2;
		tmpMyTetis.CurBlockCoord[3].y -= 1;
		tmpMyTetis.CurBlockType = RIGHTLONGBLOCK_LEFT;
	}break;
	case RIGHTLONGBLOCK_LEFT:
	{
		tmpMyTetis.CurBlockCoord[1].x += 1;
		tmpMyTetis.CurBlockCoord[1].y -= 1;
		tmpMyTetis.CurBlockCoord[2].x -= 1;
		tmpMyTetis.CurBlockCoord[2].y += 1;
		tmpMyTetis.CurBlockCoord[3].y += 2;
		tmpMyTetis.CurBlockType = RIGHTLONGBLOCK_DOWN;
	}break;
	case RIGHTLONGBLOCK_DOWN:
	{
		tmpMyTetis.CurBlockCoord[0].x -= 1;
		tmpMyTetis.CurBlockCoord[0].y += 1;
		tmpMyTetis.CurBlockCoord[1].x -= 1;
		tmpMyTetis.CurBlockCoord[1].y += 1;
		tmpMyTetis.CurBlockCoord[3].y -= 2;
		tmpMyTetis.CurBlockType = RIGHTLONGBLOCK_RIGHT;
	}break;


	case UNIVEBLOCK_UP:
	{
		tmpMyTetis.CurBlockCoord[2].y -= 1;
		tmpMyTetis.CurBlockCoord[3].x += 1;
		tmpMyTetis.CurBlockCoord[3].y -= 2;

		tmpMyTetis.CurBlockType = UNIVEBLOCK_RIGHT;
	}break;
	case UNIVEBLOCK_RIGHT:
	{
		tmpMyTetis.CurBlockCoord[3].x -= 1;
		tmpMyTetis.CurBlockCoord[3].y += 1;
		tmpMyTetis.CurBlockType = UNIVEBLOCK_DOWN;
	}break;
	case UNIVEBLOCK_DOWN:
	{
		tmpMyTetis.CurBlockCoord[2].x -= 1;
		tmpMyTetis.CurBlockCoord[2].y -= 1;
	
		tmpMyTetis.CurBlockType = UNIVEBLOCK_LEFT;
	}break;
	case UNIVEBLOCK_LEFT:
	{
		tmpMyTetis.CurBlockCoord[2].x += 1;
		tmpMyTetis.CurBlockCoord[2].y += 2;

		tmpMyTetis.CurBlockCoord[3].y += 1;
		tmpMyTetis.CurBlockType = UNIVEBLOCK_UP;
	}break;
	default:
		break;
	}

	if (IsCollisionAndOutMap(arryMap, &tmpMyTetis) == NOT)
	{
		*pMyTetis = tmpMyTetis;
		return YES;
	}

	return NOT;
}

int OnButtom(int* arryMap, struct tagTetisPlay* pMyTetis)
{
	NoShowCurBlock(arryMap, pMyTetis);

	int isOnButtom = NOT;
	int isInBlock = NOT;
	int isTapBlock = NOT;

	int minY = pMyTetis->CurBlockCoord[0].y;

	for (int i = 0; i < BLOCKLENGTH; i++)
	{
		if (pMyTetis->CurBlockCoord[i].y == MAPROW - 1)
		{
			isOnButtom = YES;
			break;
		}
		
		if (GetMapPointer(arryMap, pMyTetis->CurBlockCoord[i].x, pMyTetis->CurBlockCoord[i].y + 1) == 1)
		{
			isOnButtom = YES;
			break;
		}
	}

	ShowCurBlock(arryMap, pMyTetis);
	//if (isOnButtom)
	//{
	//	isTapBlock = TapBlox(arryMap, pMyTetis);
	//}
	return isOnButtom;
}

int IsInMapCol(int nCol)
{
	if (nCol < 0 && nCol >= MAPCOL)
	{
		return YES;
	}
	return NOT;
}

void NoShowCurBlock(int* arryMap, tagTetisPlay* pMyTetis)
{
	// 取消原来的标记
	for (int i = 0; i < BLOCKLENGTH; i++)
	{
		if (pMyTetis->CurBlockCoord[i].x < 0 || pMyTetis->CurBlockCoord[i].x >= MAPCOL || pMyTetis->CurBlockCoord[i].y < 0 || pMyTetis->CurBlockCoord[i].y >= MAPROW)
		{
			continue;
		}
		arryMap[pMyTetis->CurBlockCoord[i].y * MAPCOL + pMyTetis->CurBlockCoord[i].x] = 0;
	}
}

void ShowCurBlock(int* arryMap, tagTetisPlay* pMyTetis)
{
	// 取消原来的标记
	for (int i = 0; i < BLOCKLENGTH; i++)
	{
		if (pMyTetis->CurBlockCoord[i].x < 0 || pMyTetis->CurBlockCoord[i].x >= MAPCOL || pMyTetis->CurBlockCoord[i].y < 0 || pMyTetis->CurBlockCoord[i].y >= MAPROW)
		{
			continue;
		}
		arryMap[pMyTetis->CurBlockCoord[i].y * MAPCOL + pMyTetis->CurBlockCoord[i].x] = 1;
	}
}

int IsCollisionAndOutMap(int* arryMap, tagTetisPlay* pMyTetis)
{

	for (int i = 0; i < BLOCKLENGTH; i++)
	{
		if (pMyTetis->CurBlockCoord[i].x  < 0 || pMyTetis->CurBlockCoord[i].x >= MAPCOL || pMyTetis->CurBlockCoord[i].y >= MAPROW)
		{
			return YES;
		}

		if (GetMapPointer(arryMap, pMyTetis->CurBlockCoord[i].x, pMyTetis->CurBlockCoord[i].y) == 1)
		{
			return YES;
		}
	}


	return NOT;
}

int IsGameOver(int* arryMap, tagTetisPlay* pMyTetis)
{
	for (int i = 0; i < BLOCKLENGTH; i++)
	{
		if (pMyTetis->CurBlockCoord[i].y < 0)
		{
			return YES;
		}
	}

	return NOT;
}