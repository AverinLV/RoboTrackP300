#include "stdafx.h"
#include "Core.h"
#include <thread>
//#include <boost/signals2.hpp>
#include <iostream>
#include "LSLConnector/LSLConnector.h"
#include "DataHandler/DataHandler.h"
//#include "boost/bind.hpp"

std::thread* CoreThread;
bool run = true;

void Core::main(std::thread* coreThread)
{
	LSLConnector LSLInput;
	DataHandler dataHandler;
	//��� ��������� LSLInput � dataHandler (������ sendData � ���� dataProcessing)
	//LSLInput.sendData.connect(boost::bind(&DataHandler::dataProcessing, &dataHandler));
	while (run)
	{
		dataHandler.dataProcessing(LSLInput.getData());
		//���������� ������, ��� ����� �������� ������,
	}
}

void Core::stopCore()
{
	run = false;
	//��� �������� ��� ���������� ������ �������
	//� ������ ������ - ���������� ������ �����
}
