#pragma once
#include"functions.h"
#include"structs.h"
#include"Machine.h"
class ant
{
private:
	// 用户偏好向量
	float Vmk;
	float Vepc;
	
	
	float Cmax;//记录最大makespan
	float EPC;//记录最终的EPC

	
public:
	int id;
	vector<int> sol;//存放解
	vector<batch> tempB;
	ant()
	{
		
	};
	void generateV();//产生偏好向量的两个值
	void createBatchSeq();// 构造解（批序列）
	void LS();// LS算法
	float getEPC1(float t, float detaT,int k,int l);// 计算EPC，t为下界，detaT为整个过程的时间,机器为第k阶段的第l台机器
	float getEPC2(float t, float detaT);//计算机器的待机电费
	~ant();
};

