#ifndef TABLE_H
#define TABLE_H
#include "Row.h"
#include <fstream>
#include <vector>

const int CAP_START_TABLE = 16;

class Table {
private:

	std::string name = "";
	std::string filename = "";

	Row* rows = nullptr;
	int size = 0;
	int cap = 0;

private:
	void resize();

	void cpy(const Table& other);

	void aloc(const int& cap);
	void del();

public:
	Table();
	Table(const std::string& failname);
	Table(const Table& other);
	Table& operator=(const Table& other);
	~Table();

	void add(const Row& row);

	void select(const int& index, std::string& value) const;
	void update(const int& indexFind, const std::string& valueFind, const int& indexChange, const std::string& valueChange);
	void deleteRow(const int& index, const std::string& value);

	void addCollum();

	int count(const int& index, const std::string& value) const;

	void exprt(const std::string& filename) const;

	Row operator[](const int& index) const;
	std::string getName() const;

	void setName(const std::string& name);

	void printTypes() const;
	void print() const;

	friend std::ostream& operator<<(std::ostream& os, const Table& table);
	friend std::istream& operator>>(std::istream& is, Table& table);

};
#endif