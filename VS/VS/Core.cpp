#include "stdafx.h"
#include "Core.h"
#include <thread>
#include <iostream>
#include "LSLConnector/LSLConnector.h"
#include "DataHandler/DataHandler.h"
#include "tcpSender.h"

using namespace Core;

bool runCore = true;

LSLConnector LSLInput;
DataHandler dataHandler;
tcpSender tcpSender;

void Core::main(std::thread* coreThread)
{
	while (runCore)
	{
		std::vector<std::vector<float>> vectorProb = dataHandler.dataProcessing(LSLInput.getData());
		
		if (!vectorProb.empty()) 
		{//���� ����� ������
			tcpSender.sendDataByTCP(vectorProb);
			dataHandler.out << "�������� �������:" << std::endl;
			for (std::vector<float> proba : vectorProb) 
			{
				dataHandler.out << "������:" << std::endl;
				for (float data : proba) 
				{
					dataHandler.out << data << ' ';
				}
				dataHandler.out << std::endl;
				if(proba.size()!=200)
					dataHandler.out <<"������:"<< proba.size() <<" ���������"<< std::endl;
			}
		}
	}
}

void Core::stopCore()
{
	runCore = false;
	//��� �������� ��� ���������� ������ �������
	//� ������ ������ - ���������� ������ �����
}

void Core::askStatus(int stat) {
	//dataHandler.out << "����� = " << stat << "\n";
	dataHandler.setStatusPicture(stat);
}