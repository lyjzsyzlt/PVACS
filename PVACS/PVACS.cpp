// PVACS.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"functions.h"
#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

int main()
{
	vector<job> J;
	vector<batch> B;
	initJob(J);
	BFLPT(J, B);
	displayBatch(B);

    return 0;
}

