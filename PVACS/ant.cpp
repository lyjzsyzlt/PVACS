#include "stdafx.h"
#include "ant.h"
#include<random>
#include<iostream>
#include"defines.h"
using namespace std;
extern int info[100][100];
extern int pos[100];
extern float phmk[100][100];//mk对应的信息素矩阵
extern float phepc[100][100];//epc对应的信息素矩阵
extern vector<batch> B;
extern int bNum;

void ant::generateV()
{
	Vmk = rand() % 100 / 100.0;
	Vepc = 1 - Vmk;
}

void ant::createBatchSeq()
{
	vector<batch> tempB = B;
	vector<float> pb;// 每只蚂蚁选择第一个批的概率
	int sum = 0;
	for (int i = 0; i < bNum; i++)
		sum += (bNum - pos[i] + 1)*(bNum - pos[i] + 1);

	for (int i = 0; i < bNum; i++)
		pb.push_back((float)(bNum - pos[i] + 1)*(bNum - pos[i] + 1) / sum);

	float m = 0;
	float r = rand() % 100 / 100.0;
	vector<int> sol;//存放解
	// 按照概率选择第一批
	for (int i = 0; i < bNum; i++)
	{
		m += pb[i];
		if (r < m) {
			sol.push_back(i);
			tempB[i].flag = 0;//表示这个批已经加入了
			break;
		}
	}

	// 继续选择后面的解
	for (int i = 1; i < bNum; i++)// 还有bNum-1个批需要加入
	{
		float q = rand() % 100 / 100.0;
		float max = -999999.0;
		int select = -1;//选择的批的编号
		if (q <= q0)
		{
			for (int j = 0; j < tempB.size(); j++)
			{
				if (tempB[j].flag == 1)// 从未加入的集合里面选
				{
					float temp = pow((pow(Vmk, alpha)*phmk[sol.back()][j] + pow(Vepc, alpha)*phepc[sol.back()][j]), alpha)*pow(info[sol.back()][j], beta);
					if ( temp > max)
					{
						max = temp;
						select = j;
					}
				}
			}
			//此时已经找出最大的了
			sol.push_back(select);//把select放进去
			tempB[select].flag = 0;//标识赋值为0
			
		}
		//q>q0时,H
		else
		{
			float sum = 0;
			for (int l = 0; l < tempB.size(); l++)
			{
				if(tempB[l].flag==1)
					sum += pow((pow(Vmk, alpha)*phmk[sol.back()][l] + pow(Vepc, alpha)*phepc[sol.back()][l]), alpha)*pow(info[sol.back()][l], beta);
			}
			float P[100];
			for (int p = 0; p < tempB.size(); p++)
			{
				if (tempB[p].flag == 1)
				{
					P[p] = pow((pow(Vmk, alpha)*phmk[sol.back()][p] + pow(Vepc, alpha)*phepc[sol.back()][p]), alpha)*pow(info[sol.back()][p], beta) / sum;
				}
				else
				{
					P[p] = 0;
				}
			}

			float r = rand() % 100 / 100.0;
			float temp = 0;
			for (int t = 0; t < tempB.size(); t++)
			{
				temp += P[t];
				if (r < temp)
				{
					sol.push_back(t);
					tempB[t].flag = 0;
				
					break;
				}
			}
		}
	}
	cout << id<<"蚂蚁的序列为：";
	for (int i = 0; i < sol.size(); i++)
	{
		cout << sol[i] << "  ";
	}
	cout << endl;
	/*for (int i = 0; i < sol.size(); i++)
	{
		cout <<i<<"   "<< tempB[sol[i]].BId << "  "<<tempB[sol[i]].JNum<<"  "<<tempB[sol[i]].BP[0]<<endl;
	}*/


}
ant::~ant()
{
}
