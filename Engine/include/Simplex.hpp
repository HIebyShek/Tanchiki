#ifndef SIMPLEX_HPP
#define SIMPLEX_HPP

#include <SFML/System/Vector3.hpp>
#include <cstddef>
#include <initializer_list>

struct Simplex
{
    static const size_t MAX_SIZE = 3;
    sf::Vector3f points[MAX_SIZE];
    size_t size;

    Simplex(std::initializer_list<sf::Vector3f> list);

    Simplex() : points(), size(0) {}

    Simplex &operator=(std::initializer_list<sf::Vector3f> list);

    sf::Vector3f &operator[](int index);

    sf::Vector3f operator[](int index) const;

    void push_front(sf::Vector3f point);

    void push_back(sf::Vector3f point);

    void insert(const int &pos, sf::Vector3f point);
};

#endif // SIMPLEX_HPP