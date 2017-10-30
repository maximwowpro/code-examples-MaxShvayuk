//реалізація класа
#include "MaxClimate.h"

#include <iostream>
using namespace std;
	
MaxClimate :: MaxClimate()//конструктор класа за замовчуванням
	{
		temp = 17;
		light = 267;
		water = 13;
		acid = 456;
		cout << "\ndefault contructor has worked";
	}
	
MaxClimate::MaxClimate (float temp_construct, float light_construct, float water_construct, float acid_construct)//конструктор класса з параметрами
	{
		setClimate(temp_construct, light_construct, water_construct, acid_construct);
		cout << "parametric contructor has worked";

	} 
	
MaxClimate :: MaxClimate(const MaxClimate &src)//конструктор копіювання
	{
		cout << "\ncopy contructor has worked"<<endl;
		*this = src;//власне, операція копіювання. src - це тимчасовий об"єкт, який ми будемо, наприклад, передавати в функцію
	}
	
void MaxClimate :: copyContructorTest(MaxClimate testObject)//тест конструктора копіювання
	{
		cout<<" copy constructor test";
		testObject.getClimate();
	}
	
void MaxClimate :: setClimate(float temp_public, float light_public, float water_public, float acid_public)//задати клімат
	{	
		temp = temp_public;
		light = light_public;
		water = water_public; 
		acid = acid_public;
	}
	
 void MaxClimate::getClimate()// вивести клімат у консоль
	{
		cout << "\n\nClimate now is: "<< "\n temp = "<< temp <<"\n light = "<<light<<"\n water = "<<water<<"\n acid = "<<acid<< endl;
	}
	
void MaxClimate :: modificatorTemp(float tempMod)//модифікатор
	{		
		temp = tempMod;
	}

void MaxClimate :: modificatorWater(float waterMod)//модифікатор
	{		
		water = waterMod;
	}
	
void MaxClimate :: modificatorLight(float lightMod)//модифікатор
	{		
		light = lightMod;
	}
	
void MaxClimate :: modificatorAcid(float acidMod)//модифікатор
	{		
		acid = acidMod;
	}

void MaxClimate :: testPointer(float temp_mod, float water_mod, float light_mod, float acid_mod)//тест вказівника this
	{
		
		cout<<"\n\ntest pointer test:";
		
		this->temp = temp_mod;//ми отримуємо доступ до змінних класу за допомогою вказівника this,
		this->water = water_mod;//який вказує на цей об'єкт
		this->light = light_mod;
		this->acid = acid_mod;
		
		getClimate();

	}	

float MaxClimate :: showPrivateTemp() const//селектор//віртуальна функція
	{
		cout << "\n VIRTUAL selector func test MaxClimate\n";
		return temp;
	}

float MaxClimate :: summOf2parameters(float tempInput, float waterInput)//перегрузка функции
	{
		float summ = tempInput + waterInput;
		return summ;
	}
	
float MaxClimate :: summOf2parameters(float tempInput, float waterInput, float lightInput, float acidInput)//перегрузка функции
	{
		float summ = tempInput + waterInput + lightInput + acidInput;
		return summ;
	}
	
MaxClimate :: 	~MaxClimate()//деструктор класа
	{
		cout << "\ndestructor has worked";
	}
	
