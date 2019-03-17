//Author: Piotr Sawicki
#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <sstream>
#include <string>
class Vector{
	private:
		unsigned int dimension;
		double * data;
		bool inputFail;
	public:
		Vector(const unsigned int& d);
		Vector();
		void outOfBoundsError() const; 
		double getNthValue(const unsigned int& n) const;
		void setNthValue(const unsigned int& n, const double& newValue);
		unsigned int getDimension() const;
		bool isSameDimension(const Vector& second) const;
		void incompatibleError() const;
		bool getInputFail() const;
		Vector& operator=(const Vector& second);
		Vector operator+(const Vector& second) const;
		Vector& operator+=(const Vector& second);
		Vector operator-() const;
		Vector operator-(const Vector& second) const;
		Vector& operator-=(const Vector& second);
		double operator*(const Vector& second) const;
		bool operator==(const Vector& second) const;
		bool operator!=(const Vector& second) const;
		friend std::ostream& operator<<(std::ostream& os, const Vector& vect);	
		void incorrectlyFormatedError();
		friend std::istream& operator>>(std::istream& is, Vector& vect);
		~Vector();
};
#endif
