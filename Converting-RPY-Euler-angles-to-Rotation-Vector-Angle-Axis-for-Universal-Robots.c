#include <iostream>
#include "math.h"
using namespace std;
#define pi 3.1415926
/*
ToRotVector函数功能：将欧拉角（RPY角）转换为旋转矢量（Rx，Ry，Rz）；
UR脚本语言中关于位姿的定义为：（x,y,z,Rx,Ry,Rz）；
Roll, Pitch and Yaw中，改变Yaw的值可以实现机器人绕工具系的z轴方向旋转；
ToRotVector函数输入：欧拉角：r，p，y；
ToRotVector函数输出：旋转矢量的数组[Rx,Ry,Rz]
参考：
1. http://www.zacobria.com/universal-robots-knowledge-base-tech-support-forum-hints-tips/c-code-example-of-converting-rpyeuler-angles-to-rotation-vectorangle-axis-for-universal-robots/
2. http://www.zacobria.com/universal-robots-knowledge-base-tech-support-forum-hints-tips/python-code-example-of-converting-rpyeuler-angles-to-rotation-vectorangle-axis-for-universal-robots/
*/

double* ToRotVector(double r, double p, double y)
{
	double RV[3] = { 0, 0, 0 };
	double rpy[3] = { 0, 0, 0 };
	double rollM[3][3] = { { 1, 0, 0 }, { 0, 9, 9 }, { 0, 9, 9 } };
	double pitchM[3][3] = { { 9, 0, 9 }, { 0, 1, 0 }, { 9, 0, 9 } };
	double yawM[3][3] = { { 9, 9, 0 }, { 9, 9, 0 }, { 0, 0, 1 } };
	double RotM[3][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
	double Rot[3][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };

	//for (int i = 0; i < 3; i++)
	//for (int j = 0; j < 3; j++)
	//{
	//	cout << "pitchM[" << i << "][" << j << "]: ";
	//	cout << pitchM[i][j] << endl;
	//}
	//RPY角输入赋值；
	rpy[0] = r;
	rpy[1] = p;
	rpy[2] = y;

	rollM[1][1] = cos(rpy[0]);
	rollM[1][2] = -sin(rpy[0]);
	rollM[2][1] = sin(rpy[0]);
	rollM[2][2] = cos(rpy[0]);

	pitchM[0][0] = cos(rpy[1]);
	pitchM[0][2] = sin(rpy[1]);
	pitchM[2][0] = -sin(rpy[1]);
	pitchM[2][2] = cos(rpy[1]);

	yawM[0][0] = cos(rpy[2]);
	yawM[0][1] = -sin(rpy[2]);
	yawM[1][0] = sin(rpy[2]);
	yawM[1][1] = cos(rpy[2]);

	// 输出数组中每个元素的值                      
	/*for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
	{
	cout << "pitchM[" << i << "][" << j << "]: ";
	cout << pitchM[i][j] << endl;
	}*/
	/*for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
	{
	cout << "rollM[" << i << "][" << j << "]: ";
	cout << rollM[i][j] << endl;
	}*/
	//double rollm = rollM[1][1];
	//printf("rollm:%8g\n", rollm);
	//rot = yaw * pitch * roll
	//rotM = pitch * roll
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				RotM[i][j] += pitchM[i][k] * rollM[k][j];
			}
		}
	}

	//rot = yawM * rotM 
	for (auto i = 0; i < 3; i++)
	{
		for (auto j = 0; j < 3; j++)
		{
			for (auto k = 0; k < 3; k++)
			{
				Rot[i][j] += yawM[i][k] * RotM[k][j];
			}
		}
	}
	//for (int i = 0; i < 3; i++)
	//for (int j = 0; j < 3; j++)
	//{
	//	cout << "Rot[" << i << "][" << j << "]: ";
	//	cout << Rot[i][j] << endl;
	//}
	/*double RotA = Rot[0][0];
	printf("Rota:%8g\n", RotA);*/
	double rotSum = (Rot[0][0] + Rot[1][1] + Rot[2][2]) - 1;
	double alpha = acos(rotSum / 2);
	double theta = 0;
	if (rpy[0] >= 0)
	{
		theta = alpha;
	}
	else
	{
		theta = 2 * pi - alpha;
	}
	double my = 1 / (2 * sin(theta));

	double rx = my * (Rot[2][1] - Rot[1][2]) * theta;
	double ry = my * (Rot[0][2] - Rot[2][0]) * theta;
	double rz = my * (Rot[1][0] - Rot[0][1]) * theta;

	RV[0] = rx;
	RV[1] = ry;
	RV[2] = rz;

	return RV;

}


void main()
{
	double *result;
	double *result2;

	result = ToRotVector(1.1626, -2.9205, 0); //test data1
	printf("Rx:%8g\nRy:%8g\nRz:%8g\n", result[0], result[1], result[2]);

	system("pause");

}
