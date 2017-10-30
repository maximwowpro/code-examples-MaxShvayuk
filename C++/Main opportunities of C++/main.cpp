//Created by Max Shvayuk 15.09.2017
#include <iostream>
#include "MaxClimateLaba2.h"
using namespace std;

int main ()
{	
	MaxClimate MaxBasic (11, 29, 38, 44);//базовий клас
	//MaxBasic.getClimate();
	float temp = MaxBasic.showPrivateTemp();//віртуальна функція
	cout<<"\ntemp = "<<temp<<"\ntest of peregruzka function: summOf2 = ";//тест перевантаженої функції
	float summ = MaxBasic.summOf2parameters(11, 29);
	cout<<summ<<"\nsummOf4 = ";
	summ = MaxBasic.summOf2parameters(11, 29, 38, 44);
	cout<<summ<<endl;
	
	cout << "\nGARDEN\n";
	MaxClimateGarden MaxGarden (12, 45, 67, 34);//клас - нащадок - город
	//MaxGarden.getClimate();
//	MaxGarden.criticalValues(30, 19);//максимальні допустимі значення
	temp = MaxGarden.showPrivateTemp();//віртуальна функція
	cout<<"\ntemp = "<<temp<<"\n == test"<<"\ntest overloading of ' = ' \n";
	
	MaxClimateGarden MaxGarden2;
	MaxGarden2 = MaxGarden;//тест перевантаженого оператора =
	
	MaxGarden.getClimate();//тут ми бачимо у консолі різницю на 10 у temp i light
	MaxGarden2.getClimate();

	MaxGarden2 == MaxGarden;//тест перевантаженого оператора ==
	
	cout << "\ntest operator \n";
	cin >> MaxGarden2;
	cout<<"\ntest operator << \n"<<MaxGarden2;
	
	MaxGarden2++;//збільшуємо значення water на 1
	MaxGarden2.getClimate();

	
	cout << "\nGREENHOUSE\n";
	MaxClimateGreenhouse MaxGreenhouse (21, 21, 21, 21);
//	MaxGreenhouse.getClimate();
//	MaxGreenhouse.fillOptimalConditions(20, 20, 20, 20);//внесли оптимальні значення
//	MaxGreenhouse.fillAllowableConditions(30, 30, 30, 30);//внесли максимальні допустимі значення
//	MaxGreenhouse.analyseConditions();
	temp = MaxGreenhouse.showPrivateTemp();//віртуальна функція
	cout<<"\ntemp = "<<temp<<endl;
	
	
	
	
	
	
	MaxClimate* pointer [3];
	MaxClimateGarden obj1(12,23,34,45);
	MaxClimateGreenhouse obj2(1,2,3,4);
	pointer[0] = &obj1;

	pointer[1] = &obj2;
	for (int i = 0; i < 2; i++)
	{
		float a = pointer[i]->showPrivateTemp();
		cout << a<<endl;
	}

	return 0;
}



















