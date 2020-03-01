#include"bigint.h"

BigInt BigInt::operator+(BigInt &bi)
{
	std::string ret = add(m_number, bi.m_number);
	return BigInt(ret);
}
BigInt BigInt::operator-(BigInt &bi)
{
	std::string ret = sub(m_number, bi.m_number);
	return BigInt(ret);
}
BigInt BigInt::operator*(BigInt &bi)
{
	std::string ret = mul(m_number, bi.m_number);
	return BigInt(ret);
}
BigInt BigInt::operator/(BigInt &bi)
{
	std::pair<std::string, std::string> ret = dev(m_number, bi.m_number);
	return BigInt(ret.first);
}
BigInt BigInt::operator%(BigInt &bi)
{
	std::pair<std::string, std::string> ret = dev(m_number, bi.m_number);
	return BigInt(ret.second);
}

std::string BigInt::add(std::string num1, std::string num2)//+
{
	int size = num1.size() > num2.size() ? num1.size() : num2.size();
	std::string add(size,'0');
	if (num1.size() > num2.size())
	{
		num2.insert(0,size-num2.size(),'0');
	}
	else if (num1.size() < num2.size())
	{
		num1.insert(0, size - num1.size(), '0');
	}

	int carry = 0;
	for (int i = size - 1; i >= 0; i--)
	{
		add[i] = (num1[i] - '0') + (num2[i] - '0') + '0' + carry;
		if (add[i] > '9')
		{
			carry = 1;
			add[i] -= 10;
		}
		else
		{
			carry = 0;
		}
	}
	if (carry == 1)
	{
		add.insert(0, 1, '1');
	}

	return add;
}

std::string BigInt::sub(std::string num1, std::string num2)//-
{
	int size = num1.size() > num2.size() ? num1.size() : num2.size();
	std::string res(size, '0');
	if (num1.size() > num2.size())
	{
		num2.insert(0, size - num2.size(), '0');
	}
	else if (num1.size() < num2.size())
	{
		num1.insert(0, size - num1.size(), '0');
	}

	for (int i = size - 1; i >= 0; i--)
	{
		if (num1[i] < num2[i])
		{
			num1[i] += 10;
			num1[i - 1] -= 1;
		}
		res[i] = (num1[i] - '0') - (num2[i] - '0') + '0';	
	}

	while(res.size() > 0 && res[0] == '0'){
		res.erase(0, 1);
	}

	return res;
}

std::string BigInt::mul(std::string num1, std::string num2)//*，借助加法实现
{
	if (num2.size() > num1.size())
	{
		num2.swap(num1);//把小的作为乘数，大的作为被乘数
	}

	std::string ret("0");//保存返回值
	for (int i = num2.size() - 1; i >= 0; i--)
	{
		int mult = num2[i] - '0';
		std::string tmp = num1;


		int carry = 0;//进位

		for (int j = tmp.size() - 1; j >= 0; j--)
		{
			tmp[j] = (tmp[j]-'0') * mult + carry;
			if (tmp[j] > 9)
			{
				carry = tmp[j] / 10;
				tmp[j] = tmp[j] % 10;
			}
			else
			{
				carry = 0;
			}
			tmp[j] += '0';
		}
		if (carry > 0)
		{
			tmp.insert(0, 1, carry + '0');
		}
		tmp.append(num2.size() - 1 - i, '0');

		ret = add(ret, tmp);
	}

	return ret;
}

std::pair<std::string, std::string> BigInt::dev(std::string num1, std::string num2)///;借助减法实现
{
	std::string ret;//商值
	std::string rem(num1);//余数

	int dvalue = num1.size() - num2.size();
	num2.append(dvalue, '0');

	for (int i = 0; i <= dvalue; i++)
	{
		char count = '0';
		while (1)
		{
			if (less(rem, num2))
				break;
			rem = sub(rem, num2);
			count++;
		}
		ret += count;
		//除数减小10
		num2.pop_back();
	}
	//删除前置的0
	while (ret.size() > 1 && ret[0] == '0')
	{
		ret.erase(0, 1);
	}
	return make_pair(ret,rem);


}

bool BigInt::less(std::string num1, std::string num2)
{
	if (num1.size() > num2.size())
		return false;
	else if (num2.size() > num1.size())
		return true;
	else
		return num1 < num2;

}

std::ostream& operator<<(std::ostream &os, const BigInt &bi)
{
	os << bi.m_number;
	return os;
}
