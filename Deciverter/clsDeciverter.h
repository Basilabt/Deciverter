#pragma once



#include<iostream>
#include<unordered_map>
#include<string>

// DEC.

class clsDeciverter
{

	private:

		enum enSize {
			Extendable = 1, NotExtendable = 2
		};


		std::unordered_map<std::string, char> _hexMap;

		std::unordered_map<std::string, char> _octalMap;



		std::string _convertToBinary(std::string);

		std::string _convertToHexadecimal(std::string);

		std::string _convertToOctal(std::string);

		
		bool _checkValidInput(std::string);

		bool _isInputDecimalNumber(std::string);

		enSize _checkNumberSize(std::string);

		std::string _extendNumber(std::string);

		std::string _reverse(std::string);


		void _initializeHexMapValues(void);

		void _initializeOctMapValues(void);

	public:

		clsDeciverter();

		~clsDeciverter();

		std::string convertToBinary(std::string);

		std::string convertToHexadecimal(std::string);

		std::string convertToOctal(std::string);

};







// DEF.

clsDeciverter::clsDeciverter() {
	this->_initializeHexMapValues();
	this->_initializeOctMapValues();
}

clsDeciverter::~clsDeciverter() {
	this->_hexMap.clear();
	this->_octalMap.clear();
}



void clsDeciverter::_initializeHexMapValues() {
	this->_hexMap["0000"] = '0';
	this->_hexMap["0001"] = '1';
	this->_hexMap["0010"] = '2';
	this->_hexMap["0011"] = '3';
	this->_hexMap["0100"] = '4';
	this->_hexMap["0101"] = '5';
	this->_hexMap["0110"] = '6';
	this->_hexMap["0111"] = '7';
	this->_hexMap["1000"] = '8';
	this->_hexMap["1001"] = '9';
	this->_hexMap["1010"] = 'A';
	this->_hexMap["1011"] = 'B';
	this->_hexMap["1100"] = 'C';
	this->_hexMap["1101"] = 'D';
	this->_hexMap["1110"] = 'E';
	this->_hexMap["1111"] = 'F';
}

void clsDeciverter::_initializeOctMapValues() {
	this->_octalMap["000"] = '0';
	this->_octalMap["001"] = '1';
	this->_octalMap["010"] = '2';
	this->_octalMap["011"] = '3';
	this->_octalMap["100"] = '4';
	this->_octalMap["101"] = '5';
	this->_octalMap["110"] = '6';
	this->_octalMap["111"] = '7';
}



bool clsDeciverter::_checkValidInput(std::string number) {

	if (number == "") {
		return false;
	}

	return this->_isInputDecimalNumber(number);
}

bool clsDeciverter::_isInputDecimalNumber(std::string number) {

	for (char& c : number) {
		if (!isdigit(c)) {
			return false;
		}
	}

	return true;
}

clsDeciverter::enSize clsDeciverter::_checkNumberSize(std::string number) {

	const short sizeInBits = 32;

	return (number.length() == sizeInBits) ? enSize::NotExtendable : enSize::Extendable;
}

std::string clsDeciverter::_extendNumber(std::string number) {

	enSize result = this->_checkNumberSize(number);

	if (result == enSize::NotExtendable) {
		return number;
	}


	int numberOfExtraBits = 32 - number.length();

	std::string extendedNumber = "";

	while (numberOfExtraBits--) {
		extendedNumber += '0';
	}

	extendedNumber = extendedNumber + number;

	return extendedNumber;
}

std::string clsDeciverter::_reverse(std::string number) {

	int left = 0;
	int right = number.length() - 1;

	while (left < right) {

		char temp = number[left];
		number[left] = number[right];
		number[right] = temp;

		left++;
		right--;
	}

	return number;
}










std::string clsDeciverter::_convertToBinary(std::string number) {
	
	if (!this->_checkValidInput(number)) {
		return "ERROR";
	}


	int numberInDecimal = std::stoi(number);

	std::string answer = "";

	while (numberInDecimal != 0) {
		answer += std::to_string(numberInDecimal % 2);
		numberInDecimal = numberInDecimal / 2;
	}


	return this->_extendNumber(this->_reverse(answer));
}

std::string clsDeciverter::convertToBinary(std::string number) {
	return this->_convertToBinary(number);
}



std::string clsDeciverter::_convertToHexadecimal(std::string number) {

	number = this->convertToBinary(number);


	std::string numberInHex = "";
	std::string nibble = "";

	for (int i = 0; i < number.length(); i++) {

		nibble += number[i];

		if (nibble.length() == 4) {
			numberInHex += this->_hexMap[nibble];
			nibble = "";
		}

	}


	return numberInHex;

}

std::string clsDeciverter::convertToHexadecimal(std::string number) {
	return this->_convertToHexadecimal(number);
}




std::string clsDeciverter::_convertToOctal(std::string number) {

	number = this->convertToBinary(number);

	std::string numberInOctal = "";
	std::string triad = "";


	for (int i = 0; i < number.length(); i++) {

		triad += number[i];

		if (triad.length() == 3) {
			numberInOctal += this->_octalMap[triad];
			triad = "";
		}
	}


	return numberInOctal;

}

std::string clsDeciverter::convertToOctal(std::string number) {
	return this->_convertToOctal(number);
}

