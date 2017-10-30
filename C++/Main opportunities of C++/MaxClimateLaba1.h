//функції критичних значень та класи - нащадки
#include "MaxClimate.h"
#include <iostream>

class MaxClimateGarden : public MaxClimate//город
{
	protected:
	float criticalWater;//критичний рівень вологи
	float criticalAcid;//критичний рівень кислотності
	
	public:
	
	MaxClimateGarden() : MaxClimate()//використовуємо конструктор базового класа у класі - нащадку
	{	}
	
	MaxClimateGarden(float temp_input, float light_input, float water_input, float acid_input) : MaxClimate(temp_input, light_input, water_input,  acid_input)
	{	}
	//використовуємо констурктор з параметрами базового класа у нащадку
	
	int criticalValues (float critWater, float critAcid);
	//задати критичні вологість та кислотність
	//виводить чи перевищує вода або кислота дозволений рівень і на скільки	
	
	MaxClimateGarden& operator =( MaxClimateGarden &src);//перевантаження оператора - присвоєння
	// тепер він буде збільшувати значення temp i water на 10
	
	const bool operator  == (const MaxClimateGarden &v1);
	
	friend std::ostream& operator << (std::ostream& os, MaxClimateGarden& data);
	friend std::istream& operator >> (std::istream& os, MaxClimateGarden& data);
	
	MaxClimateGarden& operator ++(int);//перевантаження ++, у результаті якого від збільшує water на 1
	
	float showPrivateTemp() const;// VIRTUAL - селектор	
};

class MaxClimateGreenhouse : public MaxClimate//теплиця
{
	protected:
	float optimalConditions[4];//оптимальні умови
	float allowableConditions[4];//допустимі умови
	
	public: 
	
	MaxClimateGreenhouse() : MaxClimate()
	{	}
	
	MaxClimateGreenhouse(float temp_input, float light_input, float water_input, float acid_input) : MaxClimate(temp_input, light_input, water_input, acid_input)
	{	}
	
	void fillOptimalConditions(float temp_opt, float water_opt, float light_opt, float acid_opt);
	void fillAllowableConditions(float temp_allow, float water_allow, float light_allow, float acid_allow);
	//заповнюють оптимальні та допустимі значення
	
	void analyseConditions();
	//аналізує поточні значення, порівнює їх з оптимальними та допустимими
	//якщо вони більш-менш підходять до оптимальних - пише про це
	//якщо вони виходять за допустимі - пише про це і видає на скільки перевищують допустимий максимум
	//якщо не входять ні у яку категорію - пише про це
	
	float showPrivateTemp() const;// VIRTUAL - селектор	

};



