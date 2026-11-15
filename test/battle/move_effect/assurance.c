#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_ASSURANCE) == EFFECT_ASSURANCE);
}

DOUBLE_BATTLE_TEST("Assurance doubles in power if False Swipe connected but didn't do any damage")
{
    s16 hits[2];

    GIVEN {
        ASSUME(GetMoveEffect(MOVE_FALSE_SWIPE) == EFFECT_FALSE_SWIPE);
        ASSUME(GetMoveEffect(MOVE_RECOVER) == EFFECT_RESTORE_HP);
        PLAYER(SPECIES_WOBBUFFET) { HP(1); }
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponentLeft, MOVE_ASSURANCE, target: playerRight); }
        TURN {
            MOVE(opponentLeft, MOVE_FALSE_SWIPE, target: playerLeft);
            MOVE(playerLeft, MOVE_RECOVER);
            MOVE(opponentRight, MOVE_ASSURANCE, target: playerLeft);
        }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ASSURANCE, opponentLeft);
        HP_BAR(playerRight, captureDamage: &hits[0]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FALSE_SWIPE, opponentLeft);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ASSURANCE, opponentRight);
        HP_BAR(playerLeft, captureDamage: &hits[1]);
    } THEN {
        EXPECT_MUL_EQ(hits[0], Q_4_12(2.0), hits[1]);
    }
}

DOUBLE_BATTLE_TEST("Assurance does not double in power if the target's damage is blocked by Substitute")
{
    s16 hits[2];

    GIVEN {
        ASSUME(GetMoveEffect(MOVE_SUBSTITUTE) == EFFECT_SUBSTITUTE);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_HOPPIP) { Ability(ABILITY_INFILTRATOR); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponentLeft, MOVE_ASSURANCE, target: playerLeft); }
        TURN {
            MOVE(playerLeft, MOVE_SUBSTITUTE);
            MOVE(opponentRight, MOVE_POUND, target: playerLeft);
            MOVE(opponentLeft, MOVE_ASSURANCE, target: playerLeft);
        }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ASSURANCE, opponentLeft);
        HP_BAR(playerLeft, captureDamage: &hits[0]);

        ANIMATION(ANIM_TYPE_MOVE, MOVE_SUBSTITUTE, playerLeft);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POUND, opponentRight);
        SUB_HIT(playerLeft);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ASSURANCE, opponentLeft);
        HP_BAR(playerLeft, captureDamage: &hits[1]);
    } THEN {
        EXPECT_EQ(hits[0], hits[1]);
    }
}

SINGLE_BATTLE_TEST("Assurance doubles in power if the target has been damaged by entry hazards on switch-in", s16 damage)
{
    bool32 hazards;

    PARAMETRIZE { hazards = FALSE; }
    PARAMETRIZE { hazards = TRUE; }

    GIVEN {
        ASSUME(GetMoveEffect(MOVE_STEALTH_ROCK) == EFFECT_STEALTH_ROCK);
        PLAYER(SPECIES_WOBBUFFET) { Speed(5); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
        OPPONENT(SPECIES_WYNAUT) { MaxHP(500); HP(500); Speed(1); }
    } WHEN {
        if (hazards)
            TURN { MOVE(player, MOVE_STEALTH_ROCK); }
        else
            TURN { MOVE(player, MOVE_CELEBRATE); }
        TURN { SWITCH(opponent, 1); MOVE(player, MOVE_ASSURANCE); }
    } SCENE {
        if (hazards)
            HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ASSURANCE, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(2.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Assurance doubles in power if the target took damage from confusion")
{
    s16 hits[2];

    GIVEN {
        ASSUME(GetMoveEffect(MOVE_CONFUSE_RAY) == EFFECT_CONFUSE);
        PLAYER(SPECIES_WOBBUFFET) { MaxHP(500); HP(500); Speed(2); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_ASSURANCE); }
        TURN { MOVE(opponent, MOVE_CONFUSE_RAY); }
        TURN { MOVE(player, MOVE_CELEBRATE, WITH_RNG(RNG_CONFUSION, TRUE)); MOVE(opponent, MOVE_ASSURANCE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ASSURANCE, opponent);
        HP_BAR(player, captureDamage: &hits[0]);

        ANIMATION(ANIM_TYPE_MOVE, MOVE_CONFUSE_RAY, opponent);

        MESSAGE("It hurt itself in its confusion!");
        HP_BAR(player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ASSURANCE, opponent);
        HP_BAR(player, captureDamage: &hits[1]);
    } THEN {
        EXPECT_MUL_EQ(hits[0], Q_4_12(2.0), hits[1]);
    }
}

SINGLE_BATTLE_TEST("Assurance doubles in power if the target has been damaged by Life Orb")
{
    s16 hits[2];

    GIVEN {
        ASSUME(gItemsInfo[ITEM_LIFE_ORB].holdEffect == HOLD_EFFECT_LIFE_ORB);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_LIFE_ORB); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_ASSURANCE); }
        TURN { MOVE(player, MOVE_POUND); MOVE(opponent, MOVE_ASSURANCE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ASSURANCE, opponent);
        HP_BAR(player, captureDamage: &hits[0]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POUND, player);
        HP_BAR(player); // life orb
        HP_BAR(player, captureDamage: &hits[1]);
    } THEN {
        EXPECT_MUL_EQ(hits[0], Q_4_12(2.0), hits[1]);
    }
}

SINGLE_BATTLE_TEST("Assurance doubles in power if the target has been damaged by Recoil")
{
    s16 hits[2];


#if MAX_MON_ITEMS > 1
SINGLE_BATTLE_TEST("Assurance doubles in power if the target has been damaged in the same turn - Life Orb (Items)")
{
    s16 hits[2];

    GIVEN {
        ASSUME(gItemsInfo[ITEM_LIFE_ORB].holdEffect == HOLD_EFFECT_LIFE_ORB);
        PLAYER(SPECIES_WOBBUFFET) { Items(ITEM_GREAT_BALL, ITEM_LIFE_ORB); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_ASSURANCE); }
        TURN { MOVE(player, MOVE_POUND); MOVE(opponent, MOVE_ASSURANCE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ASSURANCE, opponent);
        HP_BAR(player, captureDamage: &hits[0]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POUND, player);
        MESSAGE("Wobbuffet was hurt by the Life Orb!");
        HP_BAR(player, captureDamage: &hits[1]);
    } THEN {
        EXPECT_MUL_EQ(hits[0], Q_4_12(2.0), hits[1]);
    }
}
#endif
