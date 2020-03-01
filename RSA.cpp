#include"RSA.h"
#include<time.h>
#include<iostream>
#include<math.h>
#include<fstream>

void RSA::ecrept(const char* filename, const char* fileout)//（输入文件，输出文件）
{
	std::ifstream fin(filename, std::ifstream::binary);//构建输入文件流对象 // 按照二进制打开
	std::ofstream fout(fileout, std::ofstream::binary);//构建输出文件流对象
	if (!fin.is_open())//j检查文件是否打开成功
	{
		perror("input file open failed");//若没打开，说明错误
		return;
	}

	char* buffer = new char[NUMBER];//这个缓冲区用于接收加密前的数据
	DataType *bufferOut = new DataType[NUMBER];//这个缓冲区用于接收加密后的数据

	while (!fin.eof())
	{
		fin.read(buffer, NUMBER);//读取数据（以字节为单位）
		int curNum = fin.gcount();//获取最近一次所读取的数量（以（读取类型(字节)大小）为单位）
		for (int i = 0; i < curNum; i++)
		{
			bufferOut[i] = ecrept((DataType)buffer[i], m_key.m_ekey, m_key.m_pkey);//对数据（datatype为单位）进行加密
		}
		fout.write((char*)bufferOut, curNum * sizeof(DataType));//写
	}

	delete[]buffer;
	delete[]bufferOut;

	fin.close();
	fout.close();

}

void RSA::decrept(const char* filename, const char* fileout)//对文件进行解密
{
	std::ifstream fin(filename, std::ifstream::binary);//构建输入流文件对象
	std::ofstream fout(fileout, std::ofstream::binary);//构建输出流文件对象
	if (!fin.is_open())
	{
		perror("file open failed");
		return;
	}

	DataType *buffer = new DataType[NUMBER];//解密缓冲区(输入)
	char *bufferOut = new char[NUMBER];//输出缓冲区

	while (!fin.eof())
	{
		fin.read((char*)buffer, NUMBER * sizeof(DataType));//读取数据
		int num = fin.gcount();//读取数据的个数（以字节为单位）
		num /= sizeof(DataType);//的到真正读了几个
		for (int i = 0; i < num; i++)
		{
			bufferOut[i] = (char)decrept(buffer[i], m_key.m_dkey, m_key.m_pkey);//对数据进行解密
		}
		fout.write(bufferOut, num);//输出
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


DataType RSA::getPrime()//产生素数
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

/*bool RSA::isPrime(DataType data)//判断是否为素数
{
	for (int i = 2; i <= sqrt(data); i++)
	{
		if (data%i == 0)
			return false;
	}
	return true;
}
*/

DataType RSA::getPkey(DataType prime1, DataType prime2)//求n
{
	return prime1 * prime2;
}

DataType RSA::getOrla(DataType prime1, DataType prime2)//求欧拉
{
	return(prime1 - 1)*(prime2 - 1);
}

DataType RSA::getEkey(DataType orla)//求e//加密密钥
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

DataType RSA::getDkey(DataType orla, DataType ekey)//求d//解密密钥//扩展的欧几里得算法
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

DataType RSA::getGcd(DataType data1, DataType data2)//求最大公约数,欧几里得算法
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

DataType RSA::exGcd(DataType a, DataType b, DataType &x, DataType &y)//求最大公约数,欧几里得算法的扩展
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

DataType RSA::ecrept(DataType data, DataType ekey, DataType pkey)//加密(同余定理+恒幂运算)
{
	DataType Ai = data;
	DataType msgE = 1;

	while (ekey)
	{
		if (ekey & 1)
			msgE = (msgE*Ai) % pkey;
		ekey >>= 1;//取存在的位
		Ai = (Ai*Ai) % pkey;//求出下一位Ai的大小
	}
	return msgE;
}

DataType RSA::decrept(DataType data, DataType dkey, DataType pkey)//解密
{
	return ecrept(data, dkey, pkey);
}
