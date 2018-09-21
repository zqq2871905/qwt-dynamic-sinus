/* SinData.c */
#include "SinData.h"
#define PI 3.1415926
#define BUFFER_SIZE 1024

int g_Buffer[BUFFER_SIZE];
int g_BufferIndex;
int g_AxisX;
int g_AxisY;
int g_AxisIndex;
int g_Amplitude = 25;
int g_Cycle = 6;
int g_SinOffset = 135;

/*
Function Name   :    SetAmplitude
Description :        设置振幅
Input Parameters:    Amplitude :振幅值
*/
void SetAmplitude(int Amplitude)
{
	g_Amplitude = Amplitude;
}

/*
Function Name   :    SetCycle
Description :        设置周期
Input Parameters:    Cycle :周期
*/
void SetCycle(int Cycle)
{
	g_Cycle = Cycle;
}

/*
Function Name   :    SetSinOffset
Description :        设置偏移量
Input Parameters:    SinOffset :y轴的偏移量
*/
void SetSinOffset(int SinOffset)
{
	g_SinOffset = SinOffset;
}


/*
Function Name:   RecvData
Description  :   设置完参数后，用来重新生成数据，更新Sin图像
*/
void UpdateSinData(int AxisX[], int AxisY[])
{

	int m;
	for (m = 0; m <g_AxisIndex; m++)
	{
		AxisX[m] = m;
		AxisY[m] = g_Amplitude * sin(PI / g_Cycle * (AxisX[m])) + g_SinOffset;
	}
}


/*
Function Name:   void DrawSin
Description  :   产生sin图像的坐标
*/
void DrawSin()
{
	g_AxisY = g_Amplitude * sin(PI / g_Cycle *  g_AxisIndex) + g_SinOffset;
	g_AxisX = g_AxisIndex;
	g_AxisIndex++;
}


/*
Function Name   :    GetSinData
Description     :    获取sin图像的坐标，供外部调用
Input Parameters：   AxisX ：x轴坐标   AxisY：y轴坐标
Return Value    ：   1 ：成功获取
0 ：获取失败(接收数据的缓冲区没满)
-1：获取失败
*/
int GetSinData(int *AxisX, int *AxisY)
{
	if (g_BufferIndex == BUFFER_SIZE)
	{
		DrawSin();
		*AxisX = g_AxisX;
		*AxisY = g_AxisY;
		static int s_Tick = 0;
		s_Tick++;
		g_BufferIndex = 0;
		return 1;
	}

	return 0;
}

/*
Function Name:   RecvData
Description  :   模仿接收1K的数据
*/
void RecvData()
{
	while (1)
	{
		if (g_BufferIndex == BUFFER_SIZE)
			return;
		g_Buffer[g_BufferIndex] = g_BufferIndex;
		g_BufferIndex++;

	}
}

void *RecvDataPthread(void *arg)
{
	while (1)
	{
		RecvData();
	}
}

/*
Function Name   :    StartSin
Description     :    启动线程，不停地获取数据
*/

void StartSin()
{
	pthread_t pid;
	pthread_create(&pid, NULL, RecvDataPthread, NULL);
}