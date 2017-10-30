//������� ��������� ������� �� ����� - �������
#include "MaxClimate.h"
#include <iostream>

class MaxClimateGarden : public MaxClimate//�����
{
	protected:
	float criticalWater;//��������� ����� ������
	float criticalAcid;//��������� ����� ����������
	
	public:
	
	MaxClimateGarden() : MaxClimate()//������������� ����������� �������� ����� � ���� - �������
	{	}
	
	MaxClimateGarden(float temp_input, float light_input, float water_input, float acid_input) : MaxClimate(temp_input, light_input, water_input,  acid_input)
	{	}
	//������������� ����������� � ����������� �������� ����� � �������
	
	int criticalValues (float critWater, float critAcid);
	//������ ������� �������� �� ����������
	//�������� �� �������� ���� ��� ������� ���������� ����� � �� ������	
	
	MaxClimateGarden& operator =( MaxClimateGarden &src);//�������������� ��������� - ���������
	// ����� �� ���� ���������� �������� temp i water �� 10
	
	const bool operator  == (const MaxClimateGarden &v1);
	
	friend std::ostream& operator << (std::ostream& os, MaxClimateGarden& data);
	friend std::istream& operator >> (std::istream& os, MaxClimateGarden& data);
	
	MaxClimateGarden& operator ++(int);//�������������� ++, � ��������� ����� �� ������ water �� 1
	
	float showPrivateTemp() const;// VIRTUAL - ��������	
};

class MaxClimateGreenhouse : public MaxClimate//�������
{
	protected:
	float optimalConditions[4];//��������� �����
	float allowableConditions[4];//�������� �����
	
	public: 
	
	MaxClimateGreenhouse() : MaxClimate()
	{	}
	
	MaxClimateGreenhouse(float temp_input, float light_input, float water_input, float acid_input) : MaxClimate(temp_input, light_input, water_input, acid_input)
	{	}
	
	void fillOptimalConditions(float temp_opt, float water_opt, float light_opt, float acid_opt);
	void fillAllowableConditions(float temp_allow, float water_allow, float light_allow, float acid_allow);
	//���������� ��������� �� �������� ��������
	
	void analyseConditions();
	//������ ������ ��������, ������� �� � ������������ �� �����������
	//���� ���� ����-���� �������� �� ����������� - ���� ��� ��
	//���� ���� �������� �� �������� - ���� ��� �� � ���� �� ������ ����������� ���������� ��������
	//���� �� ������� � � ��� �������� - ���� ��� ��
	
	float showPrivateTemp() const;// VIRTUAL - ��������	

};



