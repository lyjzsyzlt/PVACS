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
	
	
	float Cmax;//��¼���makespan
	float EPC;//��¼���յ�EPC

	
public:
	int id;
	vector<int> sol;//��Ž�
	vector<batch> tempB;
	ant()
	{
		
	};
	void generateV();//����ƫ������������ֵ
	void createBatchSeq();// ����⣨�����У�
	void LS();// LS�㷨
	float getEPC1(float t, float detaT,int k,int l);// ����EPC��tΪ�½磬detaTΪ�������̵�ʱ��,����Ϊ��k�׶εĵ�l̨����
	float getEPC2(float t, float detaT);//��������Ĵ������
	~ant();
};

