#include "Row.h"

bool Row::find(const std::string& value, const int& index) const
{
    return this->cells[index] == value;
}

void Row::update(const std::string& valueChange, const int& indexChange)
{
    if (indexChange < 0 || indexChange >= this->size) return;

    this->cells[indexChange].setValue(valueChange);
}

void Row::resize()
{
    Cell* newCells = new (std::nothrow) Cell[this->cap * 2];

    if (newCells == nullptr) {
        std::cout << "Failed memory allocation!"; 
        return;
    }

    for (int i = 0; i < this->size; ++i) newCells[i] = this->cells[i];
    
    this->del();

    this->cap *= 2;
    this->cells = newCells;
}

void Row::aloc(const int& cap)
{
    this->cells = new (std::nothrow) Cell[cap];
}

void Row::del()
{
    delete[] this->cells;
}

Row::Row() : cap(CAP_START_ROW), size(0)
{
    this->aloc(this->cap);
}

Row::Row(const int& cap) : cap(cap), size(0)
{
    this->aloc(this->cap);
}

Row::Row(const Row& other) : cap(other.cap), size(other.size)
{
    this->aloc(this->cap);

    for (int i = 0; i < size; ++i) {
        this->cells[i] = other[i];
    }
}

Row& Row::operator=(const Row& other)
{
    if (this != &other) {

        this->del();

        this->size = other.size;
        this->cap = other.cap;
        this->aloc(this->cap);

        for (int i = 0; i < size; ++i) {
            this->cells[i] = other[i];
        }
    }

    return *this;
}

Row::~Row()
{
    this->del();
}

void Row::add(const Cell& cell)
{
    if (this->size == this->cap) this->resize();

    this->cells[this->size] = cell;
    this->size++;
}

Cell Row::operator[](const int& index) const
{
    return this->cells[index];
}

void Row::printTypes() const
{
    for (int i = 0; i < size; ++i) this->cells[i].printType();
   
    std::cout << "\n";
}

void Row::print() const
{
    for (int i = 0; i < this->size; ++i) 
        this->cells[i].print();
    
}

std::ostream& operator<<(std::ostream& os, const Row& other)
{
    os << other.size << " ";
    for (int i = 0; i < other.size; ++i) os << other[i];
    os << "\n";

    return os;
}

std::istream& operator>>(std::istream& is, Row& other)
{
    int count = 0;
    is >> count;
    is.ignore();

    other.del();
    other.size = 0;
    other.cap = count;
    other.aloc(count);

    Cell tempCell;

    for (int i = 0; i < other.cap; ++i) {
        is >> tempCell;
        other.add(tempCell);
    }

    return is;
}
