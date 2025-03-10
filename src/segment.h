#pragma once
#include "circlesolver.h"

class SegmentSolver {

public:
    typedef struct Segment {
    CircleObject *obj1;
    CircleObject *obj2;
    float target_distance;
    } Segment;

    void SpawnLink(int pos1, int pos2, float distance);
    void SpawnVerletObject(sf::Vector2f position, float radius, sf::Color color);
    void SpawnVerletObjectStatic(sf::Vector2f position, float radius, sf::Color color);
    void SpawnStructureRope(sf::Vector2f pos, int numJoints, float distance,
            float radius, Anchoring anchoring, sf::Color color);
    void SpawnVerletObjectNonColliding(sf::Vector2f pos, float rad, sf::Color color);
    void Draw(sf::RenderWindow& window);
    void UpdateRope();
    void ApplyLinks();
    bool GetRopeState();
    void ClearRope();
    void SpawnStructureCloth(sf::Vector2f pos, int numOfSideJoints, float distance, float rad, sf::Color color);
    int XYToNum(int x, int y, int width);
    void applyBorders();
    void Attract(sf::Vector2f pos);

private:
    std::vector<Segment> segments;
    std::vector<CircleObject> objects;

    int numOfSegments = 0;
    int numOfObjects = 0;
};
