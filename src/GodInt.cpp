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
	//digits.resize(digits.size());
}
GodInt::GodInt(std::string &str)
{
	//@TODO: handle errors in the string parsing

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
		result += std::to_string(digits[i]);
	}

	return result;
}

Sign GodInt::getSign() const {
	return sign;
}

void GodInt::editSign(Sign val)
{
	sign = val;
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

//@TODO optimize this shit please
GodInt operator+(GodInt lhs, const GodInt& rhs) {
	lhs += rhs;
	return lhs;
}
GodInt operator+(GodInt lhs, const int& rhs) {
	lhs += GodInt(rhs);
	return lhs;
}

GodInt operator-(GodInt lhs, const GodInt & rhs)
{
	lhs -= rhs;
	return lhs;
}
GodInt operator-(GodInt lhs, const int & rhs)
{
	lhs -= GodInt(rhs);
	return lhs;
}

GodInt & GodInt::operator += (const GodInt& rhs) {
	int sum;
	int carry = 0;
	int len;

	//take into account the sign
	if (getSign() != rhs.getSign()) {
		//		*this -= (-1 * rhs); //STILL TO BE DEFINED @TODO
		return *this;
	}

	//deal with += this
	if (this == &rhs) {
		//*this *= 2; STILL TO BE DEFINED @TODO
		return *this;
	}

	if (rhs.size() < size())
		len = size();
	else
		len = rhs.size();
	register short i;
	for (i = 0; i < len; i++) {
		int val1 = getDigit(i);
		int val2 = rhs.getDigit(i);
		sum = (carry + (val1 + val2)) % 10;
		carry = (carry + (val1 + val2)) / 10;
		if (i < size())
			editDigit(i, sum);
		else
			addMSV(sum);
	}
	if (carry != 0)
		addMSV(carry);
	return *this;
}
GodInt & GodInt::operator -= (const GodInt& rhs) {
	int res;
	int borrow = 0;

	if (getSign() != rhs.getSign()) {
		//		*this += (-1 * rhs); //STILL TO BE DEFINED @TODO
		return *this;
	}

	if (this == &rhs) {
		*this = 0; //STILL TO BE DEFINED @TODO
		return *this;
	}

	//we have to stack on top the longest number
	//@TODO make this shit efficient
	if (size() < rhs.size()) {
		*this = rhs - (*this);
		if (getSign() == positive)
			editSign(negative);
		else
			editSign(positive);
		return *this;
	}

	//not sure this works
	register short i;
	for (i = 0; i < size(); i++) {
		int val1 = getDigit(i) - borrow;
		borrow = 0;
		int val2 = rhs.getDigit(i);

		if (val1 < val2)
			borrow++;

		res = val1 + 10 * borrow - val2;

		editDigit(i, res);
	}
	//return *this ?????
}

GodInt & GodInt::operator++()
{
	*this += 1;
	return *this;
}

GodInt & GodInt::operator--()
{
	*this -= 1;
	return *this;
}
GodInt & GodInt::operator++(int)
{
	*this += 1;
	return *this;
}

GodInt & GodInt::operator--(int)
{
	*this -= 1;
	return *this;
}

GodInt & GodInt::operator*=(const GodInt & rhs)
{
	Sign final_sign = Sign::positive;
	if (getSign() != rhs.getSign())
		final_sign = Sign::negative;
	return *this;
}

/*GodInt GodInt::operator-()
{
	if (getSign() == positive)
		this->editSign(Sign::negative);
	else
		this->editSign(Sign::positive);
	return *this;
}*/

//SEEMS TO BE WORKING
bool operator==(const GodInt& lhs, const GodInt& rhs) {
	if (lhs.getSign() == rhs.getSign() && lhs.size() == rhs.size()) {
		for (register short i = 0; i < lhs.size(); i++) {
			if (lhs.getDigit(i) != rhs.getDigit(i))
				return false;
		}
		return true;
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
//SEEMS TO BE WORKING
bool operator< (const GodInt& lhs, const GodInt& rhs) {
	if (lhs.size() != rhs.size()) {
		if (lhs.getSign() == rhs.getSign()) {
			if (lhs.getSign() == positive)
				return lhs.size() < rhs.size();
			else
				return lhs.size() > rhs.size();
		}
		else {
			if (lhs.getSign() == positive)
				return false;
			else
				return true;
		}
	}
	else {
		// same size
		for (register short i = lhs.size() - 1; i >= 0; i--) {
			if (lhs.getDigit(i) < rhs.getDigit(i))
				return lhs.getSign() == Sign::positive;
			if (lhs.getDigit(i) > rhs.getDigit(i))
				return lhs.getSign() == Sign::negative;
		}
		if (lhs.getSign() == rhs.getSign())
			return false;
		else
			return lhs.getSign() == Sign::negative;
	}
}
bool operator< (const int& lhs, const GodInt& rhs) {
	return GodInt(lhs) < rhs;
}
bool operator< (const GodInt& lhs, const int& rhs) {
	return lhs < GodInt(rhs);
}

bool operator> (const GodInt& lhs, const GodInt& rhs) {
	return  operator< (rhs, lhs);
}
bool operator> (const int& lhs, const GodInt& rhs) {
	return  operator< (rhs, lhs);
}
bool operator> (const GodInt& lhs, const int& rhs) {
	return  operator< (rhs, lhs);
}
bool operator<=(const GodInt& lhs, const GodInt& rhs) {
	return !operator> (lhs, rhs);
}
bool operator<=(const int& lhs, const GodInt& rhs) {
	return !operator> (lhs, rhs);
}
bool operator<=(const GodInt& lhs, const int& rhs) {
	return !operator> (lhs, rhs);
}
bool operator>=(const GodInt& lhs, const GodInt& rhs) {
	return !operator< (lhs, rhs);
}
bool operator>=(const int& lhs, const GodInt& rhs) {
	return !operator< (lhs, rhs);
}
bool operator>=(const GodInt& lhs, const int& rhs) {
	return !operator< (lhs, rhs);
}
bool operator!=(const GodInt& lhs, const GodInt& rhs) {
	return !operator==(lhs, rhs);
}
bool operator!=(const int& lhs, const GodInt& rhs) {
	return !operator==(lhs, rhs);
}
bool operator!=(const GodInt& lhs, const int& rhs) {
	return !operator==(lhs, rhs);
}