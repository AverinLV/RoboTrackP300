#include "stdafx.h"
#include "Game.h"

#include <thread>
#include <iostream>

using namespace Game;

bool runGame = true;

void Game::main(std::thread* gameThread)
{
	//������������� ����
	while (runGame)
	{
		std::cout << "";
		 // ������� ����, ������� ����� ����������
	}
	// ����� �������� ������������ ��������
}

void Game::stopGame() // ���������� ����� ��������� �����������
{
	runGame = false;
	//��� �������� ��� ���������� ������ ����
	//� ������ ������ - ���������� ������ �����
}
