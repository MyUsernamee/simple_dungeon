#include "Spell.hpp"
#include "Components.hpp"
#include <utils/TextureCache.hpp>
#include "Spells.hpp"

std::vector<Spell> loadSpells()
{
    
    std::vector<Spell> spells;

    // Fireball
    Spell fireball;
    fireball.manaCost = 10;
    fireball.projectile = {
        0,
        600,
        1000,
        {0.0, 0.0} // This is the direction, it will be set when the spell is cast
    };
    fireball.projectileTexture = LoadTextureCached("assets/particles/up.png");
    fireball.spellTexture = LoadTextureCached("assets/spells/fireball.png");
    fireball.castDirections = {CastDirection::UP, CastDirection::RIGHT, CastDirection::DOWN, CastDirection::LEFT};
    fireball.cast_on_death = false;
    fireball.castFunction = castFireball;
    spells.push_back(fireball);

    return spells;

}