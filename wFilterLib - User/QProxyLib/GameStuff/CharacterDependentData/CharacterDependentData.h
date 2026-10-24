#pragma once

#define g_CCharacterDependentData (*reinterpret_cast<CCharacterDependentData*>(0x00eeebd8))

class CCharacterDependentData {
public:
	char pad_0000[136]; //0x0000
	int32_t PartyNumber; //0x0088

	/// \address 00987070
	bool IsInParty() const;

	/// \address 009870E0
	bool IsInGuild() const;

	/// \address 00987140
	bool IsInTrainingCamp() const;

	/// \address 00988A50
	bool sub_988A50() const;
}; 