//функції критичних значень та класи - нащадки

#include "MaxClimateLaba1.h"
#include <iostream>
using namespace std;


int MaxClimateGarden :: criticalValues (float critWater, float critAcid)
{
	criticalWater = critWater;
	criticalAcid = critAcid;
	
	float difference = 0;
	if (water > critWater)
	{
		difference = water - critWater;
		cout << "\n CRITICAL CONDITION OF WATER IS EXCEEDED ON "<< difference<< endl;
		return 1;
	}
	
	if(acid > critAcid)
	{
		difference = acid - critAcid;
		cout << "\n CRITICAL CONDITION OF ACID IS EXCEEDED ON "<< difference<< endl;
		return 2;
	}
	
	if(difference == 0)
	{
		cout<< "\nCritical conditions haven't been exceeded"<< endl;
		return 0;
	}
}

MaxClimateGarden &MaxClimateGarden :: operator =( MaxClimateGarden &src)//перевантаження оператора - присвоєння
	{// тепер він буде збільшувати значення temp i light на 
		temp = src.temp+10;
		water = src.water;
		light = src.light+10;
		acid = src.acid;
		return *this;		
	}

const bool MaxClimateGarden::operator == (const MaxClimateGarden & src)
{
	bool result = false;

	if(temp == src.temp && light == src.light && water == src.water && acid == src.acid && criticalWater == src.criticalWater && criticalAcid == src.criticalAcid)
	{
		result = true;
		cout << "\n they are equal";
	}
	else
	{
		cout << "\n not equal";
	}

	return result;
}

ostream& operator << (ostream& os, MaxClimateGarden& data)
{
	cout << "temp: " << data.temp << endl;
	cout << "water: " << data.water << endl;
	cout << "light: " << data.light << endl;
	cout << "acid: " << data.acid << endl;
	return os;
}

istream& operator >> (istream& os,  MaxClimateGarden& data)
{
	cout << "\ntemp: "; cin >> data.temp;
	cout << "\nwater: "; cin >> data.water;
	cout << "\nlight: "; cin >> data.light;
	cout << "\nacid: "; cin >> data.acid;
	return os;
}

MaxClimateGarden& MaxClimateGarden :: operator ++(int)
	{//перевантаження ++, у результаті якого від збільшує water на 1
		this->water++;
		return *this;	
	}

float MaxClimateGarden :: showPrivateTemp() const//селектор//віртуальна функція
	{
		cout << "\n\n VIRTUAL selector func test MaxClimateGarden";
		return temp;
	}

void MaxClimateGreenhouse :: fillOptimalConditions(float temp_opt, float water_opt, float light_opt, float acid_opt)
{
	optimalConditions[0] = temp_opt;
	optimalConditions[1] = water_opt;
	optimalConditions[2] = light_opt;
	optimalConditions[3] = acid_opt;
}

void MaxClimateGreenhouse :: fillAllowableConditions(float temp_allow, float water_allow, float light_allow, float acid_allow)
{
	allowableConditions[0] = temp_allow;
	allowableConditions[1] = water_allow;
	allowableConditions[2] = light_allow;
	allowableConditions[3] = acid_allow;	
}

void MaxClimateGreenhouse :: analyseConditions()
{
	 //аналіз температури
	 if(temp > allowableConditions[0])
	 {
	 	float difference = temp - allowableConditions[0];
	 	cout<<"\nTEMP IN GREENHOUSE IS HIGHTER THEN ALLOWABLE ON "<<difference<<endl;
	 }
	 else
	 {
	 	float temp_optimal_max = optimalConditions[0]+2;
	 	float temp_optimal_min = optimalConditions[0]-2;
		if(temp > temp_optimal_min && temp < temp_optimal_max)
		{
			cout<<"\ntemp in greenhouse is optimal\n";
		}
		else
		{
			cout<<"\ntemp in greenhouse is normal\n";
		}
	 }
	 
	 //аналіз вологості
	 if(water > allowableConditions[1])
	 {
	 	float difference = water - allowableConditions[1];
	 	cout<<"\nWATER IN GREENHOUSE IS HIGHTER THEN ALLOWABLE ON "<<difference<<endl;
	 }
	 else
	 {
	 	float water_optimal_max = optimalConditions[1]+2;
	 	float water_optimal_min = optimalConditions[1]-2;
		if(water > water_optimal_min && water < water_optimal_max)
		{
			cout<<"\nwater in greenhouse is optimal\n";
		}
		else
		{
			cout<<"\nwater in greenhouse is normal\n";
		}
	 }
	 
	 //аналіз освітленості
	 if(light > allowableConditions[2])
	 {
	 	float difference = light - allowableConditions[2];
	 	cout<<"\nLIGHT IN GREENHOUSE IS HIGHTER THEN ALLOWABLE ON "<<difference<<endl;
	 }
	 else
	 {
	 	float light_optimal_max = optimalConditions[2]+2;
	 	float light_optimal_min = optimalConditions[2]-2;
		if(light > light_optimal_min && light < light_optimal_max)
		{
			cout<<"\nlight in greenhouse is optimal\n";
		}
		else
		{
			cout<<"\nlight in greenhouse is normal\n";
		}
	 }
	 
	 //аналіз кислотності
	 if(acid > allowableConditions[3])
	 {
	 	float difference = acid - allowableConditions[3];
	 	cout<<"\nACID IN GREENHOUSE IS HIGHTER THEN ALLOWABLE ON "<<difference<<endl;
	 }
	 else
	 {
	 	float acid_optimal_max = optimalConditions[3]+2;
	 	float acid_optimal_min = optimalConditions[3]-2;
		if(acid > acid_optimal_min && acid < acid_optimal_max)
		{
			cout<<"\nacid in greenhouse is optimal\n";
		}
		else
		{
			cout<<"\nacid in greenhouse is normal\n";
		}
	 }
}

float MaxClimateGreenhouse :: showPrivateTemp() const//селектор//віртуальна функція
	{
		cout << "\n\n VIRTUAL selector func test MaxClimateGreenhouse";
		return temp;
	}


