#pragma once
#include"defines.h"
#include<vector>
using namespace std;

class Machine
{
private:
	
public:
	int V[k][machineNum];//�����׶β�ͬ�������ٶ�
	int PW[k][machineNum];//���������ڲ�ͬ�׶��µĹ�������
	int avt[k][machineNum];//��k�׶Σ�ÿ�������ĵ�ǰ����ʱ��
	Machine();
	void init();
	~Machine();
};

