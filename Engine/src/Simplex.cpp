#include "Simplex.hpp"

Simplex::Simplex(std::initializer_list<sf::Vector3f> list)
{
    size = 0;
    for (auto &&p : list)
    {
        points[size++] = p;
        if (size == MAX_SIZE)
            break;
    }
}

Simplex &Simplex::operator=(std::initializer_list<sf::Vector3f> list)
{
    size = 0;
    for (auto &&p : list)
    {
        points[size++] = p;
        if (size == MAX_SIZE)
            break;
    }
    return *this;
}

sf::Vector3f Simplex::operator[](int index) const
{
    return points[index];
}

sf::Vector3f &Simplex::operator[](int index)
{
    return points[index];
}

void Simplex::push_front(sf::Vector3f point)
{
    size_t _size = size;
    *this = {point, points[0], points[1]};
    if (_size < MAX_SIZE)
        size = _size + 1;
}

void Simplex::push_back(sf::Vector3f point)
{
    if (size < MAX_SIZE)
    {
        points[size - 1] = point;
        ++size;
    }
}

void Simplex::insert(const int &pos, sf::Vector3f point)
{
    int i = 0;
    for (i = size - 1; i > pos; --i)
        points[i] = points[i - 1];
    points[i] = point;
    size = (size + 1) % MAX_SIZE;
}