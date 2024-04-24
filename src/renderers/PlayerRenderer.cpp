
#include "PlayerRenderer.hpp"
#include "Components.hpp"

#include "utils/consts.hpp"

PlayerRenderer::PlayerRenderer(raylib::Color color)
{

    this->color = color;
    this->idleAnimation = Animation("assets/0x72_DungeonTilesetII_v1.7/frames/skelet_idle_anim_f%d.png");
    this->runAnimation = Animation("assets/0x72_DungeonTilesetII_v1.7/frames/skelet_run_anim_f%d.png");

}


void PlayerRenderer::render(const entt::registry &registry, const entt::entity &entity)
{

    auto &transform = registry.get<Position>(entity);
    auto &player = registry.get<Player>(entity);
    auto &velocity = registry.get<Velocity>(entity);
    auto &renderable = registry.get<Renderable>(entity);

    color.a = renderable.opacity;
    
    Texture2D frame;

    if (velocity.velocity.LengthSqr() > 0) {

        frame = runAnimation.getFrame((int)(GetTime() * 12.0) % runAnimation.getFrameCount()); // TODO: Make this a constant / variable

    }
    else {

        frame = idleAnimation.getFrame((int)(GetTime() * 4.0) % idleAnimation.getFrameCount());

    }

    bool flip = velocity.velocity.x < 0;

    if (flip) {

        DrawTexturePro(
            frame,
            Rectangle{0, 0, -(float)frame.width, (float)frame.height},
            Rectangle{transform.position.x, transform.position.y, (float)frame.width * 2, (float)frame.height * 2},
            raylib::Vector2(0, 0),
            0,
            color
        );
    }
    else {

        DrawTextureEx(frame, raylib::Vector2(transform.position.x, transform.position.y), 0, 2, color);

    }

}

void PlayerRenderer::statsRenderer(entt::registry &registry, const entt::entity &entity)
{

    int width = (GetRenderWidth() - PADDING * 2) / 4;
    int height = 50; // TODO: Make this a constant / variable
    int y_offset = GetRenderHeight() - PADDING - height; // TODO: Make this a constant / variable
    int y_end = GetRenderHeight() - PADDING;
    int offset = registry.get<Player>(entity).gamepad + 1;
    int x_end = offset * width + width;
    int x_offset = offset * width;

    auto &player = registry.get<Player>(entity);
    auto &health = registry.get<Health>(entity);

    DrawRectangle(PADDING + offset * width, y_offset, width, height, raylib::Color(125 + player.color.r / 2, 125 + player.color.g / 2, 125 + player.color.b / 2, 255));
    DrawRectangleLines(PADDING + offset * width, y_offset, width, height, raylib::Color(0, 0, 0, 255));
    DrawText(TextFormat("Player %i", player.gamepad + 1), PADDING + offset * width + 10, y_offset + 10, 5, BLACK);

    // Draw the players sprite
    DrawTexturePro(
        idleAnimation.getFrame(0),
        Rectangle{0, 0, (float)idleAnimation.getFrame(0).width, (float)idleAnimation.getFrame(0).height},
        Rectangle{(float)PADDING + offset * width, (float)y_offset + height - PADDING - 8, 16, 16},
        raylib::Vector2(0, 0),
        0,
        player.color
    );

    DrawRectangle(x_end - PADDING - width / 2, y_offset + PADDING, width / 2, 10, raylib::Color(255, 80, 80, 255));
    DrawRectangle(x_end - PADDING - width / 2, y_offset + PADDING, width / 2 * health.health / health.maxHealth, 10, raylib::Color(80, 255, 80, 255));

}