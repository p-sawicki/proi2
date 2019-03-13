//Author: Piotr Sawicki
#include "vector.h"
Vector::Vector(const unsigned int& d) : DIMENSION(d), inputFail(false) {
	if(DIMENSION){
		data = new double[DIMENSION];
		for(unsigned int i = 0; i < DIMENSION; ++i)
			data[i] = 0.0;
	}
	else
		std::cout << "Vector dimension must be positive.\n";
}
void Vector::outOfBoundsError() const {
	std::cout << "Number must be between 0 and " << DIMENSION - 1 << std::endl;
}
double Vector::getNthValue(const unsigned int& n) const {
	if(n < DIMENSION)
		return data[n];
	outOfBoundsError();
}
void Vector::setNthValue(const unsigned int& n, const double& newValue){
	if(n < DIMENSION)
		data[n] = newValue;
	else
		outOfBoundsError();
}
unsigned int Vector::getDimension() const {
	return DIMENSION;
}
bool Vector::isSameDimension(const Vector& second) const {
	return (DIMENSION == second.DIMENSION);
}
void Vector::incompatibleError() const {
	std::cout << "Both vectors in the operation must be of same dimension.\n";
}
bool Vector::getInputFail() const {
	return inputFail;
}
Vector& Vector::operator=(const Vector& second){
	if(isSameDimension(second))
		for(unsigned int i = 0; i < DIMENSION; ++i)
			data[i] = second.data[i];
	else
		incompatibleError();
	return *this;
}
Vector Vector::operator+(const Vector& second) const {
	Vector temp(DIMENSION);
	if(isSameDimension(second))
		for(unsigned int i = 0; i < DIMENSION; ++i)
			temp.setNthValue(i, data[i] + second.data[i]);
	else
		incompatibleError();
	return temp;
}
Vector& Vector::operator+=(const Vector& second){
	*this = *this + second;
	return *this;
}
Vector Vector::operator-() const {
	Vector temp(DIMENSION);
	for(unsigned int i = 0; i < DIMENSION; ++i)
		temp.setNthValue(i, -1 * data[i]);
	return temp;
}
Vector Vector::operator-(const Vector& second) const {
	Vector temp(DIMENSION);
	temp = *this + -second;
	return temp;
}
Vector& Vector::operator-=(const Vector& second){
	*this += -second;
	return *this;
}
double Vector::operator*(const Vector& second) const {
	double result = 0.0;
	if(isSameDimension(second))
		for(unsigned int i = 0; i < DIMENSION; ++i)
			result += data[i] * second.data[i];
	else
		incompatibleError();
	return result;
}
bool Vector::operator==(const Vector& second) const {
	if(!isSameDimension(second))
		return false;
	for(unsigned int i = 0; i < DIMENSION; ++i)
		if(data[i] != second.data[i])
			return false;
	return true;
}
bool Vector::operator!=(const Vector& second) const {
	return !(*this == second);
}
std::ostream& operator<<(std::ostream& os, const Vector& vect){
	os << "[";
	for(unsigned int i = 0; i < vect.DIMENSION; ++i){
		if(i)
			os << ", ";
		os << vect.data[i];
	}
	os << "]";
	return os;
}
void Vector::incorrectlyFormatedError(){
	std::cout << "Input was not a correct vector. Try [";
	char letter = 'a';
	for(int i = 0; i < DIMENSION; ++i){
		std::cout << letter++;
		if(i == DIMENSION - 1)
			std::cout << "]: ";
		else
			std::cout << ", ";
	}
}
std::istream& operator>>(std::istream& is, Vector& vect){
	std::string input;
	std::getline(is, input);
	std::stringstream inputStream(input);
	char check = 0;
	inputStream >> check;
	vect.inputFail = check != '[';
	Vector temp(vect.DIMENSION);
	for(int i = 0; i < vect.DIMENSION && !vect.inputFail; ++i){
		double number;
		inputStream >> number;
		if(inputStream.fail()){
			vect.inputFail = true;
			break;
		}
		temp.data[i] = number;
		inputStream >> check;
		if(i == vect.DIMENSION - 1)
			vect.inputFail = check != ']';
		else
			vect.inputFail = check != ',' && check != ';';
	}
	if(!vect.inputFail)
		vect = temp;
	else
		vect.incorrectlyFormatedError();
	return is;
}
Vector::~Vector(){
	if(data)
		delete[] data;
}
