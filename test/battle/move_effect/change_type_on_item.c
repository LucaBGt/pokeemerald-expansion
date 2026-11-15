#include "global.h"
#include "test/battle.h"

static uq4_12_t GetSpeciesTypeEffectiveness(enum Type moveType, enum Species species)
{
    enum Type type1 = GetSpeciesType(species, 0);
    enum Type type2 = GetSpeciesType(species, 1);
    uq4_12_t modifier = GetTypeModifier(moveType, type1);

    if (type1 != type2)
        modifier = uq4_12_multiply(modifier, GetTypeModifier(moveType, type2));

    return modifier;
}

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_TECHNO_BLAST) == EFFECT_CHANGE_TYPE_ON_ITEM);
    ASSUME(GetMoveEffectArg_HoldEffect(MOVE_TECHNO_BLAST) == HOLD_EFFECT_DRIVE);
    ASSUME(GetSpeciesTypeEffectiveness(TYPE_FIRE, SPECIES_VENUSAUR) == UQ_4_12(2.0));
    ASSUME(GetSpeciesTypeEffectiveness(TYPE_WATER, SPECIES_CHARIZARD) == UQ_4_12(2.0));
    ASSUME(GetSpeciesTypeEffectiveness(TYPE_ELECTRIC, SPECIES_BLASTOISE) == UQ_4_12(2.0));
    ASSUME(GetSpeciesTypeEffectiveness(TYPE_ICE, SPECIES_DRATINI) == UQ_4_12(2.0));
}

SINGLE_BATTLE_TEST("Techno Blast changes type depending on the drive the user holds")
{
    enum Species species;
    enum Item item;

    PARAMETRIZE { species = SPECIES_CHARIZARD; item = ITEM_DOUSE_DRIVE; }
    PARAMETRIZE { species = SPECIES_BLASTOISE; item = ITEM_SHOCK_DRIVE; }
    PARAMETRIZE { species = SPECIES_VENUSAUR; item = ITEM_BURN_DRIVE; }
    PARAMETRIZE { species = SPECIES_DRATINI; item = ITEM_CHILL_DRIVE; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(item); }
        OPPONENT(species);
    } WHEN {
        TURN { MOVE(player, MOVE_TECHNO_BLAST); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TECHNO_BLAST, player);
        EFFECTIVENESS_SE(opponent, SE_SUPER_EFFECTIVE);
        HP_BAR(opponent);
    }
}

TO_DO_BATTLE_TEST("Judgement changes type depending on the plate the user holds");
TO_DO_BATTLE_TEST("Multi Attack changes type depending on the memory the user holds");

#if MAX_MON_ITEMS > 1
SINGLE_BATTLE_TEST("Techno Blast changes type depending on the drive the user holds (Items)")
{
    u16 species;
    enum Item item;

    PARAMETRIZE { species = SPECIES_CHARIZARD; item = ITEM_DOUSE_DRIVE; }
    PARAMETRIZE { species = SPECIES_BLASTOISE; item = ITEM_SHOCK_DRIVE; }
    PARAMETRIZE { species = SPECIES_VENUSAUR; item = ITEM_BURN_DRIVE; }
    PARAMETRIZE { species = SPECIES_DRATINI; item = ITEM_CHILL_DRIVE; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_PECHA_BERRY, item); }
        OPPONENT(species);
    } WHEN {
        TURN { MOVE(player, MOVE_TECHNO_BLAST); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TECHNO_BLAST, player);
        HP_BAR(opponent);
        MESSAGE("It's super effective!");
    }
}
#endif
