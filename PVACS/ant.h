#pragma once
#include"functions.h"
#include"structs.h"
#include"Machine.h"
class ant
{
private:
	// �û�ƫ������
	float Vmk;
	float Vepc;
	vector<int> sol;//��Ž�
	vector<batch> tempB;
	Machine *M;
	//int bNum;// ��������
	/*static int pos[100];// λ��
	static int info[100][100];// ����ʽ��Ϣ*/
	
public:
	int id;
	ant()
	{
		M = new Machine();
	};
	void generateV();//����ƫ������������ֵ
	void createBatchSeq();// ����⣨�����У�
	void LS();// LS�㷨
	int getEPC(int t, int detaT,int k,int l);// ����EPC��tΪ�½磬detaTΪ�������̵�ʱ��,����Ϊ��k�׶εĵ�l̨����
	~ant();
};

