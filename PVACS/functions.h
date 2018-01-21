#pragma once
#ifndef functions_H
#define functions_H

#include"structs.h"
#include<algorithm>
#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
int max(int a, int b)
{
	return a > b ? a : b;
}

// ��ʼ����������Ϣ
void initJob(vector<job> &J)
{
	// ��job.txt�ļ��ж�ȡ�����ı�ţ���С�������׶ε�����ӹ�ʱ��
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
	return J1.JobPT[0] > J2.JobPT[0];//���յ�һ�׶εļӹ�ʱ������
}

// ��ʼ�����Ļ�����Ϣ
void initBatch(batch &B,int id)
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

// ���������������ӹ�ʱ��
void getPbk(vector<job> J,vector<batch> &B)
{
	for (int i = 0; i < B.size(); i++) //��i����
	{
		for (int p = 0; p < k; p++)// ��p���׶�
		{
			int maxPT = -999999;
			for (int j = 0; j < B[i].JNum; j++)// ��j������
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

// ����
void BFLPT(vector<job> J,vector<batch> &B)
{
	sort(J.begin(),J.end(), cmp);//�Թ������ռӹ�ʱ��ǵ���˳������

	vector<job>::iterator it2 = J.begin();//���������ĵ�����
	int initBid = 0;//���ĳ�ʼ���

	for (it2; it2 != J.end(); it2++)//�������еĹ���
	{
		int min = 9999999;//��С�ĵ�ʣ��ռ�
		int minBid = -1;//��Ӧ�������
		vector<batch>::iterator it = B.begin();//�������ĵ�����
		for (it; it != B.end(); it++)//Ϊÿ����������һ�ε�ǰ��������
		{
			if ((*it).freeSpace >= (*it2).JobSize)//��ǰ��������㹻�����������
			{
				if ((*it).freeSpace - (*it2).JobSize < min)//�жϷ���֮���Ƿ�ʹ�����������������������ʣ��ռ���С
				{
					min = (*it).freeSpace - (*it2).JobSize;
					minBid = (*it).BId;
				}
			}
		}
		//���½���һ����
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
		// ������������������������
		else
		{
			B[minBid].freeSpace -=(*it2).JobSize;
			B[minBid].JNum++;
			B[minBid].BJob.push_back((*it2));
		}
	}
	getPbk(J, B);//��ȫ�����������׶ε�����ӹ�ʱ��
}

// ��������������Ĺ���
void displayBatch(vector<batch> B)//������const vector<batch> B
{
	int i = 1;//�����±�
	vector<batch>::iterator it = B.begin();
	for (; it != B.end(); it++) {
		cout << "��" << i << "�����ı�ţ�" << (*it).BId << endl;;
		cout << "��" << i << "����������������" << (*it).JNum << endl;
		cout << "��" << i << "�����������Ĺ���Ϊ(��ţ�:";

		for (int p = 0; p < (*it).JNum; p++) {
			cout << (*it).BJob[p].JobId << "  ";
		}
		cout << endl;

		for (int j = 0; j < k; j++) {//k���׶�
			cout << "    ��" << j+1<< "�׶ε�����ӹ�ʱ��:" << (*it).BP[j] << endl;
			cout << "    ��" << j+1 << "�׶ε����ڻ�����:" << (*it).MId[j] << endl;
		}
		i++;
	}
}
#endif // !functions_H
