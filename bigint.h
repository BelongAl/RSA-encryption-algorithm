#pragma once
#include<string>
#include<utility>//pair��ͷ�ļ�
#include<iostream>

class BigInt
{
	std::string m_number;

public:
	BigInt(const std::string&num) :
		m_number(num)
	{}

	BigInt(const int num)
	{}

	BigInt() = default;

	BigInt operator+(BigInt &bi);
	BigInt operator-(BigInt &bi);
	BigInt operator*(BigInt &bi);
	BigInt operator/(BigInt &bi);
	BigInt operator%(BigInt &bi);
	friend std::ostream& operator <<(std::ostream &os, const BigInt &bi);

	std::string add(std::string num1, std::string num2);//+
	std::string sub(std::string num1, std::string num2);//-
	std::string mul(std::string num1, std::string num2);//*
	std::pair<std::string, std::string> dev(std::string num1,  std::string num2);///
	bool less(std::string num1, std::string num2);
	//���������
	//�������

};
