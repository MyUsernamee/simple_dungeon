#include "Spell.hpp"
#include "Components.hpp"
#include <utils/TextureCache.hpp>
#include "Spells.hpp"

std::vector<Spell> loadSpells()
{
    
    std::vector<Spell> spells;

    // Load the fireball spell
    Spell fireball;
    fireball.manaCost = 10;
    fireball.texture = TextureCache::getTexture("assets/spells/fireball.png");
    fireball.cast = castFireball;
    spells.push_back(fireball);

    // Load the ice spell
    Spell ice;
    ice.manaCost = 10;
    ice.texture = TextureCache::getTexture("assets/spells/ice.png");
    ice.cast = castIce;
    spells.push_back(ice);

    return spells;

}