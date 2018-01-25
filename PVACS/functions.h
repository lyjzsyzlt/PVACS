#pragma once
#ifndef functions_H
#define functions_H

#include"structs.h"
#include<algorithm>
#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
int max(int a, int b);


// 初始化工件的信息
void initJob(vector<job> &J);


bool cmp(const job &J1, const job &J2);


bool cmp2(const batch &b1, const batch &b2);
bool cmp3(const batch &b1, const batch &b2);
// 初始化批的基本信息
void initBatch(batch &B, int id);

// 计算各个批的名义加工时间
void getPbk(vector<job> J, vector<batch> &B);

// 分批
void BFLPT(vector<job> J/*, vector<batch> &B*/);


// 输出各个批包含的工件
void displayBatch(/*vector<batch> B*/);//不能是const vector<batch> B

// 计算各个批的倾斜度,获取启发式信息矩阵

/*int info[100][100];
int pos[100];*/
void computeSIb(/*vector<batch> &B*/);

/*float phmk[100][100];//mk对应的信息素矩阵
float phepc[100][100];//epc对应的信息素矩阵*/

// 初始化信息素矩阵
void initPh();

#endif // !functions_H
