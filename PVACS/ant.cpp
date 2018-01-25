#include "stdafx.h"
#include "ant.h"
#include<random>
#include<iostream>
#include"defines.h"
using namespace std;
extern int info[100][100];
extern int pos[100];
extern float phmk[100][100];//mk��Ӧ����Ϣ�ؾ���
extern float phepc[100][100];//epc��Ӧ����Ϣ�ؾ���
extern vector<batch> B;
extern int bNum;

void ant::generateV()
{
	Vmk = rand() % 100 / 100.0;
	Vepc = 1 - Vmk;
	sol.clear();
}

void ant::createBatchSeq()
{
	tempB = B;
	vector<float> pb;// ÿֻ����ѡ���һ�����ĸ���
	int sum = 0;
	for (int i = 0; i < bNum; i++)
		sum += (bNum - pos[i] + 1)*(bNum - pos[i] + 1);

	for (int i = 0; i < bNum; i++)
		pb.push_back((float)(bNum - pos[i] + 1)*(bNum - pos[i] + 1) / sum);

	float m = 0;
	float r = rand() % 100 / 100.0;
	
	// ���ո���ѡ���һ��
	for (int i = 0; i < bNum; i++)
	{
		m += pb[i];
		if (r < m) {
			sol.push_back(i);
			tempB[i].flag = 0;//��ʾ������Ѿ�������
			break;
		}
	}

	// ����ѡ�����Ľ�
	for (int i = 1; i < bNum; i++)// ����bNum-1������Ҫ����
	{
		float q = rand() % 100 / 100.0;
		float max = -999999.0;
		int select = -1;//ѡ������ı��
		if (q <= q0)
		{
			for (int j = 0; j < tempB.size(); j++)
			{
				if (tempB[j].flag == 1)// ��δ����ļ�������ѡ
				{
					float temp = pow((pow(Vmk, alpha)*phmk[sol.back()][j] + pow(Vepc, alpha)*phepc[sol.back()][j]), alpha)*pow(info[sol.back()][j], beta);
					if ( temp > max)
					{
						max = temp;
						select = j;
					}
				}
			}
			//��ʱ�Ѿ��ҳ�������
			sol.push_back(select);//��select�Ž�ȥ
			tempB[select].flag = 0;//��ʶ��ֵΪ0
			
		}
		//q>q0ʱ,H
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
	cout << id<<"���ϵ�����Ϊ��";
	for (int i = 0; i < sol.size(); i++)
	{
		cout << sol[i] << "  ";
	}
	cout << endl;
	for (int i = 0; i < sol.size(); i++)
	{
		cout <<i<<"   "<< tempB[sol[i]].BId << "  "<<tempB[sol[i]].JNum<<"  "<<tempB[sol[i]].BP[0]<<endl;
	}


}

// LS�㷨
void ant::LS()
{
	vector<int> SOL;//���ÿһ�׶ε������У�����ĸ���ǰ��ģ�
	SOL = sol;
	//����ÿ���׶�
	for (int p = 0; p < k; p++)
	{
		//����ÿһ����
		for (int h = 0; h < B.size(); h++)
		{
			float min=9999999;//����ʽ�ӵ���Сֵ
			int selectMachine;//����ѡ��Ļ���
			float max1 = -9999;
			float max2 = -9999;
			int CT;//K-1�׶Σ�����һ�׶ε����ʱ��

			//����ǵ�һ�׶Σ�����һ�׶ε����ʱ��Ϊ0
			if (p = 0)
				CT = 0;
			else
				CT = B[SOL[h]].BC[p-1];//��һ�׶ε����ʱ��
			for (int i = 0; i < machineNum; i++)//��į����
			{
				int temp1;
				temp1 = max(CT, M->avt[p][i]) + B[SOL[h]].BP[p] - CT;
				if (temp1 > max1)
					max1 = temp1;

				float temp2 = getEPC(max(CT, M->avt[p][i]), B[SOL[h]].BP[p], p, i);
				if (temp2 > max2)
					max2 = temp2;
			}
		
			for (int i = 0; i < machineNum; i++)
			{
				float temp = Vmk * (max(CT, M->avt[p][i]) + B[SOL[h]].BP[p] - CT) / max1 + Vepc * getEPC(max(CT, M->avt[p][i]), B[SOL[h]].BP[p], p, i) / max2;
				if (temp < min)
				{
					min = temp;
					selectMachine = i;
				}
			}

			//ѡ���˻���selectMachine��
			tempB[SOL[h]].BC[p] = max(CT, M->avt[p][selectMachine]) + tempB[SOL[h]].BP[p];//�������ڴ˽׶ε����ʱ��
			M->avt[p][selectMachine] = tempB[SOL[h]].BC[p];//���»����Ŀ���ʱ��
		}
		//��ȡ��һ���׶ε������У�������һ�׶ε����ʱ������
		vector<batch> tempBB=tempB;
		sort(tempBB.begin(), tempBB.end(), cmp3);
		SOL.clear();
		for (int j = 0; j < tempBB.size(); j++)
			SOL.push_back(tempBB[j].BId);
	}
	
}
ant::~ant()
{

}
