#include "stdafx.h"
#include "DataHandler.h"


DataHandler::DataHandler()
{
	out.open("log.log");        // �������� ���� ��� ������
	if (out.is_open())
	{
		out << "Log started!" << std::endl;
	}
}


DataHandler::~DataHandler()
{
	out.close();
}

void DataHandler::dataProcessing(std::vector<float> sample)
{
	//----------------------------------------------------------
	// ����� ��� ������
	for (std::size_t i = 0; i < sample.size(); ++i) {
		out << sample[i] << ' ';
	}
	out << std::endl;
	//----------------------------------------------------------

	//printf("123");
	//��� ��� (�����) ����������
}
