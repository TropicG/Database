#ifndef DATABASE_H
#define DATABASE_H
#include "Table.h"

const int CAP_TABLE_START = 32;

class Database {
private:
	Table* tables = nullptr;
	int size = 0;
	int cap = 0;

private:
	bool inside(const std::string& name) const;

	int getLocOfTable(const std::string& name) const;

	void resize();

	void cpy(const Database& other);

	void aloc(const int& cap);
	void del();

public:
	Database();
	Database(const std::string& filename);
	Database(const Database& other);
	Database& operator=(const Database& other);
	~Database();

	void addCollum(const std::string name);

	void update(const std::string name,
		const int& searchIndex, const std::string& searchValue,
		const int& changeIndex, const std::string& changeValue
	);

	void select(const int& index, std::string& value, std::string& name) const;

	void dlt(const std::string name, const int& index, const std::string& value);

	void rename(const std::string& oldName,const std::string& newName);

	int count(const std::string& name, const int& index, const std::string& value) const;

	void import(const Table& table);

	void exprt(const std::string& name, const std::string& filename) const;

	void showtables() const;

	void print(const std::string& name) const;

	void describe(const std::string& name) const;

	friend std::ostream& operator<<(std::ostream& os, const Database& database);
	friend std::istream& operator>>(std::istream& is, Database& database);
};
#endif