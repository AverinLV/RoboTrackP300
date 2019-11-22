#include "stdafx.h"
#include "DataHandler.h"



DataHandler::DataHandler()
{
	out.open("log.log");        // �������� ���� ��� ������
	if (out.is_open())
	{
		out << "Log started!" << std::endl;
	}
	t1 = std::chrono::high_resolution_clock::now();
}

DataHandler::~DataHandler()
{
	out.close();
}

std::vector<std::vector<float>> DataHandler::dataProcessing(std::vector<float> sample)
{
	//----------------------------------------------------------
	// ����� ��� ������

	
	std::chrono::steady_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	// floating-point duration: no duration_cast needed
	std::chrono::duration<double, std::milli> fp_ms = t2 - t1;

	float timeNOW = fp_ms.count();






	//out << timeNOW << ' ';
	//for (std::size_t i = 0; i < sample.size(); ++i) {
	//	out << sample[i] << ' ';
	//}
	//out << std::endl;
	
	if (vectorProb.empty()) {
		out << "������� ������ ���� � ";
		for (int i = 0; i < sample.size()+2; i++) {
			std::vector<float> proba;
			vectorProb.push_back(proba);
			out << i << ' ';
		}
		out << std::endl << "������� �������." << std::endl;
	}
	

	
	vectorProb[0].push_back(timeNOW);
	vectorProb[1].push_back(STATUS);
	for (int i = 0; i < sample.size(); i++) 
	{
		vectorProb[i + 2].push_back(sample[i]);
	}

	float oldPackageTime = vectorProb[0][0];


	if ((timeNOW - SIZE_PRESHOW > oldPackageTime) && (!CREATING_PROBA)) // ���� �� �� ����������� ����� � ���������� ������ ������ ������� ������ ������
	{
		int i = 0;
		while (i<vectorProb[0].size()) {
			if (timeNOW - SIZE_PRESHOW > vectorProb[0][i]) {
				i++;
			}
			else {

				break;
			}
		}

		// ������� ������ ������ �� i���� �������� ������������
		for (int j = 0; j < vectorProb.size(); j++) {
			vectorProb[j].erase(vectorProb[j].begin(), vectorProb[j].begin() + i);
		}
	}

	if (CREATING_PROBA) { // ���� �� ������� �����
		if (timeNOW - oldPackageTime >= SIZE_PROBA) {// � ��� ���������
			//������� ��������� �������
			for (int j = 0; j < vectorProb.size(); j++) {
				vectorProb[j].erase(vectorProb[j].end()-1);
			}
			CREATING_PROBA = false;//�������� ��� �� ������ ��������� ���������� �����
			STATUS = 0; // �������� ������
			return vectorProb;
		}
	}



	//out << std::endl;
	//out << std::endl;
	
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
		startCreateVectorProba();         // �������� ���������� �����
		STATUS = status;
	}
}
