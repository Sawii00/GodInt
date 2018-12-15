#include "GodInt.h"
#include <cmath>

GodInt::GodInt()
	:sign(positive)
{
	digits.push_back(0);
}
GodInt::GodInt(int n)
{
	sign = n >= 0 ? positive : negative;
	n = n < 0 ? n * -1 : n;
	int rest = n % 10;

	digits.reserve(10);
	if (n == 0)
		digits.push_back(0);
	while (n != 0) {
		n = n / 10;
		digits.push_back(rest);
		rest = n % 10;
	}
	digits.resize(digits.size());
}
GodInt::GodInt(std::string str)
{
	digits.reserve(str.size());
	for (register int i = str.size() - 1; i >= 0; i--)
	{
		char & ch = str[i];
		if (ch != '+' && ch != '-' && isdigit(ch))
			//trick to retrieve the correct integer and not the ascii value
			digits.push_back(ch - '0');
		else if (ch == '-')
			sign = negative;
		else if (ch == '+')
			sign = positive;
		else
			throw "This is not an integer!!!";
		//it throws an error if parsing characters instead of digits
	}
}

GodInt::GodInt(const char * str) : GodInt(std::string(str))
{
}

GodInt::GodInt(const GodInt &rhs)
{
	std::cout << "Copied\n";
	for (register int i = 0; i < rhs.size(); i++) {
		addMSV(rhs.getDigit(i));
	}
}
void GodInt::clear() {
	digits.clear();
	sign = Sign::positive;
}

void GodInt::addLSV(std::uint8_t n)
{
	digits.insert(digits.begin(), n);
}

void GodInt::addMSV(std::uint8_t n)
{
	digits.push_back(n);
}
//return the digit at the specified index.... if the index is invalid, 0 is returned
std::uint8_t GodInt::getDigit(int n) const
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
	if (digits.size() == 0)return "0";
	if (sign == negative)result += '-';
	for (register int i = digits.size() - 1; i >= 0; i--)
	{
		result += std::to_string(digits[i]);
	}

	return result;
}
GodInt GodInt::pow(GodInt & lhs, int n)
{
	GodInt result(lhs);
	for (register int i = 0; i < n; i++) {
		result *= lhs;
	}
	return result;
}
//DONT THINK THIS IS USEFUL AT ALL
GodInt GodInt::pow(GodInt & lhs, GodInt & rhs)
{
	return GodInt(0);
}

void GodInt::clearZeros()
{
	for (register int i = size() - 1; getDigit(i) == 0; i--) {
		digits.pop_back();
	}
}

unsigned long long int GodInt::toInt()
{
	//only if size is less than 18
	if (size() < 18) {
		int result = 0;
		for (int i = 0; i < size(); i++)
		{
			result += getDigit(i)*(int(std::pow(10.0, i)));
		}
		return result;
	}
	else {
		throw "The number you are converting is too big for an ULLI";
	}
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

void GodInt::editDigit(int id, std::uint8_t val) {
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
	std::uint8_t sum;
	std::uint8_t carry = 0;
	int len;

	//take into account the sign
	if (getSign() != rhs.getSign()) {
		*this -= (-1 * rhs);
		return *this;
	}

	//deal with += this
	if (this == &rhs) {
		*this *= 2;
		return *this;
	}

	if (rhs.size() < size())
		len = size();
	else
		len = rhs.size();
	register long i;
	for (i = 0; i < len; i++) {
		std::uint8_t val1 = getDigit(i);
		std::uint8_t val2 = rhs.getDigit(i);
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
GodInt & GodInt::operator+=(const int & rhs)
{
	GodInt rhs_(rhs);
	return (*this += rhs_);
}
GodInt & GodInt::operator -= (const GodInt& rhs) {
	std::int8_t res;
	std::uint8_t borrow = 0;

	if (getSign() != rhs.getSign()) {
		*this += (-1 * rhs);
		return *this;
	}

	if (this == &rhs) {
		*this = 0;
		return *this;
	}

	//we have to stack on top the longest number
	//@TODO make this shit efficient
	if (*this < rhs) {
		*this = rhs - (*this);
		if (getSign() == positive)
			editSign(negative);
		else
			editSign(positive);
		return *this;
	}

	for (register long i = 0; i < size(); i++) {
		res = getDigit(i) - rhs.getDigit(i) - borrow;
		borrow = 0;
		if (res < 0) {
			res += 10;
			borrow = 1;
		}
		editDigit(i, res);
	}
	clearZeros();
	return *this;
}

GodInt & GodInt::operator-=(const int & rhs)
{
	GodInt rhs_(rhs);
	return (*this -= rhs_);
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
GodInt operator*(GodInt lhs, const GodInt & rhs)
{
	return lhs *= rhs;
}

GodInt operator*(GodInt lhs, const int & rhs)
{
	return lhs *= GodInt(rhs);
}

GodInt GodInt::multiplyBySingleDigit(short digit)
{
	//ONLY USE WITH 1-DIGIT NUMBERSSSSSSSSSSSSSSSSSS AND POSITIVE ONES
	if (digit <= 0 || digit / 10 != 0)throw"Error, only use with 1-digit positive numbers";
	int res = 0;
	for (int i = 0; i < size(); i++)
	{
		res += getDigit(i) * digit * int(std::pow(10.0, i));
	}
	return GodInt(res);
}

GodInt & GodInt::operator *=(const int n) {
	int carry = 0;
	int product;
	if (n == 0) {
		*this = 0;
		return *this;
	}
	if (n == 1) {
		return *this;
	}

	if (n < 0 && getSign() == Sign::positive) {
		editSign(Sign::negative);
	}
	else if (n < 0 && getSign() == Sign::negative) {
		editSign(Sign::positive);
	}

	for (register int i = 0; i < size(); i++)
	{
		product = std::abs(n) * getDigit(i) + carry;
		carry = product / 10;
		editDigit(i, product % 10);
	}
	while (carry != 0) {
		addMSV(carry % 10);
		carry /= 10;
	}
	return *this;
}

//STUPID ASS VERSION
GodInt & GodInt::operator*=(const GodInt & rhs)
{
	if (getSign() != rhs.getSign())
		this->editSign(Sign::negative);
	GodInt sum(0);
	int len = rhs.size();
	for (register int k = 0; k < len; k++) {
		sum += this->multiplyBySingleDigit(rhs.getDigit(k));
		(*this) *= 10;
	}
	*this = sum;
	return *this;
}

GodInt GodInt::operator-()
{
	if (getSign() == positive)
		editSign(Sign::negative);
	else
		editSign(Sign::positive);
	return *this;
}

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
		for (register long i = lhs.size() - 1; i >= 0; i--) {
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

#if 0
//utilities
GodInt GodInt::range_prod(GodInt low, GodInt high) {
	if ((low + 1) < high) {
		ulli mid = (high + low) / 2;
		return range_prod(low, mid) * range_prod(mid + 1, high);
	}
	if (low == high) {
		return low;
	}
	return (low * high);
}

GodInt GodInt::factorial(long long int n) {
	if (n < 2)return GodInt(1);
	return GodInt::range_prod(1, n);
}

GodInt GodInt::fibonacci(long long int n) {
	return GodInt(0);
}

#endif