#include "stdafx.h"
#include "Core.h"
#include <thread>
#include <iostream>

std::thread* CoreThread;
bool run = true;
void Core::main(std::thread* coreThread)
{
	while (run)//�.�. ������ �����, ���� ��������� �� ������
	printf( "���� ��������! ���� ����� �������� �� ������." );	// �������� � ������ � �������, ������ �� �����. ����� ���� �������.
}

void Core::stopCore()
{
	run = false;
	std::cout << "��� �������� ��� ���������� ������ �������";	// ������� ��� � ���� ������ �� ������� ����� � �������, 
																//��� ������ - ����� �������
}
