PhilKseHouse_1_MapScripts::
# 2 "data/maps/PhilKseHouse_1/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, PhilKseHouse_1_MapScripts_OnTransition
	.byte 0


PhilKseHouse_1_MapScripts_OnTransition::
# 7 "data/maps/PhilKseHouse_1/scripts.pory"
	call Common_EventScript_SetupRivalGfxId
	end


PhilKseHouse_1_MapScripts_PartnerInteraction::
# 12 "data/maps/PhilKseHouse_1/scripts.pory"
	lock
# 13 "data/maps/PhilKseHouse_1/scripts.pory"
	faceplayer
# 14 "data/maps/PhilKseHouse_1/scripts.pory"
	msgbox PhilKseHouse_1_MapScripts_PartnerInteraction_Text_0, MSGBOX_DEFAULT
# 15 "data/maps/PhilKseHouse_1/scripts.pory"
	setflag FLAG_RECEIVED_RUNNING_SHOES
# 16 "data/maps/PhilKseHouse_1/scripts.pory"
	setflag FLAG_SYS_B_DASH
# 17 "data/maps/PhilKseHouse_1/scripts.pory"
	release
	end


PhilKseHouse_1_MapScripts_GotBike::
# 22 "data/maps/PhilKseHouse_1/scripts.pory"
	lock
# 23 "data/maps/PhilKseHouse_1/scripts.pory"
	faceplayer
# 24 "data/maps/PhilKseHouse_1/scripts.pory"
	msgbox PhilKseHouse_1_MapScripts_GotBike_Text_0, MSGBOX_DEFAULT
# 25 "data/maps/PhilKseHouse_1/scripts.pory"
	giveitem ITEM_MACH_BIKE
# 26 "data/maps/PhilKseHouse_1/scripts.pory"
	removeobject 2
# 27 "data/maps/PhilKseHouse_1/scripts.pory"
	setflag FLAG_RECEIVED_BIKE
# 28 "data/maps/PhilKseHouse_1/scripts.pory"
	release
	end


PhilKseHouse_1_MapScripts_PartnerInteraction_Text_0:
# 14 "data/maps/PhilKseHouse_1/scripts.pory"
	.string "How about taking these?$"

PhilKseHouse_1_MapScripts_GotBike_Text_0:
# 24 "data/maps/PhilKseHouse_1/scripts.pory"
	.string "Better take my bike...$"
