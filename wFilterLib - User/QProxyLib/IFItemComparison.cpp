#include "IFItemComparison.h"
#include "GameStuff/CGInterface/IFHelperBubbleWindow.h"
#include "GameStuff/CGInterface/IFEquipment.h"
#include "GameStuff/CGInterface/CSOItem.h"
#include "GameStuff/CGInterface/CObjectData.h"
//#include <Data\CharacterData.h>
//#include "NotificationHandler.h"
//#include <TextStringManager.h>

void CIFItemComparison::AppendAdvancedInfo(CIFHelperBubbleWindow* window)
{
	//reinterpret_cast<void(__thiscall*)(CIFItemComparison*, CIFHelperBubbleWindow*)>(0x0066FA60)(this, window); // old tooltip
	reinterpret_cast<void(__thiscall*)(CIFItemComparison*, CIFHelperBubbleWindow*)>(0x0066FD60)(this, window); //normal tooltip

	/*0: EQUIP_SLOT_HELM
	1: EQUIP_SLOT_MAIL,
	2: EQUIP_SLOT_SHOULDERGUARD,
	3: EQUIP_SLOT_GAUNTLET,
	4: EQUIP_SLOT_PANTS,
	5: EQUIP_SLOT_BOOTS,
	6: EQUIP_SLOT_WEAPON,
	7: EQUIP_SLOT_SHIELD or ARROW,
	9: EQUIP_SLOT_EARRING,
	10: EQUIP_SLOT_NECKLACE,
	11: EQUIP_SLOT_L_RING,
	12: EQUIP_SLOT_R_RING,
	*/

	short ALTState = GetKeyState(VK_MENU);
	if (ALTState == -127 || ALTState == -128) // ALT is hold
	{
		wchar_t buffer[45];
		w_string_last mymsg(L"\n       <<Comparison>>");
		UINT msgcolor = 0xFFEFDAA4; //No Difference: FFFEFEFF | Better: FFFFD953 | Worse: FFFF4A4A
		window->WriteLine(mymsg, 0, msgcolor, 0, 3);
		CSOItem* myitem = this->_CSOItem;
		CSOItem* curritem;

		switch (myitem->GetObjectData()->TID)
		{
		case 0x132C: //ch sword
		case 0x1B2C: //ch blade
		case 0x232C: //ch spear
		case 0x2B2C: //ch glaive
		case 0x332C: //ch bow
		case 0x6B2C: //eu dagger
		case 0x3B2C: //eu 1h
		case 0x432C: //eu 2h
		case 0x4B2C: //eu axe
		case 0x632C: //eu crossbow
		case 0x532C: //eu warlock
		case 0x5B2C: //eu 2hstaff
		case 0x732C: //eu harp
		case 0x7B2C: //eu staff
		{
			int dmi = 0, dma = 0;
			float drmi = 0, drma = 0;
			curritem = g_CGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(6);
			if (myitem->PhyAtkPwrMax || curritem->PhyAtkPwrMax)
			{
				dmi = myitem->PhyAtkPwrMin - curritem->PhyAtkPwrMin;
				dma = myitem->PhyAtkPwrMax - curritem->PhyAtkPwrMax;

				if (dmi == 0 && dma == 0)
				{
					msgcolor = 0xFFFEFEFF;
					swprintf_s(buffer, sizeof(buffer), L"Phy. atk. pwr. +0 ~ +0");
				}
				else if (dmi > -1 && dma > -1)
				{
					msgcolor = 0xFFFFD953;
					swprintf_s(buffer, sizeof(buffer), L"Phy. atk. pwr. +%d ~ +%d", dmi, dma);
				}
				else if (dmi < 0 && dma < 0)
				{
					msgcolor = 0xFFFF4A4A;
					swprintf_s(buffer, sizeof(buffer), L"Phy. atk. pwr. %d ~ %d", dmi, dma);
				}
				else if (dmi > 0 && dma < 0 && (dmi - dma) > 0)
				{
					msgcolor = 0xFFFFD953;
					swprintf_s(buffer, sizeof(buffer), L"Phy. atk. pwr. +%d ~ %d", dmi, dma);
				}
				else if (dma > 0 && dmi < 0 && (dma - dmi) > 0)
				{
					msgcolor = 0xFFFFD953;
					swprintf_s(buffer, sizeof(buffer), L"Phy. atk. pwr. %d ~ +%d", dmi, dma);
				}
				else if (dmi > 0 && dma < 0 && (dmi - dma) < 0)
				{
					msgcolor = 0xFFFF4A4A;
					swprintf_s(buffer, sizeof(buffer), L"Phy. atk. pwr. +%d ~ %d", dmi, dma);
				}
				else if (dma > 0 && dmi < 0 && (dma - dmi) < 0)
				{
					msgcolor = 0xFFFF4A4A;
					swprintf_s(buffer, sizeof(buffer), L"Phy. atk. pwr. %d ~ +%d", dmi, dma);
				}

				mymsg.assign(buffer);
				window->WriteLine(mymsg, 0, msgcolor, 0, 1);
			}

			if (myitem->MagAtkPwrMax || curritem->MagAtkPwrMax)
			{
				dmi = myitem->MagAtkPwrMin - curritem->MagAtkPwrMin;
				dma = myitem->MagAtkPwrMax - curritem->MagAtkPwrMax;

				if (dmi == 0 && dma == 0)
				{
					msgcolor = 0xFFFEFEFF;
					swprintf_s(buffer, sizeof(buffer), L"Mag. atk. pwr. +0 ~ +0");
				}
				else if (dmi > -1 && dma > -1)
				{
					msgcolor = 0xFFFFD953;
					swprintf_s(buffer, sizeof(buffer), L"Mag. atk. pwr. +%d ~ +%d", dmi, dma);
				}
				else if (dmi < 0 && dma < 0)
				{
					msgcolor = 0xFFFF4A4A;
					swprintf_s(buffer, sizeof(buffer), L"Mag. atk. pwr. %d ~ %d", dmi, dma);
				}
				else if (dmi > 0 && dma < 0 && (dmi - dma) > 0)
				{
					msgcolor = 0xFFFFD953;
					swprintf_s(buffer, sizeof(buffer), L"Mag. atk. pwr. +%d ~ %d", dmi, dma);
				}
				else if (dma > 0 && dmi < 0 && (dma - dmi) > 0)
				{
					msgcolor = 0xFFFFD953;
					swprintf_s(buffer, sizeof(buffer), L"Mag. atk. pwr. %d ~ +%d", dmi, dma);
				}
				else if (dmi > 0 && dma < 0 && (dmi - dma) < 0)
				{
					msgcolor = 0xFFFF4A4A;
					swprintf_s(buffer, sizeof(buffer), L"Mag. atk. pwr. +%d ~ %d", dmi, dma);
				}
				else if (dma > 0 && dmi < 0 && (dma - dmi) < 0)
				{
					msgcolor = 0xFFFF4A4A;
					swprintf_s(buffer, sizeof(buffer), L"Mag. atk. pwr. %d ~ +%d", dmi, dma);
				}

				mymsg.assign(buffer);
				window->WriteLine(mymsg, 0, msgcolor, 0, 1);
			}

			dmi = myitem->MaxDurability - curritem->MaxDurability;
			if (dmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Durability +%d", dmi);
			}
			else if (dmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Durability %d", dmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Durability +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			dmi = myitem->AttackRateValue - curritem->AttackRateValue;
			if (dmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Attack rate +%d", dmi);
			}
			else if (dmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Attack rate %d", dmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Attack rate +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			dmi = myitem->CriticalValue - curritem->CriticalValue;
			if (dmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Critical +%d", dmi);
			}
			else if (dmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Critical %d", dmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Critical +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			if (myitem->PhyReinforcementMax || curritem->PhyReinforcementMax)
			{
				drmi = myitem->PhyReinforcementMin - curritem->PhyReinforcementMin;
				drma = myitem->PhyReinforcementMax - curritem->PhyReinforcementMax;

				if (drmi == 0 && drma == 0)
				{
					msgcolor = 0xFFFEFEFF;
					swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce +0%% ~ +0%%");
				}
				else if (drmi > -1 && drma > -1)
				{
					msgcolor = 0xFFFFD953;
					swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce +%.1f%% ~ +%.1f%%", drmi * 100, drma * 100);
				}
				else if (drmi < 0 && drma < 0)
				{
					msgcolor = 0xFFFF4A4A;
					swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce %.1f%% ~ %.1f%%", drmi * 100, drma * 100);
				}
				else if (drmi > 0 && drma < 0 && (drmi - drma) > 0)
				{
					msgcolor = 0xFFFFD953;
					swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce +%.1f%% ~ %.1f%%", drmi * 100, drma * 100);
				}
				else if (drma > 0 && drmi < 0 && (drma - drmi) > 0)
				{
					msgcolor = 0xFFFFD953;
					swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce %.1f%% ~ +%.1f%%", drmi * 100, drma * 100);
				}
				else if (drmi > 0 && drma < 0 && (drmi - drma) < 0)
				{
					msgcolor = 0xFFFF4A4A;
					swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce +%.1f%% ~ %.1f%%", drmi * 100, drma * 100);
				}
				else if (drma > 0 && drmi < 0 && (drma - drmi) < 0)
				{
					msgcolor = 0xFFFF4A4A;
					swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce %.1f%% ~ +%.1f%%", drmi * 100, drma * 100);
				}

				mymsg.assign(buffer);
				window->WriteLine(mymsg, 0, msgcolor, 0, 1);
			}

			if (myitem->MagReinforcementMax || curritem->MagReinforcementMax)
			{
				drmi = myitem->MagReinforcementMin - curritem->MagReinforcementMin;
				drma = myitem->MagReinforcementMax - curritem->MagReinforcementMax;

				if (drmi == 0 && drma == 0)
				{
					msgcolor = 0xFFFEFEFF;
					swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce +0%% ~ +0%%");
				}
				else if (drmi > -1 && drma > -1)
				{
					msgcolor = 0xFFFFD953;
					swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce +%.1f%% ~ +%.1f%%", drmi * 100, drma * 100);
				}
				else if (drmi < 0 && drma < 0)
				{
					msgcolor = 0xFFFF4A4A;
					swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce %.1f%% ~ %.1f%%", drmi * 100, drma * 100);
				}
				else if (drmi > 0 && drma < 0 && (drmi - drma) > 0)
				{
					msgcolor = 0xFFFFD953;
					swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce +%.1f%% ~ %.1f%%", drmi * 100, drma * 100);
				}
				else if (drma > 0 && drmi < 0 && (drma - drmi) > 0)
				{
					msgcolor = 0xFFFFD953;
					swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce %.1f%% ~ +%.1f%%", drmi * 100, drma * 100);
				}
				else if (drmi > 0 && drma < 0 && (drmi - drma) < 0)
				{
					msgcolor = 0xFFFF4A4A;
					swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce +%.1f%% ~ %.1f%%", drmi * 100, drma * 100);
				}
				else if (drma > 0 && drmi < 0 && (drma - drmi) < 0)
				{
					msgcolor = 0xFFFF4A4A;
					swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce %.1f%% ~ +%.1f%%", drmi * 100, drma * 100);
				}

				mymsg.assign(buffer);
				window->WriteLine(mymsg, 0, msgcolor, 0, 1);
			}
			break;
		}

		case 0x0A2C: //ch shield
		case 0x122C: //eu shield
		{
			curritem = g_CGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(7);
			int dmi = 0;
			float drmi = 0;
			drmi = myitem->PhyDefPwrValue - curritem->PhyDefPwrValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagDefPwrValue - curritem->MagDefPwrValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			dmi = myitem->MaxDurability - curritem->MaxDurability;
			if (dmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Durability +%d", dmi);
			}
			else if (dmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Durability %d", dmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Durability +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			dmi = myitem->BlockingRateValue - curritem->BlockingRateValue;
			if (dmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Blocking rate +%d", dmi);
			}
			else if (dmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Blocking rate %d", dmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Blocking rate +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->PhyReinforcementValue - curritem->PhyReinforcementValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. +%.1f%%", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. %.1f%%", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. +0%%");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagReinforcementValue - curritem->MagReinforcementValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. +%.1f%%", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. %.1f%%", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. +0%%");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);
			break;
		}

		case 0x0AAC: //ch earring
		case 0x0E2C: //eu earring
		{
			curritem = g_CGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(9);
			float drmi = 0;
			drmi = myitem->PhyAbsorption - curritem->PhyAbsorption;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. absorption +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. absorption %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. absorption +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagAbsorption - curritem->MagAbsorption;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. absorption +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. absorption %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. absorption +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);
			break;
		}

		case 0x12AC: //ch necklace
		case 0x162C: //eu necklace
		{
			curritem = g_CGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(10);
			float drmi = 0;
			drmi = myitem->PhyAbsorption - curritem->PhyAbsorption;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. absorption +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. absorption %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. absorption +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagAbsorption - curritem->MagAbsorption;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. absorption +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. absorption %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. absorption +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);
			break;
		}

		case 0x1AAC: //ch ring
		case 0x1E2C: //eu ring
		{
			CIFEquipment* myequipments = g_CGInterface->GetMainPopup()->GetEquipment();
			curritem = myequipments->GetEquipmentObjectBySlot(11);

			float drmi = 0;
			mymsg.assign(L"<<Left>>");
			msgcolor = 0xFFEFDAA4;
			window->WriteLine(mymsg, 0, msgcolor, 0, 2);

			drmi = myitem->PhyAbsorption - curritem->PhyAbsorption;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. absorption +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. absorption %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. absorption +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagAbsorption - curritem->MagAbsorption;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. absorption +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. absorption %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. absorption +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			curritem = myequipments->GetEquipmentObjectBySlot(12);

			mymsg.assign(L"\n<<Right>>");
			msgcolor = 0xFFEFDAA4;
			window->WriteLine(mymsg, 0, msgcolor, 0, 2);

			drmi = myitem->PhyAbsorption - curritem->PhyAbsorption;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. absorption +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. absorption %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. absorption +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagAbsorption - curritem->MagAbsorption;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. absorption +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. absorption %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. absorption +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);
			break;
		}

		//Head
		case 0x0D2C:
		case 0x092C:
		case 0x0CAC:
		case 0x0DAC:
		case 0x08AC:
		case 0x09AC:
		{
			curritem = g_CGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(0);
			int dmi = 0;
			float drmi = 0;
			drmi = myitem->PhyDefPwrValue - curritem->PhyDefPwrValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagDefPwrValue - curritem->MagDefPwrValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			dmi = myitem->MaxDurability - curritem->MaxDurability;
			if (dmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Durability +%d", dmi);
			}
			else if (dmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Durability %d", dmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Durability +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			dmi = myitem->ParryRateValue - curritem->ParryRateValue;
			if (dmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate +%d", dmi);
			}
			else if (dmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate %d", dmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->PhyReinforcementValue - curritem->PhyReinforcementValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. +%.1f%%", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. %.1f%%", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. +0%%");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagReinforcementValue - curritem->MagReinforcementValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. +%.1f%%", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. %.1f%%", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. +0%%");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);
			break;
		}

		//Shoulder
		case 0x15AC:
		case 0x10AC:
		case 0x152C:
		case 0x11AC:
		case 0x112C:
		case 0x14AC:
		{
			curritem = g_CGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(2);
			int dmi = 0;
			float drmi = 0;
			drmi = myitem->PhyDefPwrValue - curritem->PhyDefPwrValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagDefPwrValue - curritem->MagDefPwrValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			dmi = myitem->MaxDurability - curritem->MaxDurability;
			if (dmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Durability +%d", dmi);
			}
			else if (dmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Durability %d", dmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Durability +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			dmi = myitem->ParryRateValue - curritem->ParryRateValue;
			if (dmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate +%d", dmi);
			}
			else if (dmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate %d", dmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->PhyReinforcementValue - curritem->PhyReinforcementValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. +%.1f%%", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. %.1f%%", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. +0%%");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagReinforcementValue - curritem->MagReinforcementValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. +%.1f%%", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. %.1f%%", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. +0%%");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);
			break;
		}

		//Chest
		case 0x1CAC:
		case 0x192C:
		case 0x18AC:
		case 0x1DAC:
		case 0x19AC:
		case 0x1D2C:
		{
			curritem = g_CGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(1);
			int dmi = 0;
			float drmi = 0;
			drmi = myitem->PhyDefPwrValue - curritem->PhyDefPwrValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagDefPwrValue - curritem->MagDefPwrValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			dmi = myitem->MaxDurability - curritem->MaxDurability;
			if (dmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Durability +%d", dmi);
			}
			else if (dmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Durability %d", dmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Durability +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			dmi = myitem->ParryRateValue - curritem->ParryRateValue;
			if (dmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate +%d", dmi);
			}
			else if (dmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate %d", dmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->PhyReinforcementValue - curritem->PhyReinforcementValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. +%.1f%%", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. %.1f%%", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. +0%%");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagReinforcementValue - curritem->MagReinforcementValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. +%.1f%%", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. %.1f%%", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. +0%%");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);
			break;
		}

		//Legs
		case 0x25AC:
		case 0x21AC:
		case 0x252C:
		case 0x212C:
		case 0x24AC:
		case 0x20AC:
		{
			curritem = g_CGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(4);
			int dmi = 0;
			float drmi = 0;
			drmi = myitem->PhyDefPwrValue - curritem->PhyDefPwrValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagDefPwrValue - curritem->MagDefPwrValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			dmi = myitem->MaxDurability - curritem->MaxDurability;
			if (dmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Durability +%d", dmi);
			}
			else if (dmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Durability %d", dmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Durability +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			dmi = myitem->ParryRateValue - curritem->ParryRateValue;
			if (dmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate +%d", dmi);
			}
			else if (dmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate %d", dmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->PhyReinforcementValue - curritem->PhyReinforcementValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. +%.1f%%", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. %.1f%%", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. +0%%");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagReinforcementValue - curritem->MagReinforcementValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. +%.1f%%", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. %.1f%%", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. +0%%");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);
			break;
		}

		//Hands
		case 0x2CAC:
		case 0x292C:
		case 0x28AC:
		case 0x2DAC:
		case 0x2D2C:
		case 0x29AC:
		{
			curritem = g_CGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(3);
			int dmi = 0;
			float drmi = 0;
			drmi = myitem->PhyDefPwrValue - curritem->PhyDefPwrValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagDefPwrValue - curritem->MagDefPwrValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			dmi = myitem->MaxDurability - curritem->MaxDurability;
			if (dmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Durability +%d", dmi);
			}
			else if (dmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Durability %d", dmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Durability +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			dmi = myitem->ParryRateValue - curritem->ParryRateValue;
			if (dmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate +%d", dmi);
			}
			else if (dmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate %d", dmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->PhyReinforcementValue - curritem->PhyReinforcementValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. +%.1f%%", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. %.1f%%", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. +0%%");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagReinforcementValue - curritem->MagReinforcementValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. +%.1f%%", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. %.1f%%", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. +0%%");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);
			break;
		}

		//Foot
		case 0x30AC:
		case 0x312C:
		case 0x31AC:
		case 0x34AC:
		case 0x352C:
		case 0x35AC:
		{
			curritem = g_CGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(5);
			int dmi = 0;
			float drmi = 0;
			drmi = myitem->PhyDefPwrValue - curritem->PhyDefPwrValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. def. pwr. +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagDefPwrValue - curritem->MagDefPwrValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. +%.1f", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. %.1f", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. def. pwr. +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			dmi = myitem->MaxDurability - curritem->MaxDurability;
			if (dmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Durability +%d", dmi);
			}
			else if (dmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Durability %d", dmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Durability +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			dmi = myitem->ParryRateValue - curritem->ParryRateValue;
			if (dmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate +%d", dmi);
			}
			else if (dmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate %d", dmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Parry rate +0");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->PhyReinforcementValue - curritem->PhyReinforcementValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. +%.1f%%", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. %.1f%%", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Phy. reinforce. +0%%");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);

			drmi = myitem->MagReinforcementValue - curritem->MagReinforcementValue;
			if (drmi > 0)
			{
				msgcolor = 0xFFFFD953;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. +%.1f%%", drmi);
			}
			else if (drmi < 0)
			{
				msgcolor = 0xFFFF4A4A;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. %.1f%%", drmi);
			}
			else
			{
				msgcolor = 0xFFFEFEFF;
				swprintf_s(buffer, sizeof(buffer), L"Mag. reinforce. +0%%");
			}
			mymsg.assign(buffer);
			window->WriteLine(mymsg, 0, msgcolor, 0, 1);
			break;
		}
		}
	}
}
