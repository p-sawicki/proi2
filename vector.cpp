//Author: Piotr Sawicki
#include "vector.h"
Vector::Vector(const unsigned int& d) : dimension(d), inputFail(false) {
	if(dimension){
		data = new double[dimension];
		for(unsigned int i = 0; i < dimension; ++i)
			data[i] = 0.0;
	}
	else
		std::cout << "Vector dimension must be positive.\n";
}
Vector::Vector() : Vector(1){}
void Vector::outOfBoundsError() const {
	std::cout << "Number must be between 0 and " << dimension - 1 << std::endl;
}
double Vector::getNthValue(const unsigned int& n) const {
	if(n < dimension)
		return data[n];
	outOfBoundsError();
}
void Vector::setNthValue(const unsigned int& n, const double& newValue){
	if(n < dimension)
		data[n] = newValue;
	else
		outOfBoundsError();
}
unsigned int Vector::getDimension() const {
	return dimension;
}
bool Vector::isSameDimension(const Vector& second) const {
	return (dimension == second.dimension);
}
void Vector::incompatibleError() const {
	std::cout << "Both vectors in the operation must be of same dimension.\n";
}
bool Vector::getInputFail() const {
	return inputFail;
}
Vector& Vector::operator=(const Vector& second){
	if(*this == second)
		return *this;
	if(!isSameDimension(second)){
		delete[] data;
		dimension = second.dimension;
		data = new double[dimension];
	}
	for(unsigned int i = 0; i < dimension; ++i)
		data[i] = second.data[i];
	return *this;
}
Vector Vector::operator+(const Vector& second) const {
	Vector temp(dimension);
	if(isSameDimension(second))
		for(unsigned int i = 0; i < dimension; ++i)
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
	Vector temp(dimension);
	for(unsigned int i = 0; i < dimension; ++i)
		temp.setNthValue(i, -1 * data[i]);
	return temp;
}
Vector Vector::operator-(const Vector& second) const {
	Vector temp(dimension);
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
		for(unsigned int i = 0; i < dimension; ++i)
			result += data[i] * second.data[i];
	else
		incompatibleError();
	return result;
}
bool Vector::operator==(const Vector& second) const {
	if(!isSameDimension(second))
		return false;
	for(unsigned int i = 0; i < dimension; ++i)
		if(data[i] != second.data[i])
			return false;
	return true;
}
bool Vector::operator!=(const Vector& second) const {
	return !(*this == second);
}
std::ostream& operator<<(std::ostream& os, const Vector& vect){
	os << "[";
	for(unsigned int i = 0; i < vect.dimension; ++i){
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
	for(int i = 0; i < dimension; ++i){
		std::cout << letter++;
		if(i == dimension - 1)
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
	Vector temp(vect.dimension);
	for(int i = 0; i < vect.dimension && !vect.inputFail; ++i){
		double number;
		inputStream >> number;
		if(inputStream.fail()){
			vect.inputFail = true;
			break;
		}
		temp.data[i] = number;
		inputStream >> check;
		if(i == vect.dimension - 1)
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
