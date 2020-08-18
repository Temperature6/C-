//version:20200818 ���� ��һ����������ʹ�õİ汾
#include <iostream>
#include <vector>
#include <string>
#include "function.h"
using namespace std;
bool isNegative = false;
bool* p_negative = &isNegative;

vector<char> Addition(string num1, string num2);
vector<char> Subtraction(string num1, string num2);
vector<char> Multiplication(string num1, string num2);
vector<char> Division(string num1, string num2, int decimal);
void ErrorExit(char pos);

int main()
{
	system("title �߾��������㷨");
FLAG:
	vector <char> answer;
	string Str;
	cout << "������ʽ>>>";
	cin >> Str;
	if (Str == "github")
	{
		system("start https://github.com/Temperature6/High-precision-algorithm");
		goto FLAG;
	}
	//Ѱ�������
	int opea = findopreator(Str);
	//�ж��Ƿ�Ϸ�����ʼ���ü��㺯��
	if (opea == 0)
	{
		printf("��������:\n\t����û���ڱ��ʽ���ҵ������\n\n");
		printf("�ο����¾���:\n\t���(+); \n\t���(-); \n\t���(*); \n\t����(/); \n\n");
		system("pause");
		goto FLAG;
	}
	else
	{
		vector <string> v;
		switch (Str[opea])
		{
		case '+':
			v = split(Str, "+");
			answer = Addition(v[0], v[1]);
			break;
		case '-':
			v = split(Str, "-");
			answer = Subtraction(v[0], v[1]);
			break;
		case '*':
			v = split(Str, "*");
			answer = Multiplication(v[0], v[1]);
			break;
		case '/':
			v = split(Str, "/");
			if (isNumberofTen(v[1]))
			{
				printf("ֻ���ƶ�С����ı��ʽ�������");
				break;
			}
			if (NumberisZero(v[1]))
			{
				printf("����!����Ϊ��!");
				break;
			}
			int dec = 0;
			printf("����𰸵���λ��(������������):");
			cin >> dec;
			answer = Division(v[0], v[1], dec);
			break;
		}
	}
	if (answer.size() != 0)
	{
		printf("\n");
		PrintAnswer(answer);
		printf("\n\n");
		system("pause");
	}
	printf("\n");
	goto FLAG;
}

void ErrorExit(char pos)
{
	printf("������������");
	printf("���棬������ִ���\n\n");
	printf("�������������Ƿ������ѧ����\n\n");
	switch (pos)
	{
	case 'A':
		printf("����ʱ���ִ���ĺ���:Addition");
		break;
	case 'S':
		printf("����ʱ���ִ���ĺ���:Subtraction");
		break;
	case 'M':
		printf("����ʱ���ִ���ĺ���:Multiplication");
		break;
	case 'D':
		printf("����ʱ���ִ���ĺ���:Division");
		break;
	}
	printf("\n\n");
	system("pause");
	exit(1);
}

vector<char> Addition(string num1, string num2)
{
	//string���ʹ���vector
	vector <char> Num1 = StringtoCharVec(num1);
	vector <char> Num2 = StringtoCharVec(num2);
	//����Ƿ����С���㣬��û�������
	if (findpoint(&Num1[0], Num1.size()) == -1)
	{
		Num1.push_back('.');
		Num1.push_back('0');
	}
	if (findpoint(&Num2[0], Num2.size()) == -1)
	{
		Num2.push_back('.');
		Num2.push_back('0');
	}
	//��ȡС����λ��,С��λ��
	int Num1point = findpoint(&Num1[0], Num1.size());
	int Num2point = findpoint(&Num2[0], Num2.size());
	int Num1decimal = DecimalPlaces(&Num1[0], Num1.size());
	int Num2decimal = DecimalPlaces(&Num2[0], Num2.size());
	//�������ֶ���
	if (Num1point > Num2point)
		Num2.insert(Num2.begin(), Num1point - Num2point, '0');
	if (Num1point < Num2point)
		Num1.insert(Num1.begin(), Num2point - Num1point, '0');
	//С�����ֶ���
	if (Num1decimal > Num2decimal)
		Num2.insert(Num2.end(), Num1decimal - Num2decimal, '0');
	if (Num1decimal < Num2decimal)
		Num1.insert(Num1.end(), Num2decimal - Num1decimal, '0');
	//ȷ������С����λ��
	int Anspoint = 0;
	if (findpoint(&Num1[0], Num1.size()) != findpoint(&Num2[0], Num2.size()))
		ErrorExit('A');
	else
		Anspoint = findpoint(&Num1[0], Num1.size());
	//ȥ��С����
	Num1.erase(Num1.begin() + findpoint(&Num1[0], Num1.size()));
	Num2.erase(Num2.begin() + findpoint(&Num2[0], Num2.size()));
	//�ַ�����ת��������
	vector <int> Number1 = VecChartoInt(Num1);
	vector <int> Number2 = VecChartoInt(Num2);
	//��ʼ����
	int unit = 0;
	int ten = 0;
	int temp = 0;
	vector <int> ReverseAns;
	
	for (int i = Number1.size() - 1; i >= 0; i--)
	{
		temp = Number1[i] + Number2[i] + ten;
		unit = temp / 1 % 10;
		ten = temp / 10 % 10;
		ReverseAns.push_back(unit);
	}
	if (ten != 0)
	{
		ReverseAns.push_back(ten);
		Anspoint++;
	}
	reverse(ReverseAns.begin(), ReverseAns.end());
	vector <char> out = VecInttoChar(ReverseAns);
	out.insert(out.begin() + Anspoint, '.');
	return out;
}

