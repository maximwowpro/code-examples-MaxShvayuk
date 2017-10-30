//інтерфейс класа

class MaxClimate// class name
{
protected:

	float temp;//температура
	float light;//освітленість
	float water;//вологість
	float acid;//кислотність ґрунту
	
	public:

	MaxClimate();//конструктор класа за замовчуванням
	
	MaxClimate (float, float, float, float);//конструктор класа з параметрами
	
	MaxClimate (const MaxClimate &src);//конструктор копіювання
	
	
	void copyContructorTest(MaxClimate testObject);//функція для тесту конструктора копіювання
	
	void setClimate(float temp_public, float light_public, float water_public, float acid_public);//задати клімат (функція для конструктора з параметрами)
	
	void getClimate();// вивести клімат у консоль
	
	void modificatorTemp(float tempMod);//модифікатор
	void modificatorWater(float waterMod);//модифікатор
	void modificatorLight(float lightMod);//модифікатор
	void modificatorAcid(float acidMod);//модифікатор
	
	void testPointer(float temp_mod, float water_mod, float light_mod, float acid_mod);//тест вказівника this
	
	virtual float showPrivateTemp() const;//селектор //віртуальна функція
	
	float summOf2parameters(float tempInput, float waterInput);//перегрузка функции
	float summOf2parameters(float tempInput, float waterInput, float lightInput, float acidInput);//перегрузка функции
	
	~MaxClimate();//деструктор класа

};



