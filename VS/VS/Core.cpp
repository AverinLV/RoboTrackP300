#include "stdafx.h"
#include "Core.h"
#include <thread>
#include <boost/signals2.hpp>
#include <iostream>

std::thread* CoreThread;
bool run = true;


class Example
{
public:
	boost::signals2::signal<void()> onShit;
};

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
