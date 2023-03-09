#include "CollisionBody.hpp"

float CollisionBody::calculateSquare(ref<sf::Shape> shape)
{
    using namespace std::views;

    auto &tr = shape->getTransform();
    auto tmp = iota(0ul, shape->getPointCount()) |
               transform([shape, &tr](auto j)
                         { return tr.transformPoint(shape->getPoint(j)); });
    std::vector<sf::Vector2f> vertexes(tmp.begin(), tmp.end());

    float square = 0;
    for (size_t i = 1; i < vertexes.size(); i++)
    {
        square += vertexes[i].x * (vertexes[i + 1].y - vertexes[i - 1].y);
    }
    square *= 0.5;
    return fabs(square);
}

void CollisionBody::process(sf::Time delta)
{
    body->move(velocity * delta.asSeconds());
}

void CollisionBody::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(*body, states);
}