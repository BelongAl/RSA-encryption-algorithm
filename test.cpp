#include<iostream>
#include<fstream>
#include<boost/multiprecision/cpp_int.hpp>

#include"bigint.h"
#include"RSA.h"

using namespace std;

/*
void RSAtest1()
{
	RSA rs;
	rs.getKeys();
	Key key = rs.getallkey();
	DataType socurcenumber = 16;
	DataType edata = rs.ecrept(socurcenumber, key.m_ekey, key.m_pkey);
	DataType ddata = rs.decrept(edata, key.m_dkey, key.m_pkey);

	std::cout << socurcenumber << " " << edata << " " << ddata << std::endl;
}
*/


void RSAtest2()
{
	RSA rs;

	rs.ecrept("test.txt", "ecrept.txt");//¼ÓÃÜ
	rs.decrept("ecrept.txt", "decrept.txt");//½âÃÜ

}

/*

void biginttest1()
{
	BigInt b1("12345");
	BigInt b2("25");

	cout << "************* + *************" << endl;
	cout << "b1:" << b1 << "+ b2:" << b2 <<endl;
	cout << 12345 + 25 << endl;
	cout << b1 + b2 << endl;

	cout << "************* - *************" << endl;
	cout << "b1:" << b1 << "- b2:" << b2 << endl;
	cout << 12345 - 25 << endl;
	cout << b1 - b2 << endl;

	cout << "************* * *************" << endl;
	cout << "b1:" << b1 << "* b2:" << b2 << endl;
	cout << 12345 * 25 << endl;
	cout << b1 * b2 << endl;

	cout << "************* / *************" << endl;
	cout << "b1:" << b1 << "/ b2:" << b2 << endl;
	cout << 12345 / 25 << endl;
	cout << b1 / b2 << endl;

	cout << "************* % *************" << endl;
	cout << "b1:" << b1 << "% b2:" << b2 << endl;
	cout << 12345 % 25 << endl;
	cout << b1 % b2 << endl;
}

void testBigInt()
{
	boost::multiprecision::int1024_t c2(1);
	cout << c2*c2 << endl;
	boost::multiprecision::int1024_t cpp1024_t = c2 << 1023;
	cout << "cpp1024_t = " << cpp1024_t << endl;
	for(int i = 0; i < cpp1024_t; i++)
	{ }
}

void testBoostRandom()
{
	boost::random::mt19937 gen(time(NULL));
	boost::random::uniform_int_distribution<DataType> dist(0, DataType(1)<<1023);
	for (int i = 0; i < 10000; i++)
	{
		std::cout << dist(gen) << std::endl;
	}
}
*/

int main()
{
	RSAtest2();
	system("pause");
	return 0;
}