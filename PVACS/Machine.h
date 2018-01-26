#pragma once
#include"defines.h"
#include"structs.h"
#include<vector>
#include<list>

using namespace std;

class Machine
{
private:
	
public:
	int V;//各个阶段不同机器的速度
	int PW;//各个机器在不同阶段下的工作功率
	int avt;//在k阶段，每个机器的当前可用时间
	list<batch> List;//记录机器上加工的批
	Machine();
	void init(float pw,float v);
	~Machine();
};