vector<char> Subtraction(string num1, string num2)
{
	//string���ʹ���vector
	vector <char> Num1 = StringtoCharVec(num1);
	vector <char> Num2 = StringtoCharVec(num2);
	//����Ƿ����С���㣬��û�������
	if (findpoint(&Num1[0], Num1.size()) == -1)
	{
		Num1.push_back('.');
		Num1.push_back('0');
	}
	if (findpoint(&Num2[0], Num2.size()) == -1)
	{
		Num2.push_back('.');
		Num2.push_back('0');
	}
	//��ȡС����λ��,С��λ��
	int Num1point = findpoint(&Num1[0], Num1.size());
	int Num2point = findpoint(&Num2[0], Num2.size());
	int Num1decimal = DecimalPlaces(&Num1[0], Num1.size());
	int Num2decimal = DecimalPlaces(&Num2[0], Num2.size());
	//�������ֶ���
	if (Num1point > Num2point)
		Num2.insert(Num2.begin(), Num1point - Num2point, '0');
	if (Num1point < Num2point)
		Num1.insert(Num1.begin(), Num2point - Num1point, '0');
	//С�����ֶ���
	if (Num1decimal > Num2decimal)
		Num2.insert(Num2.end(), Num1decimal - Num2decimal, '0');
	if (Num1decimal < Num2decimal)
		Num1.insert(Num1.end(), Num2decimal - Num1decimal, '0');
	//ȷ������С����λ��
	int Anspoint = 0;
	if (findpoint(&Num1[0], Num1.size()) != findpoint(&Num2[0], Num2.size()))
		ErrorExit('S');
	else
		Anspoint = findpoint(&Num1[0], Num1.size());
	//ȥ��С����
	Num1.erase(Num1.begin() + findpoint(&Num1[0], Num1.size()));
	Num2.erase(Num2.begin() + findpoint(&Num2[0], Num2.size()));
	//�ַ�����ת��������
	vector <int> Number1 = VecChartoInt(Num1);
	vector <int> Number2 = VecChartoInt(Num2);
	//��ʼ����
	vector <int> ReverseAns;
	int unit = 0;
	int temp = 0;

	for (int i = Number1.size() - 1; i >= 0; i--)
	{
		if (Number1[i] >= Number2[i])
			temp = Number1[i] - Number2[i];
		else
		{
			//��������һλ��Ҫ��λ�����ж�Ϊ�����������������ٵ���;
			if (i == 0)
			{
				*p_negative = true;
				vector <char> n_out;
				n_out = Subtraction(num2, num1);
				return n_out;
			}
			else
			{
				temp = Number1[i] - Number2[i] + 10;
				Number1[i - 1]--;
			}
		}
		ReverseAns.push_back(temp);
	}
	reverse(ReverseAns.begin(), ReverseAns.end());
	vector <char> out = VecInttoChar(ReverseAns);
	out.insert(out.begin() + Anspoint, '.');
	//�����������0
	out = FilterZero(out);

	if (*p_negative)
	{
		out.insert(out.begin(), '-');
		*p_negative = false;
	}

	return out;
}

