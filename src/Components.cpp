#include "Components.hpp"

Health::Health(int health, int maxHealth) : health{health}, maxHealth{maxHealth}
{
    
    

}

void Health::takeDamage(int damage)
{

    health -= damage;
    onDamage.publish();

    if (health <= 0)
    {
        onDeath.publish();
    }

}