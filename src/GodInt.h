#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>
#include <cctype>
enum Sign { positive, negative };
//@TODO:
//migrate to char when possible
//alternative solution: use a single integer to store way more than 10 values
//maybe up until 9999 in a single digit

class GodInt
{
private:
	std::vector <std::uint8_t> digits;
	Sign sign = Sign::positive;

public:
	GodInt();
	GodInt(int n);
	GodInt(std::string str);
	GodInt(const char* str);
	void addLSV(std::uint8_t n);
	void addMSV(std::uint8_t n);
	void editDigit(int id, std::uint8_t val);
	std::uint8_t getDigit(int n) const;
	Sign getSign() const;
	void editSign(Sign val);
	int size() const;
	std::string toString() const;
	void clearZeros();
	unsigned long long int toInt();
	~GodInt();

	GodInt multiplyBySingleDigit(short digit);

	//operators overload

	//STREAMS
	friend std::istream & operator >>(std::istream & in, GodInt & god_int);
	friend std::ostream & operator <<(std::ostream & out, GodInt & god_int);

	//ARITHMETIC
	GodInt & operator +=(const GodInt& rhs);
	GodInt & operator +=(const int& rhs);
	GodInt & operator -=(const GodInt&rhs);
	GodInt & operator -=(const int&rhs);
	GodInt & operator ++();
	GodInt & operator --();
	GodInt & operator ++(int);
	GodInt & operator --(int);
	friend GodInt operator+(GodInt lhs, const GodInt& rhs);
	friend GodInt operator+(GodInt lhs, const int& rhs);
	friend GodInt operator-(GodInt lhs, const GodInt& rhs);
	friend GodInt operator-(GodInt lhs, const int& rhs);
	//friend GodInt& operator=(const GodInt& rhs);
	//friend GodInt& operator=(const int& rhs);

	//multiplications to be implemented

	GodInt& operator *=(const GodInt& rhs);
	friend GodInt operator *(GodInt lhs, const GodInt &rhs);
	friend GodInt operator *(GodInt lhs, const int &rhs);

	GodInt operator-();

	//BOOLEAN

	friend bool operator==(const GodInt& lhs, const GodInt& rhs);
	friend bool operator==(const GodInt& lhs, const int& rhs);
	friend bool operator==(const int& lhs, const GodInt& rhs);
	friend bool operator< (const GodInt& lhs, const GodInt& rhs);
	friend bool operator< (const int& lhs, const GodInt& rhs);
	friend bool operator< (const GodInt& lhs, const int& rhs);
	friend bool operator> (const GodInt& lhs, const GodInt& rhs);
	friend bool operator> (const int& lhs, const GodInt& rhs);
	friend bool operator> (const GodInt& lhs, const int& rhs);
	friend bool operator<=(const GodInt& lhs, const GodInt& rhs);
	friend bool operator<=(const int& lhs, const GodInt& rhs);
	friend bool operator<=(const GodInt& lhs, const int& rhs);
	friend bool operator>=(const GodInt& lhs, const GodInt& rhs);
	friend bool operator>=(const int& lhs, const GodInt& rhs);
	friend bool operator>=(const GodInt& lhs, const int& rhs);
	friend bool operator!=(const GodInt& lhs, const GodInt& rhs);
	friend bool operator!=(const int& lhs, const GodInt& rhs);
	friend bool operator!=(const GodInt& lhs, const int& rhs);
};
