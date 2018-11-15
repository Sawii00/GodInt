#include "GodInt.h"

GodInt::GodInt()
	:sign(positive)
{
	digits.push_back(0);
}
GodInt::GodInt(int n)
{
	sign = n > 0 ? positive : negative;
	n = n < 0 ? n * -1 : n;
	int rest = n % 10;

	digits.reserve(10);

	while (n != 0) {
		n = n / 10;
		digits.push_back(rest);
		rest = n % 10;
	}
	digits.resize(digits.size());
}
GodInt::GodInt(std::string &str)
{
	//TODO: handle errors in the string parsing

	digits.reserve(str.size());
	for (register int i = str.size() - 1; i >= 0; i--)
	{
		char & ch = str[i];
		if (ch != '+' && ch != '-')
			//trick to retrieve the correct integer and not the ascii value
			digits.push_back(ch - '0');
		else if (ch == '-')
			sign = negative;
		else
			sign = positive;
	}
}

void GodInt::addLSV(int n)
{
	digits.insert(digits.begin(), n);
}

void GodInt::addMSV(int n)
{
	digits.push_back(n);
}
//return the digit at the specified index.... if the index is invalid, 0 is returned
int GodInt::getDigit(int n) const
{
	if (n >= 0 && n < digits.size())
		return digits[n];
	else
		return 0;
}

int GodInt::size() const
{
	return digits.size();
}

std::string GodInt::toString() const
{
	std::string result;
	if (sign == negative)result += '-';
	for (register int i = digits.size() - 1; i >= 0; i--)
	{
		//TODO: FIX THIS SHIT PLEASEEEEE
		//if (i < 0 || i>digits.size())break;
		result += std::to_string(digits[i]);
	}

	return result;
}

Sign GodInt::getSign() const {
	return sign;
}

GodInt::~GodInt()
{
}

void GodInt::editDigit(int id, int val) {
	if (id < digits.size() && id >= 0)
		digits[id] = val;
}

//operators

std::istream & operator >>(std::istream & in, GodInt & god_int)
{
	std::string input;
	in >> input;
	god_int = GodInt(input);
	return in;
}
std::ostream & operator <<(std::ostream & out, GodInt & god_int)
{
	out << god_int.toString();
	return out;
}

GodInt operator+(GodInt lhs, const GodInt& rhs) {
	return GodInt();
}
GodInt operator+(GodInt lhs, const int& rhs) {
	return operator+(lhs, GodInt(rhs));
}

GodInt & GodInt::operator += (const GodInt& rhs) {
	int sum;
	int carry = 0;
	int len;

	//take into account the sign
	if (getSign() != rhs.getSign()) {
		//*this -= rhs*(-1); STILL TO BE DEFINED
		return *this;
	}

	//deal with += this
	if (this == &rhs) {
		//*this *= 2; STILL TO BE DEFINED
		return *this;
	}

	if (rhs.size() < size())
		len = size();
	else
		len = rhs.size();
	register short i;
	for (i = 0; i < len; i++) {
		sum = carry + (getDigit(i) + rhs.getDigit(i)) % 10;
		carry = int(getDigit(i) + rhs.getDigit(i)) / 10;
		if (i < size())
			editDigit(i, sum);
		else
			addMSV(sum);
	}
	if (carry != 0)
		addMSV(carry);
	return *this;
}

bool operator==(const GodInt& lhs, const GodInt& rhs) {
	if (lhs.getSign() == rhs.getSign()) {
		return lhs.toString() == rhs.toString();
	}
	else {
		return false;
	}
}
bool operator==(const int& lhs, const GodInt& rhs) {
	if ((lhs > 0 && rhs.getSign() == positive) || (lhs < 0 && rhs.getSign() == negative)) {
		return std::to_string(lhs) == rhs.toString();
	}
	else {
		return false;
	}
}
bool operator==(const GodInt& lhs, const int& rhs) {
	if ((rhs > 0 && lhs.getSign() == positive) || (rhs < 0 && lhs.getSign() == negative)) {
		return std::to_string(rhs) == lhs.toString();
	}
	else {
		return false;
	}
}

bool operator< (const GodInt& lhs, const GodInt& rhs) {
	//TO BE IMPLEMENTED
	return false;
}
bool operator< (const int& lhs, const GodInt& rhs) {
	//TO BE IMPLEMENTED
	return false;
}
bool operator< (const GodInt& lhs, const int& rhs) {
	//TO BE IMPLEMENTED
	return false;
}

bool operator> (const GodInt& lhs, const GodInt& rhs) { return  operator< (rhs, lhs); }
bool operator> (const int& lhs, const GodInt& rhs) { return  operator< (rhs, lhs); }
bool operator> (const GodInt& lhs, const int& rhs) { return  operator< (rhs, lhs); }
bool operator<=(const GodInt& lhs, const GodInt& rhs) { return !operator> (lhs, rhs); }
bool operator<=(const int& lhs, const GodInt& rhs) { return !operator> (lhs, rhs); }
bool operator<=(const GodInt& lhs, const int& rhs) { return !operator> (lhs, rhs); }
bool operator>=(const GodInt& lhs, const GodInt& rhs) { return !operator< (lhs, rhs); }
bool operator>=(const int& lhs, const GodInt& rhs) { return !operator< (lhs, rhs); }
bool operator>=(const GodInt& lhs, const int& rhs) { return !operator< (lhs, rhs); }
bool operator!=(const GodInt& lhs, const GodInt& rhs) { return !operator==(lhs, rhs); }
bool operator!=(const int& lhs, const GodInt& rhs) { return !operator==(lhs, rhs); }
bool operator!=(const GodInt& lhs, const int& rhs) { return !operator==(lhs, rhs); }