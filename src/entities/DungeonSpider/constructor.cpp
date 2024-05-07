#include "constructor.hpp"
#include "entities/DungeonSpider/DungeonSpider.hpp"


entt::entity createDungeonSpider(entt::registry & registry, raylib::Vector2 position)
{

    auto entity = registry.create();

    registry.emplace<Position>(entity, position);
    registry.emplace<Velocity>(entity, raylib::Vector2{0, 0});
    registry.emplace<AI>(entity);
    registry.emplace<Renderable>(entity, LoadTexture("assets/particles/up.png"), raylib::Color{255, 255, 255, 255});
    registry.emplace<Size>(entity, raylib::Vector2{32, 32});
    registry.emplace<Collision>(entity, 0b11);
    registry.emplace<Health>(entity, 10, 10);

    auto idleAnimation = Animation("assets/Spider/Spider%d.png");
    auto walkAnimation = Animation("assets/Spider/Spider%d.png");                                                                                                                                       

    std::vector<Animation> animations = {idleAnimation, walkAnimation};

    registry.emplace<Animator>(entity, animations);

    auto &ai = registry.get<AI>(entity);
    ai.brain = new DungeonSpider();

    return entity;

}