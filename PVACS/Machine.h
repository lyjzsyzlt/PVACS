#pragma once
#include"defines.h"
#include<vector>
using namespace std;

class Machine
{
private:
	
public:
	int V[k][machineNum];//各个阶段不同机器的速度
	int PW[k][machineNum];//各个机器在不同阶段下的工作功率
	int avt[k][machineNum];//在k阶段，每个机器的当前可用时间
	Machine();
	void init();
	~Machine();
};

