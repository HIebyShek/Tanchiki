#ifndef PHYSICSSERVER_HPP
#define PHYSICSSERVER_HPP

#include <list>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include "CollisionBody.hpp"
#include "Simplex.hpp"
#include "defines.hpp"

struct Edge
{
    sf::Vector3f a;
    sf::Vector3f b;
    sf::Vector3f normal;
    int index;
    float distance;
};

struct SceneNode;

struct Manifold
{
    ref<CollisionBody> fst;
    ref<CollisionBody> snd;
    sf::Vector2f normal;
    float depth;
};

class PhysicsServer
{
public:
    void collide();

    Manifold collisionInfo(ref<CollisionBody> fst,
                           ref<CollisionBody> snd,
                           Simplex &simplex);

    Edge findClosestEdge(const Simplex &simplex);

    bool update(Simplex &simplex, sf::Vector3f &direction);

    bool line(Simplex &simplex,
                             sf::Vector3f &direction);

    bool triangle(Simplex &simplex,
                  sf::Vector3f &direction);

    bool intersects(ref<CollisionBody> fst,
                    ref<CollisionBody> snd,
                    Manifold &manifold);

    sf::Vector3f support(ref<CollisionBody> fst,
                         ref<CollisionBody> snd,
                         const sf::Vector3f &direction);

    sf::Vector3f cornerPoint(ref<CollisionBody> body,
                             const sf::Vector3f &direction);

    inline bool oneDirectional(const sf::Vector3f &v1,
                               const sf::Vector3f &v2);

    static inline sf::Vector3f cross(const sf::Vector3f &v1,
                                     const sf::Vector3f &v2);

    static inline float dot(const sf::Vector3f &fst,
                            const sf::Vector3f &snd);

    static sf::Vector3f normalized(const sf::Vector3f &v);

    static inline float quadlength(const sf::Vector3f &v);

    static inline float length(const sf::Vector3f &v);

    static inline bool equal(const sf::Vector3f &v1,
                             const sf::Vector3f &v2,
                             const float eps = 0.001f);

    static inline bool equal(const float &n1,
                             const float &n2,
                             const float eps = 0.001f);
};

#endif // PHYSICSSERVER_HPP