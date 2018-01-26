// PVACS.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"functions.h"
#include"ant.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<random>
#include<time.h>
using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	/*srand((unsigned)time(NULL));
	vector<job> J;
	
	initJob(J);
	BFLPT(J);
	displayBatch();
	
	int info[100][100];//启发式信息
	int pos[100];//根据倾斜度算出的批的位置
	computeSIb();
	initPh();
	int t = Tmax;
	ant* Ant = new ant[antNum];*/
	/*while (t--)
	{
		cout << "第" << (100-t) << "次迭代：" << endl;
		for (int i = 0; i <antNum; i++)
		{
			Ant[i].id = i;
			Ant[i].generateV();
			Ant[i].createBatchSeq();
		}
		cout << "------------------------------------------" << endl;
	}*/
	
	ant A ;
	A.id = 1;
	A.generateV();
	//A.createBatchSeq();
	A.sol = { 0,1,2,3,4 };
	ifstream in;
	in.open("batch.txt", ios::in | ios::binary);
	
	for (int i = 0; i < 5; i++)
	{
		batch b;
		//cout << "输入编号：" ;
		in >> b.BId;
		//cout << "输入第一阶段时间：";
		int x;
		in >> x;
		b.BP.push_back(x);
		//cout << "输入第二阶段时间:" ;
		in >> x;
		b.BP.push_back(x);
		A.tempB.push_back(b);
	}

	initM();
	A.LS();
    return 0;
}

