Lidl_MapScripts::
	.byte 0


Lidl_EntranceTrigger::
# 8 "data/maps/Lidl/scripts.pory"
	lock
# 9 "data/maps/Lidl/scripts.pory"
	removeobject 1
# 10 "data/maps/Lidl/scripts.pory"
	setflag FLAG_TEMP_1
# 11 "data/maps/Lidl/scripts.pory"
	delay 16
# 12 "data/maps/Lidl/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Movement_Lidl_Enter
# 13 "data/maps/Lidl/scripts.pory"
	waitmovement 0
# 14 "data/maps/Lidl/scripts.pory"
	clearflag FLAG_TEMP_1
# 15 "data/maps/Lidl/scripts.pory"
	showobjectat 1, MAP_LIDL
# 16 "data/maps/Lidl/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Movement_Lidl_Enter_2
# 17 "data/maps/Lidl/scripts.pory"
	waitmovement 0
# 18 "data/maps/Lidl/scripts.pory"
	delay 16
# 19 "data/maps/Lidl/scripts.pory"
	release
	end


Lidl_ShopGiver::
# 24 "data/maps/Lidl/scripts.pory"
	lock
# 25 "data/maps/Lidl/scripts.pory"
	faceplayer
# 27 "data/maps/Lidl/scripts.pory"
	goto_if_unset FLAG_FIRST_POTION, Lidl_ShopGiver_2
Lidl_ShopGiver_1:
# 35 "data/maps/Lidl/scripts.pory"
	msgbox Lidl_ShopGiver_Text_3, MSGBOX_DEFAULT
# 36 "data/maps/Lidl/scripts.pory"
	waitmessage
# 37 "data/maps/Lidl/scripts.pory"
	pokemart Lidl_MartItems
# 38 "data/maps/Lidl/scripts.pory"
	msgbox Lidl_ShopGiver_Text_4, MSGBOX_AUTOCLOSE
# 39 "data/maps/Lidl/scripts.pory"
	release
	end

Lidl_ShopGiver_2:
# 28 "data/maps/Lidl/scripts.pory"
	msgbox Lidl_ShopGiver_Text_0, MSGBOX_DEFAULT
# 29 "data/maps/Lidl/scripts.pory"
	msgbox Lidl_ShopGiver_Text_1, MSGBOX_DEFAULT
# 30 "data/maps/Lidl/scripts.pory"
	giveitem ITEM_POTION
# 31 "data/maps/Lidl/scripts.pory"
	msgbox Lidl_ShopGiver_Text_2, MSGBOX_DEFAULT
# 32 "data/maps/Lidl/scripts.pory"
	setflag FLAG_FIRST_POTION
	goto Lidl_ShopGiver_1


Lidl_Schlumpert_1::
# 44 "data/maps/Lidl/scripts.pory"
	goto_if_unset FLAG_GOT_FIRST_MON, Lidl_Schlumpert_1_1
	return

Lidl_Schlumpert_1_1:
# 45 "data/maps/Lidl/scripts.pory"
	msgbox Lidl_Schlumpert_1_Text_0, MSGBOX_DEFAULT
# 46 "data/maps/Lidl/scripts.pory"
	givemon SPECIES_PSYDUCK, 5, ITEM_NONE
# 47 "data/maps/Lidl/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 48 "data/maps/Lidl/scripts.pory"
	msgbox Text_RecievedPsyduck, MSGBOX_DEFAULT
# 49 "data/maps/Lidl/scripts.pory"
	waitfanfare
# 50 "data/maps/Lidl/scripts.pory"
	msgbox Lidl_Schlumpert_1_Text_1, MSGBOX_AUTOCLOSE
# 51 "data/maps/Lidl/scripts.pory"
	setflag FLAG_GOT_FIRST_MON
# 52 "data/maps/Lidl/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 53 "data/maps/Lidl/scripts.pory"
	setflag FLAG_SYS_POKEDEX_GET
# 54 "data/maps/Lidl/scripts.pory"
	setflag FLAG_SYS_POKENAV_GET
	return


	.align 2
# 59 "data/maps/Lidl/scripts.pory"
Lidl_MartItems:
# 60 "data/maps/Lidl/scripts.pory"
	.2byte ITEM_LEMONADE
# 61 "data/maps/Lidl/scripts.pory"
	.2byte ITEM_FRESH_WATER
# 62 "data/maps/Lidl/scripts.pory"
	.2byte ITEM_MOOMOO_MILK
# 63 "data/maps/Lidl/scripts.pory"
	.2byte ITEM_LAVA_COOKIE
# 64 "data/maps/Lidl/scripts.pory"
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NONE

# 67 "data/maps/Lidl/scripts.pory"
Movement_Lidl_Enter:
# 68 "data/maps/Lidl/scripts.pory"
	walk_up
# 69 "data/maps/Lidl/scripts.pory"
	walk_up
	step_end

# 72 "data/maps/Lidl/scripts.pory"
Movement_Lidl_Enter_2:
# 73 "data/maps/Lidl/scripts.pory"
	walk_up
	step_end

Lidl_ShopGiver_Text_0:
# 28 "data/maps/Lidl/scripts.pory"
	.string "Welcome to LIDL.$"

Lidl_ShopGiver_Text_1:
# 29 "data/maps/Lidl/scripts.pory"
	.string "We're running a special promotion.\nHere, a free sample for you!\p$"

Lidl_ShopGiver_Text_2:
# 31 "data/maps/Lidl/scripts.pory"
	.string "Also...\p$"

Lidl_ShopGiver_Text_3:
# 35 "data/maps/Lidl/scripts.pory"
	.string "Please check out our sortiment.$"

Lidl_ShopGiver_Text_4:
# 38 "data/maps/Lidl/scripts.pory"
	.string "Come again soon.$"

Lidl_Schlumpert_1_Text_0:
# 45 "data/maps/Lidl/scripts.pory"
	.string "{SPEAKER NAME_SCHLUMPERT}Welcome to LIDL.$"

Lidl_Schlumpert_1_Text_1:
# 50 "data/maps/Lidl/scripts.pory"
	.string "{SPEAKER NAME_SCHLUMPERT}Have fun with that.$"

Text_RecievedPsyduck::
# 76 "data/maps/Lidl/scripts.pory"
	.string "{SPEAKER NAME_NONE}{PLAYER} received a Psyduck!!$"