vector<char> Multiplication(string num1, string num2)
{
	//string���ʹ���vector
	vector <char> Num1 = StringtoCharVec(num1);
	vector <char> Num2 = StringtoCharVec(num2);
	//��ȡС��λ��
	int Num1decimal = DecimalPlaces(&Num1[0], Num1.size());
	int Num2deciaml = DecimalPlaces(&Num2[0], Num2.size());
	//ȥ0���� 0.56 ��> .56
	if (findpoint(&Num1[0], Num1.size()) != -1 and Num1[0] == '0' and Num1[1] == '.')
		Num1.erase(Num1.begin());
	if (findpoint(&Num2[0], Num2.size()) != -1 and Num2[0] == '0' and Num2[1] == '.')
		Num2.erase(Num2.begin());
	//ȥС������� 78.32 ��> 7832
	if (findpoint(&Num1[0], Num1.size()) != -1)
		Num1.erase(Num1.begin() + findpoint(&Num1[0], Num1.size()));
	if (findpoint(&Num2[0], Num2.size()) != -1)
		Num2.erase(Num2.begin() + findpoint(&Num2[0], Num2.size()));
	//�ַ�����ת��������
	vector <int> Number1 = VecChartoInt(Num1);
	vector <int> Number2 = VecChartoInt(Num2);
	//��֤λ��С��������
	if (Number2.size() > Number1.size())
		Number1.swap(Number2);
	
	vector <int> Answer;
	
	int calccount = 0;
	
	for (int i = Number2.size() - 1; i >= 0; i--)
	{
		int unit = 0;
		int ten = 0;
		int temp = 0;
		vector <int> tempvec;
		for (int j = Number1.size() - 1; j >= 0; j--)
		{
			temp = Number1[j] * Number2[i] + ten;
			unit = temp / 1 % 10;
			ten = temp / 10 % 10;
			tempvec.push_back(unit);
		}
		if (ten != 0)
			tempvec.push_back(ten);
		tempvec.insert(tempvec.begin(), calccount, 0); //��֤����λ����ʱ�����10
		reverse(tempvec.begin(), tempvec.end()); //��������,ʹ����˳����ȷ
		//����ǵ�һ�μ��㣬����Answer���鲻����ӷ�����
		if (calccount == 0)
			Answer.swap(tempvec);
		else
			Answer = AddinMul(Answer, tempvec);
		calccount++; //�������
	}
	vector <char> out;
	out = VecInttoChar(Answer);
	out = InsertPoint(out, Num1decimal + Num2deciaml);
	//ʹ�����ʽ�淶
	if (out[0] == '.')
		out.insert(out.begin(), '0');
	if (out[out.size() - 1] == '.')
		out.push_back('0');
	//ͷȥ��
	if (out.size() >= 2)
	{
		if (out[0] == '0' and out[1] == '0')
			out.erase(out.begin());
	}
	//����
	return out;
}

vector<char> Division(string num1, string num2, int decimal)
{
	//string���ʹ���vector
	vector <char> Num1 = StringtoCharVec(num1);
	vector <char> Num2 = StringtoCharVec(num2);
	//��ȡС��λ��
	int Num1decimal = DecimalPlaces(&Num1[0], Num1.size());
	int Num2deciaml = DecimalPlaces(&Num2[0], Num2.size());
	/*//ȥ0���� 0.56 ��> .56
	if (findpoint(&Num1[0], Num1.size()) != -1 and Num1[0] == '0' and Num1[1] == '.')
		Num1.erase(Num1.begin());
	if (findpoint(&Num2[0], Num2.size()) != -1 and Num2[0] == '0' and Num2[1] == '.')
		Num2.erase(Num2.begin());
	//ȥС������� 78.32 ��> 7832
	if (findpoint(&Num1[0], Num1.size()) != -1)
		Num1.erase(Num1.begin() + findpoint(&Num1[0], Num1.size()));
	if (findpoint(&Num2[0], Num2.size()) != -1)
		Num2.erase(Num2.begin() + findpoint(&Num2[0], Num2.size()));*/
	if (Num1decimal > Num2deciaml)
	{
		if (findpoint(&Num1[0], Num1.size()) != -1)
			Num1.erase(Num1.begin() + findpoint(&Num1[0], Num1.size()));
		Num2 = MovePoint(Num2, Num1decimal);
	}
	if (Num2deciaml > Num1decimal)
	{
		if (findpoint(&Num2[0], Num2.size()) != -1)
			Num2.erase(Num2.begin() + findpoint(&Num2[0], Num2.size()));
		Num1 = MovePoint(Num1, Num2deciaml);
	}
	//�ַ�����ת��������
	vector <int> Number1 = VecChartoInt(Num1);
	vector <int> Number2 = VecChartoInt(Num2);
	//��֤λ��С��������
	int numpoint = 0;
	int moveplace = 0;
	if (Number1.size() < Number2.size())
	{
		moveplace = Number2.size() - Number1.size();
		Number1.insert(Number1.end(), Number2.size() - Number1.size(), 0);
	}

	int Num2size = Number2.size();
	int pos = 0;
	
	vector <int> ans;
	vector <int> temp;

	while (ans.size() <= decimal)
	{
		if (pos == Number1.size())
			numpoint = ans.size();
		int unit = 0;
		if (pos <= Number1.size() - 1)
			temp.push_back(Number1[pos]);
		else
			temp.push_back(0);
		if (Biger(temp, Number2))
		{
			while (Biger(temp, Number2))
			{
				temp = SubinDiv(temp, Number2);
				temp = FilterVecZero(temp);
				unit++;
			}
			ans.push_back(unit);
			pos++;
		}
		else
		{
			ans.push_back(0);
			pos++;
		}
		if (temp.empty() and pos == num2.size() - 1)
			break;
	}
	vector <char> out;
	out = VecInttoChar(ans);
	if (numpoint != 0)
		out.insert(out.begin() + numpoint - moveplace, '.');
	out = FilterZero(out);

	return out;
}
