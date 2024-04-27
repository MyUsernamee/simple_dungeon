#include "Systems.hpp"
#include "Components.hpp"
#include "Game.hpp"

void animationSystem(Game* game, double dt) {
    auto& registry = game->getRegistry();
    auto view = registry.view<Animator, Renderable>();
    for (auto entity : view) {
        auto& animator = view.get<Animator>(entity);
        auto& renderable = view.get<Renderable>(entity);

        animator.frameTime += dt;

        if (animator.frameTime >= 1.0f / animator.fps) {
            animator.frameTime = 0;
            animator.currentFrame++;
        }

        animator.currentFrame %= animator.animations[animator.currentAnimation].getFrameCount();
        auto& current_animation = animator.animations[animator.currentAnimation];

         renderable.texture = current_animation.getFrame(animator.currentFrame);

    }
}