#pragma once
#include"defines.h"
#include<vector>
using namespace std;
// ����
struct job
{
	int JobId;//�������
	int JobSize;//�����ߴ�
	vector<int> JobPT;//�����ٲ�ͬ�׶εĴ���ʱ��
};

// ��
struct batch
{
	int BId;//�����
	//int BSize;//���ߴ�
	vector<int> BP;//���ٲ�ͬ�׶����崦��ʱ��
	//int BR;//������ʱ��
	//vector<int> BS;//���ٲ�ͬ�׶ο�ʼ�ӹ�ʱ��
	//vector<int> BC;//���ٲ�ͬ�׶��깤ʱ��                                         
	vector<int> MId;//������ͬ�׶����ڻ�����
	int JNum;//���й�������
	//vector<int> jobid;//���й������
	int freeSpace;//��¼����ʣ��ռ�
	vector<job> BJob;//�������ŵĹ���
};

// ����
struct machine
{
	int MId;//�������
	int MSize;//�����ߴ�
	int MP;//��ǰ��������ʱ��
	int MEpc;//�����ɱ�
	int BNum;//����������Ŀ
	int MBId[JobNum + 1];//���������ţ�0λ�ճ�
};