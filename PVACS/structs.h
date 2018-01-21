#pragma once
#include"defines.h"
#include<vector>
using namespace std;
// 工件
struct job
{
	int JobId;//工件编号
	int JobSize;//工件尺寸
	vector<int> JobPT;//工件再不同阶段的处理时间
};

// 批
struct batch
{
	int BId;//批编号
	//int BSize;//批尺寸
	vector<int> BP;//批再不同阶段名义处理时间
	//int BR;//批到达时间
	//vector<int> BS;//批再不同阶段开始加工时间
	//vector<int> BC;//批再不同阶段完工时间                                         
	vector<int> MId;//该批不同阶段所在机器号
	int JNum;//批中工件个数
	//vector<int> jobid;//批中工件编号
	int freeSpace;//记录批的剩余空间
	vector<job> BJob;//批里面存放的工件
};

// 机器
struct machine
{
	int MId;//机器编号
	int MSize;//机器尺寸
	int MP;//当前机器可用时间
	int MEpc;//机器成本
	int BNum;//机器中批数目
	int MBId[JobNum + 1];//机器中批号，0位空出
};