#pragma once
//#include"functions.h"
#include"structs.h"
class ant
{
private:
	// 用户偏好向量
	float Vmk;
	float Vepc;
	
	//int bNum;// 批的数量
	/*static int pos[100];// 位置
	static int info[100][100];// 启发式信息*/
	
public:
	int id;
	ant(){};
	void generateV();//产生偏好向量的两个值
	void createBatchSeq();// 构造解（批序列）
	~ant();
};

