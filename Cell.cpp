#include "Cell.h"

bool Cell::validInteger(const std::string& value) const
{
	if (value[0] != '-' && value[0] != '+'
		&& (value[0] < '0' || value[0] > '9')) return false;

	for (int i = 1; i < value.size(); ++i) {

		if (value[i] < '0' || value[i] > '9') return false;
	}

	return true;
}

bool Cell::validDouble(const std::string& value) const
{
	if (value[0] != '-' && value[0] != '+'
		&& (value[0] < '0' || value[0] > '9')) return false;

	int dotCount = 0;

	for (int i = 1; i < value.size(); ++i) {

		if (value[i] == '.') dotCount++;

		if ((value[i] < '0' || value[i] > '9') && value[i] != '.') return false;

		if (dotCount >= 2) return false;
	}

	if (dotCount == 0) return false;

	return true;
}

bool Cell::validString(const std::string& value) const
{

	int size = value.size();

	if (value[0] != '\"' || value[size - 1] != '\"') return false;

	for (int i = 1; i < size; ++i) {

		if (value[i] == '\\' && (value[i + 1] == '\\' || value[i + 1] == '\"')) 
			i++;
		
		else if (value[i] == '\\' && (value[i + 1] != '\\' || value[i + 1] != '\"')) 
			return false;
	
	}

	return true;
}

Cell::Cell() : value(null), type(null)
{
}

Cell::Cell(const std::string& value, const std::string& type) : value(value), type(type)
{
}

void Cell::setValue(const std::string& value)
{
	if (this->validInteger(value)) {
		this->value = value;
		this->type = integer;
		return;
	}

	if (this->validDouble(value)) {
		this->value = value;
		this->type = doubl;
		return;
	}

	if (this->validString(value)) {
		this->value = value;
		this->type = str;
		return;
	}

	std::cout << "The value: " << value << " is incorrect, changing it to NULL\n";
	this->value = null;
	this->type = null;
}

bool Cell::operator==(const std::string& value)
{
	return this->value == value;
}

std::string Cell::getValue() const
{
	return this->value;
}

void Cell::printType() const
{
	std::cout << this->type << " ";
}

void Cell::print() const
{
	std::cout << this->value << " ";
}

std::ostream& operator<<(std::ostream& os, const Cell& cell)
{
	os << cell.value << "|";

	return os;
}

std::istream& operator>>(std::istream& is, Cell& cell)
{
	char input[MAX_INPUT];
	is.getline(input, MAX_INPUT, '|');
	
	cell.setValue(input);

	return is;
}

