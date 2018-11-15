#pragma once
#include <vector>
#include <string>
#include <iostream>
enum Sign { positive, negative };
class GodInt
{
private:
	std::vector <int> digits;
	Sign sign;

public:
	GodInt();
	GodInt(int n);
	GodInt(std::string &str);
	void addLSV(int n);
	void addMSV(int n);
	void editDigit(int id, int val);
	int getDigit(int n) const;
	Sign getSign() const;
	int size() const;
	std::string toString() const;
	~GodInt();

	//operators overload

	//STREAMS
	friend std::istream & operator >>(std::istream & in, GodInt & god_int);
	friend std::ostream & operator <<(std::ostream & out, GodInt & god_int);

	//ARITHMETIC
	GodInt & operator +=(const GodInt& rhs);
	//friend GodInt & operator -=(const GodInt&rhs);
	//friend GodInt & operator ++(int);
	//friend GodInt & operator --(int);
	friend GodInt operator+(GodInt lhs, const GodInt& rhs);
	friend GodInt operator+(GodInt lhs, const int& rhs);
	//friend GodInt operator-(const GodInt& rhs);
	//friend GodInt& operator=(const GodInt& rhs);
	//friend GodInt& operator=(const int& rhs);

	//multiplications to be implemented

	//BOOLEAN

	friend bool operator==(const GodInt& lhs, const GodInt& rhs);
	friend bool operator==(const GodInt& lhs, const int& rhs);
	friend bool operator==(const int& lhs, const GodInt& rhs);
	//NEED TO BE IMPLEMENTED
	friend bool operator< (const GodInt& lhs, const GodInt& rhs);
	friend bool operator< (const int& lhs, const GodInt& rhs);
	friend bool operator< (const GodInt& lhs, const int& rhs);
	//////////////////////
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
