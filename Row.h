#ifndef ROW_H
#define ROW_H
#include "Cell.h"

const int CAP_START_ROW = 16;

class Row {
private:
	Cell* cells = nullptr;
	int size = 0;
	int cap = 0;

private:
	void resize();

	void aloc(const int& cap);
	void del();

public:
	Row();
	Row(const int& cap);
	Row(const Row& other);
	Row& operator=(const Row& other);
	~Row();

	void add(const Cell& cell);

	bool find(const std::string& value, const int& index) const;

	void update(const std::string& valueChange, const int& indexChange);

	Cell operator[](const int& index) const;

	void printTypes() const;
	void print() const;

	friend std::ostream& operator<<(std::ostream& os, const Row& other);
	friend std::istream& operator>>(std::istream& is, Row& other);
};
#endif