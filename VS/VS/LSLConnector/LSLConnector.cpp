#include "stdafx.h"
#include "LSLConnector.h"


LSLConnector::LSLConnector()
{
}

void LSLConnector::getData()
{
	double* arr = new double[5];
	for (int i = 0; i < 5; i++)
		arr[i] = i;

	//��� ������� ������ � �������. ���������� � Core. ������ ����� ��������� ����� ������ ������, �� ����������� double*
	sendData();
}

LSLConnector::~LSLConnector()
{
}
