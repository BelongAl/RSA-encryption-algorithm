#include"RSA.h"
#include<time.h>
#include<iostream>
#include<math.h>
#include<fstream>

void RSA::ecrept(const char* filename, const char* fileout)//�������ļ�������ļ���
{
	std::ifstream fin(filename, std::ifstream::binary);//���������ļ������� // ���ն����ƴ�
	std::ofstream fout(fileout, std::ofstream::binary);//��������ļ�������
	if (!fin.is_open())//j����ļ��Ƿ�򿪳ɹ�
	{
		perror("input file open failed");//��û�򿪣�˵������
		return;
	}

	char* buffer = new char[NUMBER];//������������ڽ��ռ���ǰ������
	DataType *bufferOut = new DataType[NUMBER];//������������ڽ��ռ��ܺ������

	while (!fin.eof())
	{
		fin.read(buffer, NUMBER);//��ȡ���ݣ����ֽ�Ϊ��λ��
		int curNum = fin.gcount();//��ȡ���һ������ȡ���������ԣ���ȡ����(�ֽ�)��С��Ϊ��λ��
		for (int i = 0; i < curNum; i++)
		{
			bufferOut[i] = ecrept((DataType)buffer[i], m_key.m_ekey, m_key.m_pkey);//�����ݣ�datatypeΪ��λ�����м���
		}
		fout.write((char*)bufferOut, curNum * sizeof(DataType));//д
	}

	delete[]buffer;
	delete[]bufferOut;

	fin.close();
	fout.close();

}

void RSA::decrept(const char* filename, const char* fileout)//���ļ����н���
{
	std::ifstream fin(filename, std::ifstream::binary);//�����������ļ�����
	std::ofstream fout(fileout, std::ofstream::binary);//����������ļ�����
	if (!fin.is_open())
	{
		perror("file open failed");
		return;
	}

	DataType *buffer = new DataType[NUMBER];//���ܻ�����(����)
	char *bufferOut = new char[NUMBER];//���������

	while (!fin.eof())
	{
		fin.read((char*)buffer, NUMBER * sizeof(DataType));//��ȡ����
		int num = fin.gcount();//��ȡ���ݵĸ��������ֽ�Ϊ��λ��
		num /= sizeof(DataType);//�ĵ��������˼���
		for (int i = 0; i < num; i++)
		{
			bufferOut[i] = (char)decrept(buffer[i], m_key.m_dkey, m_key.m_pkey);//�����ݽ��н���
		}
		fout.write(bufferOut, num);//���
	}

	delete[]buffer;
	delete[]bufferOut;

	fout.close();
	fin.close();
}

void RSA::getKeys()
{
	std::cout << "getPrime()" << std::endl;

	DataType prime1 = getPrime();

	std::cout << "Prime1--finsh: ";
	std::cout << prime1 << std::endl;

	DataType prime2 = getPrime();
	while (prime1 == prime2)
	{
		prime2 = getPrime();
	}

	std::cout << "Prime2--finsh: ";
	std::cout << prime2 << std::endl;
	
	std::cout << "get ORLA: " << std::endl;
	DataType orla = getOrla(prime1, prime2);
	std::cout << "get ORLA--finsh: ";
	std::cout << orla << std::endl;

	std::cout << "get n" << std::endl;
	m_key.m_pkey = getPkey(prime1, prime2);
	std::cout << "get n--finsh: ";
	std::cout << m_key.m_pkey << std::endl;

	std::cout << "get e" << std::endl;
	m_key.m_ekey = getEkey(orla);
	std::cout << "get e--finsh: ";
	std::cout << m_key.m_ekey << std::endl;

	std::cout << "get d" << std::endl;
	m_key.m_dkey = getDkey(orla, m_key.m_ekey);
	std::cout << "get d--finsh: ";
	std::cout << m_key.m_dkey << std::endl;
}


DataType RSA::getPrime()//��������
{
	brdm::mt19937 gen(time(nullptr));
	brdm::uniform_int_distribution<DataType> dist(0, DataType(1) << 300);
	DataType prime;
	while (1)
	{
		prime = dist(gen);
		//std::cout << prime << std::endl;
		if(isPrimeBigInt(prime))
			break;
	}
	return prime;
}

bool RSA::isPrimeBigInt(DataType data)
{
	brdm::mt11213b gen(time(nullptr));
	if (miller_rabin_test(data, 25, gen))
	{
		if (miller_rabin_test((data - 1) / 2, 25, gen));
		{
			return true;
		}
	}
	return false;
}

/*bool RSA::isPrime(DataType data)//�ж��Ƿ�Ϊ����
{
	for (int i = 2; i <= sqrt(data); i++)
	{
		if (data%i == 0)
			return false;
	}
	return true;
}
*/

DataType RSA::getPkey(DataType prime1, DataType prime2)//��n
{
	return prime1 * prime2;
}

DataType RSA::getOrla(DataType prime1, DataType prime2)//��ŷ��
{
	return(prime1 - 1)*(prime2 - 1);
}

DataType RSA::getEkey(DataType orla)//��e//������Կ
{
	brdm::mt19937 gen(time(nullptr));
	brdm::uniform_int_distribution<DataType> dist(2, orla);
	DataType ekey;
	while (1)
	{
		ekey = dist(gen);
		if (ekey > 1 && getGcd(ekey, orla) == 1)
		{
			return ekey;
		}
	}
}

DataType RSA::getDkey(DataType orla, DataType ekey)//��d//������Կ//��չ��ŷ������㷨
{
	DataType x = 0, y = 0;
	exGcd(ekey, orla, x, y);
	return (x%orla + orla) % orla;
/*	DataType dkey = orla / ekey; 
	while (1)
	{
		if ((ekey*dkey) % orla == 1)
		{
			std::cout << "get d--finsh" << std::endl;
			return dkey;
		}
		dkey++;
	}*/
}

DataType RSA::getGcd(DataType data1, DataType data2)//�����Լ��,ŷ������㷨
{
	DataType tmp;
	while (1)
	{
		tmp = data1 % data2;

		if (tmp == 0)
		{
			return data2;
		}
		data1 = data2;
		data2 = tmp;
	}
}

DataType RSA::exGcd(DataType a, DataType b, DataType &x, DataType &y)//�����Լ��,ŷ������㷨����չ
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	DataType gcd = exGcd(b, a%b, x, y);
	DataType x1 = x, y1 = y;
	x = y1;
	y = x1 - a / b * y1;
	return gcd;
}

DataType RSA::ecrept(DataType data, DataType ekey, DataType pkey)//����(ͬ�ඨ��+��������)
{
	DataType Ai = data;
	DataType msgE = 1;

	while (ekey)
	{
		if (ekey & 1)
			msgE = (msgE*Ai) % pkey;
		ekey >>= 1;//ȡ���ڵ�λ
		Ai = (Ai*Ai) % pkey;//�����һλAi�Ĵ�С
	}
	return msgE;
}

DataType RSA::decrept(DataType data, DataType dkey, DataType pkey)//����
{
	return ecrept(data, dkey, pkey);
}
