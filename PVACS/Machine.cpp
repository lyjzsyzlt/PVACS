#include "stdafx.h"
#include "Machine.h"


Machine::Machine()
{
	init();
}

void Machine::init()
{
	V[0][0] = 2;//第一阶段第一台机器的速度
	V[0][1] = 1;//第一阶段第二台机器的速度
	V[0][2] = 2;//第一阶段第三台机器的速度
	V[1][0] = 2;//第二阶段第一台机器的速度
	V[1][1] = 1;
	V[1][2] = 1;

	PW[0][0] = 8;//第一阶段第一台机器的功率
	PW[0][1] = 6;//第一阶段第二台机器的功率
	PW[0][2] = 10;//第一阶段第三台机器的功率
	PW[1][0] = 12;//第二阶段第一台机器的功率
	PW[1][1]=3;//第二阶段第二台机器的功率
	PW[1][2] = 4;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < machineNum; j++)
		{
			avt[i][j] = 0;
		}
	}
	
}


Machine::~Machine()
{
}
