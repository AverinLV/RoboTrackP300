#include "stdafx.h"
#include "DataHandler.h"

DataHandler::DataHandler()
{
	out.open("log.log");        // �������� ���� ��� ������
	if (out.is_open())
	{
		out << "Log started!" << std::endl;
	}

	eventOut.open("WinEEG_EventTable_v2.0_export.ann");
	if (eventOut.is_open())
	{
		eventOut << "Event Table V2.0" << std::endl;
		out << "Event Table file started!" << std::endl;
	}
	dataOut.open("WinEEG_Data_export.txt");
	if (dataOut.is_open()) 
	{
		out << "Data file started!" << std::endl;
	}
}

DataHandler::~DataHandler()
{
	out.close();
	eventOut.close();
	dataOut.close();
}

std::vector<std::vector<float>> DataHandler::dataProcessing(std::vector<float> sample)
{
	if (vectorProb.empty()) {
		out << "������� ������ ���� � ";
		for (int i = 0; i < sample.size()+1; i++) {
			std::vector<float> proba;
			vectorProb.push_back(proba);
			out << i << ' ';
		}
		out << std::endl << "������� �������." << std::endl;
	}

	vectorProb[0].push_back(STATUS);
	for (int i = 0; i < sample.size(); i++) 
	{
		vectorProb[i + 1].push_back(sample[i]);
		dataOut << (double) int(sample[i] * 10) / 10.0  << "\t";
	}
	dataOut << std::endl;
	DataTick++;

	if ((vectorProb[0].size() > SIZE_PRESHOW*Hz) && (!CREATING_PROBA)) // ���� �� �� ����������� ����� � ���������� ������ ������ ������� ������ ������
	{
		// ������� ������ ������ �� i���� �������� ������������
		for (int j = 0; j < vectorProb.size(); j++) {
			//out << "������� �� 0 �� "<< (int)(vectorProb[j].size() - SIZE_PRESHOW * Hz + 1) <<" �������� ������������\n";
			vectorProb[j].erase(vectorProb[j].begin(), vectorProb[j].begin() + (int) (vectorProb[j].size() - SIZE_PRESHOW * Hz + 1));
		}
	}
	
	if (CREATING_PROBA) { // ���� �� ������� �����
		if (vectorProb[0].size() >= SIZE_PROBA*Hz) {// � ��� ���������
			CREATING_PROBA = false;//�������� ��� �� ������ ��������� ���������� �����
			STATUS = 0; // �������� ������
			out << "�������� ���������� �����.\n";// � ����� "<<vectorProb[0].size()<<" ���������.\n";
			return vectorProb;
		}
	}

	std::vector<std::vector<float>> emptyVectProb;
	return emptyVectProb;
}

void DataHandler::startCreateVectorProba()
{
	CREATING_PROBA = true;
}

void DataHandler::setStatusPicture(int status)
{
	if ((STATUS == 0) && (status != 0)) { // ���� �� ������ ���������� ����� ��������
		STATUS = status;
		startCreateVectorProba();         // �������� ���������� �����
		eventOut << DataTick - 75 << ", 1, " << STATUS << std::endl;
		out << "������ ����������� �����..." << std::endl;
	}
}
