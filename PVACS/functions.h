#pragma once
#ifndef functions_H
#define functions_H

#include"structs.h"
#include<algorithm>
#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
int max(int a, int b);


// ��ʼ����������Ϣ
void initJob(vector<job> &J);


bool cmp(const job &J1, const job &J2);


bool cmp2(const batch &b1, const batch &b2);
bool cmp3(const batch &b1, const batch &b2);
// ��ʼ�����Ļ�����Ϣ
void initBatch(batch &B, int id);

// ���������������ӹ�ʱ��
void getPbk(vector<job> J, vector<batch> &B);

// ����
void BFLPT(vector<job> J/*, vector<batch> &B*/);


// ��������������Ĺ���
void displayBatch(/*vector<batch> B*/);//������const vector<batch> B

// �������������б��,��ȡ����ʽ��Ϣ����

/*int info[100][100];
int pos[100];*/
void computeSIb(/*vector<batch> &B*/);

/*float phmk[100][100];//mk��Ӧ����Ϣ�ؾ���
float phepc[100][100];//epc��Ӧ����Ϣ�ؾ���*/

// ��ʼ����Ϣ�ؾ���
void initPh();
void initM();
#endif // !functions_H
