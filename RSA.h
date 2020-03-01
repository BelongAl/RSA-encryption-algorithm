/*
	�ļ����ܹ���
	������1��ʹ��ŷ��������ŷ������Ϊ��ѧ����
		  2��

	����  1���õ��������ʵ��� a b����Ϊ������
		  2����n = a * b
		  3������n��ŷ����ʽOL(n)
		  4���õ�һ���������e( 1 < e < OL(n)),e��OL(n)����
		  5�����e��ģ��Ԫ��d ed%OL(n) == 1;
		  6�����ù�Կ(e,n);˽Կ(d,n);
*/

#pragma once

#include<boost/multiprecision/cpp_int.hpp>//����
#include<boost/multiprecision/random.hpp>//�����
#include<boost/multiprecision/miller_rabin.hpp>//����������

#define NUMBER 256
//typedef long DataType;
typedef boost::multiprecision::int1024_t DataType;

namespace brdm = boost::random;

struct Key//��Կ�ṹ
{
	DataType m_ekey;//��Կ
	DataType m_dkey;//˽Կ
	DataType m_pkey;
};

class RSA
{
	Key m_key;

public:

	RSA()
	{
		getKeys();
	}
	void getKeys();

	void ecrept(const char* filename, const char* fileout);//���ļ����м���
	void decrept(const char* filename, const char* fileout);//���ļ����н���

private:

	DataType ecrept(DataType data, DataType ekey, DataType pkey);//����
	DataType decrept(DataType data, DataType dkey, DataType pkey);//����

	Key getallkey()
	{
		return m_key;
	}

	DataType getPrime();//��������
	//bool isPrime(DataType data);//�ж��Ƿ�Ϊ����
	bool isPrimeBigInt(DataType data);
	DataType getPkey(DataType prime1, DataType prime2);//��n
	DataType getOrla(DataType prime1, DataType prime2);//��ŷ��
	DataType getEkey(DataType orla);//��e
	DataType getDkey(DataType orla, DataType ekey);//��d
	DataType getGcd(DataType data1, DataType data2);//�����Լ��
	DataType exGcd(DataType a, DataType b, DataType &x, DataType &y);//�����Լ��,ŷ������㷨����չ
	
};
