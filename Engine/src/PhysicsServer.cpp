#include <cmath>
#include <iterator>
#include <list>
#include <ranges>

#include "Engine.hpp"
#include "PhysicsServer.hpp"
#include "Simplex.hpp"

inline bool PhysicsServer::equal(const float &n1,
                                 const float &n2,
                                 const float eps)
{
    return fabs(n1 - n2) < eps;
}

inline bool PhysicsServer::equal(const sf::Vector3f &v1,
                                 const sf::Vector3f &v2,
                                 const float eps)
{
    return fabs(v1.x - v2.x) < eps and
           fabs(v1.y - v2.y) < eps and
           fabs(v1.z - v2.z) < eps;
}

inline float PhysicsServer::length(const sf::Vector3f &v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline float PhysicsServer::quadlength(const sf::Vector3f &v)
{
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}
sf::Vector3f PhysicsServer::normalized(const sf::Vector3f &v)
{
    auto len = length(v);
    if (fabs(len) < 0.001f)
        return v;

    return {v.x / len, v.y / len, v.z / len};
}
inline float PhysicsServer::dot(const sf::Vector3f &fst,
                                const sf::Vector3f &snd)
{
    return fst.x * snd.x + fst.y * snd.y + fst.z * snd.z;
}

inline sf::Vector3f PhysicsServer::cross(const sf::Vector3f &v1,
                                         const sf::Vector3f &v2)
{
    sf::Vector3f result;

    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;

    return result;
}

inline bool PhysicsServer::oneDirectional(const sf::Vector3f &v1,
                                          const sf::Vector3f &v2)
{
    return dot(v1, v2) > 0;
}

sf::Vector3f PhysicsServer::cornerPoint(ref<CollisionBody> body,
                                        const sf::Vector3f &direction)
{
    using namespace std::views;

    auto &tr = body->body->getTransform();
    auto vertexes3d = iota(0ul, body->body->getPointCount()) |
                      transform([&body, &tr](auto j)
                                { auto vertex2d = tr.transformPoint(body->body->getPoint(j));
                                      return sf::Vector3f{vertex2d.x, vertex2d.y, 0.f}; });

    return *std::ranges::max_element(vertexes3d, [&direction](auto v1, auto v2)
                                     { return dot(v1, direction) <
                                              dot(v2, direction); });
}

sf::Vector3f PhysicsServer::support(ref<CollisionBody> fst,
                                    ref<CollisionBody> snd,
                                    const sf::Vector3f &direction)
{
    const auto &farthestFST = cornerPoint(fst, direction);
    const auto &farthestSND = cornerPoint(snd, -direction);
    return farthestFST - farthestSND;
}

bool update(Simplex &, sf::Vector3f &);

bool PhysicsServer::intersects(ref<CollisionBody> fst,
                               ref<CollisionBody> snd, // I know I could use AABB..
                               Manifold &manifold)     // but its coooler
{
    sf::Vector3f supportPoint = support(fst, snd, {1.f, 0.f, 0.f});

    Simplex simplex;
    simplex.push_front(supportPoint);

    sf::Vector3f direction = -supportPoint;

    while (true)
    {
        supportPoint = support(fst, snd, direction);

        if (equal(supportPoint, {0.f, 0.f, 0.f}))
        {
            manifold = collisionInfo(fst, snd, simplex);
            return true;
        }

        if (!oneDirectional(supportPoint, direction))
            return false;

        simplex.push_front(supportPoint);

        if (update(simplex, direction))
        {
            manifold = collisionInfo(fst, snd, simplex);
            return true;
        }
    }
}

bool PhysicsServer::line(Simplex &simplex,
                         sf::Vector3f &direction)
{
    auto [a, b, _] = simplex.points;

    sf::Vector3f ab = b - a;
    sf::Vector3f ao = -a; // A to Origin

    if (oneDirectional(ab, ao))
        direction = cross(cross(ab, -a), ab);

    else
    {
        simplex = {a};
        direction = ao;
    }

    return false;
}

bool PhysicsServer::triangle(Simplex &simplex,
                             sf::Vector3f &direction)
{
    auto [a, b, c] = simplex.points;

    sf::Vector3f ab = b - a;
    sf::Vector3f ac = c - a;
    sf::Vector3f ao = -a;

    sf::Vector3f abc = cross(ab, ac);
    if (oneDirectional(cross(abc, ac), ao))
    {
        if (oneDirectional(ac, ao))
        {
            simplex = {a, c};
            direction = cross(cross(ac, -a), ac);
        }

        else
        {
            simplex = {a, b};
            return line(simplex, direction);
        }
    }

    else
    {
        if (oneDirectional(cross(ab, abc), ao))
        {
            simplex = {a, b};
            return line(simplex, direction);
        }

        else
            return true;
    }

    return false;
}

bool PhysicsServer::update(Simplex &simplex, sf::Vector3f &direction)
{
    switch (simplex.size)
    {
    case 2:
        return line(simplex, direction);
    case 3:
        return triangle(simplex, direction);
    }

    return false;
}

//////////////////////////////////////////

Manifold PhysicsServer::collisionInfo(ref<CollisionBody> fst,
                                      ref<CollisionBody> snd,
                                      Simplex &simplex)
{
    Manifold result;
    sf::Vector3f supportPoint;
    if (simplex.size == 1)
    {
        auto a = simplex[0];
        supportPoint = support(fst, snd, -a);

        if (!equal(supportPoint, a))
            simplex.push_front(supportPoint);
    }

    if (simplex.size == 2)
    {
        auto [a, b, _] = simplex.points;
        sf::Vector3f ab = b - a;
        sf::Vector3f direction = cross(cross(ab, -a), ab);
        supportPoint = support(fst, snd, direction);

        if (equal(supportPoint, a))
            supportPoint = support(fst, snd, -direction);

        simplex.push_front(supportPoint);
    }

    Edge e;
    while (true)
    {
        e = findClosestEdge(simplex);
        supportPoint = support(fst, snd, e.normal);

        float d = dot(supportPoint, e.normal);

        if (equal(d, e.distance))
        {
            result.normal = {e.normal.x, e.normal.y};
            result.depth = d;//+ 0.001f;
            break;
        }
        else
            simplex.insert(e.index + 1, supportPoint);
    }

    result.fst = fst;
    result.snd = snd;
    return result;
}

Edge PhysicsServer::findClosestEdge(const Simplex &simplex)
{
    Edge result;
    size_t j;
    float minDist = __FLT_MAX__, currDist;
    sf::Vector3f norm, ij;
    for (size_t i = 0; i < simplex.size; ++i)
    {
        j = (i + 1) % simplex.size;
        auto a = simplex[i];
        auto b = simplex[j];
        ij = b - a;

        norm = normalized(cross(cross(ij, a), ij));
        currDist = dot(norm, a);

        if (currDist < minDist)
        {
            minDist = currDist;
            result.b = simplex[i];
            result.a = simplex[j];
            result.normal = norm;
            result.distance = currDist;
            result.index = i;
        }
    }

    return result;
}

void PhysicsServer::collide() // can be much more readable if only Scene will provide iterator by mask
{
    auto scene = Engine::instance().sceneController.currentScene;
    if (!scene)
        return;

    bool is_I_greaterThan_J = true; //
    for (auto it = scene->nodes.begin(); it != scene->nodes.end(); ++it)
    {
        is_I_greaterThan_J = true;
        if (((*it)->mask & SceneNode::MOVEABLE) != SceneNode::MOVEABLE)
            continue;

        for (auto jt = scene->nodes.begin(); jt != scene->nodes.end(); ++jt)
        {
            if (*jt == *it)
            {
                is_I_greaterThan_J = false;
                continue;
            }

            // no sense looking for collision between two walls) + fps
            if (((*jt)->mask & SceneNode::COLLIDABLE) != SceneNode::COLLIDABLE or
                ((((*jt)->mask & Scene::MOVEABLE) == SceneNode::MOVEABLE) and is_I_greaterThan_J)) // to avoid double checking MOVEABLE objects
                continue;

            auto &physicsServer = Engine::instance().physicsServer;
            Manifold manifold;
            if (physicsServer.intersects(std::dynamic_pointer_cast<CollisionBody>(*it),
                                         std::dynamic_pointer_cast<CollisionBody>(*jt),
                                         manifold))
                scene->manifolds.push_back(std::make_shared<Manifold>(manifold));
        }
    }
}