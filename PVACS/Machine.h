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
	int V;//�����׶β�ͬ�������ٶ�
	int PW;//���������ڲ�ͬ�׶��µĹ�������
	int avt;//��k�׶Σ�ÿ�������ĵ�ǰ����ʱ��
	list<batch> List;//��¼�����ϼӹ�����
	Machine();
	void init(float pw,float v);
	~Machine();
};

