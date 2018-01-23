#include"stdafx.h"
#include"functions.h"
#include"structs.h"
#include<algorithm>
#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
vector<batch> B;
int bNum;
int max(int a, int b)
{
	return a > b ? a : b;
}

// 初始化工件的信息
void initJob(vector<job> &J)
{
	// 从job.txt文件中读取工件的编号，大小，各个阶段的名义加工时间
	ifstream in;
	in.open("job.txt", ios::in | ios::binary);
	for (int i = 0; i < JobNum; i++)
	{
		job tempj;
		batch b;
		in >> tempj.JobId;
		in >> tempj.JobSize;
		for (int j = 0; j < k; j++) {
			int x;
			in >> x;
			tempj.JobPT.push_back(x);
		}
		J.push_back(tempj);
	}
}

bool cmp(const job &J1, const job &J2)
{
	return J1.JobPT[0] > J2.JobPT[0];//按照第一阶段的加工时间排序
}

bool cmp2(const batch &b1, const batch &b2)
{
	return b1.SI > b2.SI;//按照批的倾斜度降序排列
}
// 初始化批的基本信息
void initBatch(batch &B, int id)
{
	for (int i = 0; i < k; i++)
	{
		B.BId = id;
		B.BP.push_back(-1);
		B.freeSpace = C;
		B.JNum = 0;
		B.MId.push_back(-1);
	}
}

// 计算各个批的名义加工时间
void getPbk(vector<job> J, vector<batch> &B)
{
	for (int i = 0; i < B.size(); i++) //第i个批
	{
		for (int p = 0; p < k; p++)// 第p个阶段
		{
			int maxPT = -999999;
			for (int j = 0; j < B[i].JNum; j++)// 第j个工件
			{
				if (B[i].BJob[j].JobPT[p] > maxPT)
				{
					maxPT = B[i].BJob[j].JobPT[p];
				}
			}
			B[i].BP[p] = maxPT;
		}
	}
}

// 分批
void BFLPT(vector<job> J/*, vector<batch> &B*/)
{
	sort(J.begin(), J.end(), cmp);//对工件按照加工时间非递增顺序排序

	vector<job>::iterator it2 = J.begin();//工件向量的迭代器
	int initBid = 0;//批的初始编号

	for (it2; it2 != J.end(); it2++)//遍历所有的工件
	{
		int min = 9999999;//最小的的剩余空间
		int minBid = -1;//对应的批编号
		vector<batch>::iterator it = B.begin();//批向量的迭代器
		for (it; it != B.end(); it++)//为每个工件遍历一次当前的批集合
		{
			if ((*it).freeSpace >= (*it2).JobSize)//当前的这个批足够放下这个工件
			{
				if ((*it).freeSpace - (*it2).JobSize < min)//判断放入之后，是否使得这个批在整个集合中满足剩余空间最小
				{
					min = (*it).freeSpace - (*it2).JobSize;
					minBid = (*it).BId;
				}
			}
		}
		//重新建立一个批
		if (minBid == -1)
		{
			batch tempB;
			initBatch(tempB, initBid);
			tempB.freeSpace -= (*it2).JobSize;
			tempB.JNum++;
			tempB.BJob.push_back((*it2));
			initBid++;
			B.push_back(tempB);
		}
		// 将这个工件放入符合条件的批
		else
		{
			B[minBid].freeSpace -= (*it2).JobSize;
			B[minBid].JNum++;
			B[minBid].BJob.push_back((*it2));
		}
	}
	bNum = B.size();
	getPbk(J, B);//补全各个批各个阶段的名义加工时间
}

// 输出各个批包含的工件
void displayBatch(/*vector<batch> B*/)//不能是const vector<batch> B
{
	int i = 1;//批的下标
	vector<batch>::iterator it = B.begin();
	for (; it != B.end(); it++) {
		cout << "第" << i << "个批的编号：" << (*it).BId << endl;;
		cout << "第" << i << "个批所含工件数：" << (*it).JNum << endl;
		cout << "第" << i << "个批所包含的工件为(编号）:";

		for (int p = 0; p < (*it).JNum; p++) {
			cout << (*it).BJob[p].JobId << "  ";
		}
		cout << endl;

		for (int j = 0; j < k; j++) {//k个阶段
			cout << "    第" << j + 1 << "阶段的名义加工时间:" << (*it).BP[j] << endl;
			cout << "    第" << j + 1 << "阶段的所在机器号:" << (*it).MId[j] << endl;
		}
		i++;
	}
}

// 计算各个批的倾斜度,获取启发式信息矩阵

int info[100][100];
int pos[100];
void computeSIb(/*vector<batch> &B*/)
{
	vector<batch> tempB = B;

	for (int i = 0; i < B.size(); i++)
	{
		float sum = 0;
		for (int j = 0; j < k; j++)
		{
			sum += ((k - 2 * j + 1) / 2.0*B[i].BP[j]);
		}
		B[i].SI = (-1)*sum;
		tempB[i].SI = (-1)*sum;
	}
	sort(tempB.begin(), tempB.end(), cmp2);

	// 计算pos
	for (int i = 0; i < B.size(); i++)
	{
		for (int j = 0; j < B.size(); j++)
		{
			if (tempB[j].BId == B[i].BId)
			{
				pos[i] = j;
				break;
			}
		}
	}

	// 计算启发式信息矩阵
	for (int i = 0; i < B.size(); i++)
	{
		for (int j = 0; j < B.size(); j++)
		{
			info[i][j] = B.size() - abs(pos[i] - pos[j]);
		}
	}
}

float phmk[100][100];//mk对应的信息素矩阵
float phepc[100][100];//epc对应的信息素矩阵

					  // 初始化信息素矩阵
void initPh()
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			phmk[i][j] = 0.5;
			phepc[i][j] = 0.5;
		}
	}
}
