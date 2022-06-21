#ifndef CELL_H
#define CELL_H
#include <string>
#include <iostream>

const int MAX_INPUT = 1024;

const std::string integer = "Integer";
const std::string doubl = "Double";
const std::string str = "String";
const std::string null = "NULL";

class Cell {
private:
	std::string value;
	std::string type;

private:
	bool validInteger(const std::string& value) const;
	bool validDouble(const std::string& value) const;
	bool validString(const std::string& value) const;

public:
	Cell();
	Cell(const std::string& value, const std::string& type);

	bool operator==(const std::string& value);

	std::string getValue() const;

	void setValue(const std::string& value);

	void printType() const;
	void print() const;

	friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
	friend std::istream& operator>>(std::istream& is, Cell& cell);
};
#endif