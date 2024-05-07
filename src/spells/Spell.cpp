#include "Spell.hpp"
#include "Components.hpp"
#include <utils/TextureCache.hpp>
#include "spells/ProjectileSpell.hpp"
#include "Spells.hpp"
#include "Game.hpp"

#include <entt/entt.hpp>

using namespace entt::literals; // TODO: REMOVE ME PLEASE

void SpellCaster::cast(Game * game, entt::entity entity, raylib::Vector2 direction, entt::id_type spellId)
{

    auto &registry = game->getRegistry();
    auto &spellCache = game->getSpellCache();

    auto spell = *spellCache[spellId];

    if (mana < spell->manaCost)
    {
        return;
    }

    mana -= spell->manaCost;

    auto &position = registry.get<Position>(entity);
    auto &size = registry.get<Size>(entity);

    spell->cast(game, entity, direction);

}

void loadSpells(Game* game)
{

    // Basic spell
    auto basicSpell = new SimpleDamageSpell();
    basicSpell->manaCost = 1;
    basicSpell->castDelay = 0.1;
    basicSpell->castCooldown = 0.1;
    basicSpell->projectileSpeed = 1000.0;
    basicSpell->projectileSize = 8.0;
    basicSpell->projectileLifetime = 2.0;
    basicSpell->projectileDamage = 1.0;
    game->getSpellCache().load("basic"_hs, basicSpell);

}