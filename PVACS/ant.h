#pragma once
//#include"functions.h"
#include"structs.h"
class ant
{
private:
	// �û�ƫ������
	float Vmk;
	float Vepc;
	
	//int bNum;// ��������
	/*static int pos[100];// λ��
	static int info[100][100];// ����ʽ��Ϣ*/
	
public:
	int id;
	ant(){};
	void generateV();//����ƫ������������ֵ
	void createBatchSeq();// ����⣨�����У�
	~ant();
};

