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
	vector<int> sol;//存放解
	vector<batch> tempB;
	Machine *M;
	//int bNum;// 批的数量
	/*static int pos[100];// 位置
	static int info[100][100];// 启发式信息*/
	
public:
	int id;
	ant()
	{
		M = new Machine();
	};
	void generateV();//产生偏好向量的两个值
	void createBatchSeq();// 构造解（批序列）
	void LS();// LS算法
	int getEPC(int t, int detaT,int k,int l);// 计算EPC，t为下界，detaT为整个过程的时间,机器为第k阶段的第l台机器
	~ant();
};

