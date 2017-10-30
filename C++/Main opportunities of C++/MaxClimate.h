//��������� �����

class MaxClimate// class name
{
protected:

	float temp;//�����������
	float light;//����������
	float water;//��������
	float acid;//���������� ������
	
	public:

	MaxClimate();//����������� ����� �� �������������
	
	MaxClimate (float, float, float, float);//����������� ����� � �����������
	
	MaxClimate (const MaxClimate &src);//����������� ���������
	
	
	void copyContructorTest(MaxClimate testObject);//������� ��� ����� ������������ ���������
	
	void setClimate(float temp_public, float light_public, float water_public, float acid_public);//������ ����� (������� ��� ������������ � �����������)
	
	void getClimate();// ������� ����� � �������
	
	void modificatorTemp(float tempMod);//�����������
	void modificatorWater(float waterMod);//�����������
	void modificatorLight(float lightMod);//�����������
	void modificatorAcid(float acidMod);//�����������
	
	void testPointer(float temp_mod, float water_mod, float light_mod, float acid_mod);//���� ��������� this
	
	virtual float showPrivateTemp() const;//�������� //��������� �������
	
	float summOf2parameters(float tempInput, float waterInput);//���������� �������
	float summOf2parameters(float tempInput, float waterInput, float lightInput, float acidInput);//���������� �������
	
	~MaxClimate();//���������� �����

};



