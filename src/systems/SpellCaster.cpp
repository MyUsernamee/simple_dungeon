#include "Game.hpp"

void spellCastSystem(Game* game, double dt) {

    auto& registry = game->getRegistry();

    auto view = registry.view<SpellCaster>();
    for (auto entity : view) {
        auto& spellCaster = view.get<SpellCaster>(entity);

        spellCaster.mana += spellCaster.manaRegen * dt;
    }

};