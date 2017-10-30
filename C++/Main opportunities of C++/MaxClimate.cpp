//��������� �����
#include "MaxClimate.h"

#include <iostream>
using namespace std;
	
MaxClimate :: MaxClimate()//����������� ����� �� �������������
	{
		temp = 17;
		light = 267;
		water = 13;
		acid = 456;
		cout << "\ndefault contructor has worked";
	}
	
MaxClimate::MaxClimate (float temp_construct, float light_construct, float water_construct, float acid_construct)//����������� ������ � �����������
	{
		setClimate(temp_construct, light_construct, water_construct, acid_construct);
		cout << "parametric contructor has worked";

	} 
	
MaxClimate :: MaxClimate(const MaxClimate &src)//����������� ���������
	{
		cout << "\ncopy contructor has worked"<<endl;
		*this = src;//������, �������� ���������. src - �� ���������� ��"���, ���� �� ������, ���������, ���������� � �������
	}
	
void MaxClimate :: copyContructorTest(MaxClimate testObject)//���� ������������ ���������
	{
		cout<<" copy constructor test";
		testObject.getClimate();
	}
	
void MaxClimate :: setClimate(float temp_public, float light_public, float water_public, float acid_public)//������ �����
	{	
		temp = temp_public;
		light = light_public;
		water = water_public; 
		acid = acid_public;
	}
	
 void MaxClimate::getClimate()// ������� ����� � �������
	{
		cout << "\n\nClimate now is: "<< "\n temp = "<< temp <<"\n light = "<<light<<"\n water = "<<water<<"\n acid = "<<acid<< endl;
	}
	
void MaxClimate :: modificatorTemp(float tempMod)//�����������
	{		
		temp = tempMod;
	}

void MaxClimate :: modificatorWater(float waterMod)//�����������
	{		
		water = waterMod;
	}
	
void MaxClimate :: modificatorLight(float lightMod)//�����������
	{		
		light = lightMod;
	}
	
void MaxClimate :: modificatorAcid(float acidMod)//�����������
	{		
		acid = acidMod;
	}

void MaxClimate :: testPointer(float temp_mod, float water_mod, float light_mod, float acid_mod)//���� ��������� this
	{
		
		cout<<"\n\ntest pointer test:";
		
		this->temp = temp_mod;//�� �������� ������ �� ������ ����� �� ��������� ��������� this,
		this->water = water_mod;//���� ����� �� ��� ��'���
		this->light = light_mod;
		this->acid = acid_mod;
		
		getClimate();

	}	

float MaxClimate :: showPrivateTemp() const//��������//��������� �������
	{
		cout << "\n VIRTUAL selector func test MaxClimate\n";
		return temp;
	}

float MaxClimate :: summOf2parameters(float tempInput, float waterInput)//���������� �������
	{
		float summ = tempInput + waterInput;
		return summ;
	}
	
float MaxClimate :: summOf2parameters(float tempInput, float waterInput, float lightInput, float acidInput)//���������� �������
	{
		float summ = tempInput + waterInput + lightInput + acidInput;
		return summ;
	}
	
MaxClimate :: 	~MaxClimate()//���������� �����
	{
		cout << "\ndestructor has worked";
	}
	
