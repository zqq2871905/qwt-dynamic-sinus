#pragma once
/* SinData.h */
#ifndef SINDATA_H
#define SINDATA_H

#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>

void StartSin();             //启动线程
int  GetSinData(int *AxisX, int *AxisY);   //获取Sin坐标点
void SetAmplitude(int Amplitude);   // 设置振幅
void SetCycle(int Cycle);           // 设置周期
void SetSinOffset(int SinOffset);  // 设置Y轴偏移量
void UpdateSinData(int AxisX[], int AxisY[]); // 更新Sin数据

#endif
