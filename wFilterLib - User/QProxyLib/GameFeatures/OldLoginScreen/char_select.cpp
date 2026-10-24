// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "char_select.h"

#include "static_constructor.h"

#include "Character3D.h"
#include "Keyframe.h"

#include "address_helper.h"

#include <Windows.h>
#include <stdio.h>

extern HMODULE sro_client;

#define CHARSEL_CREATE 744
#define CHARSEL_INTRO 743
#define CHARSEL_CHARPOS_1 747
#define CHARSEL_CHARPOS_2 748


#define CHARSEL_KEYFRAME_START CLIENT_OFFSET(0xAC2D88)
#define CHARSEL_KEYFRAME_END CLIENT_OFFSET(0xAC2DA8)


#define CHARSEL_KEYFRAME_CREATE_1 CLIENT_OFFSET(0xAC2DC8)
#define CHARSEL_KEYFRAME_CREATE_2 CLIENT_OFFSET(0xAC2DE8)
#define CHARSEL_KEYFRAME_CREATE_3 CLIENT_OFFSET(0xAC2E08)
#define CHARSEL_KEYFRAME_CREATE_4 CLIENT_OFFSET(0xAC2E28)

#define CHARSEL_CHARACTER_POSITION_1 CLIENT_OFFSET(0xAC2E48)
#define CHARSEL_CHARACTER_POSITION_2 CLIENT_OFFSET(0xAC2E58)

#define CHARSEL_RAW_LIZARD_Z CLIENT_OFFSET(0x9D7DF8)

#define CHARSEL_RAW_CHINESE_Z CLIENT_OFFSET(0x9D7DFC)
#define CHARSEL_RAW_CHINESE_X CLIENT_OFFSET(0x9D7E00)

#define CHARSEL_RAW_EUROPE_Z  CLIENT_OFFSET(0x9D7E28)
#define CHARSEL_RAW_EUROPE_X  CLIENT_OFFSET(0x9D7E7C)

#define CHARSEL_RAW_CRATE_Z   CLIENT_OFFSET(0x9D7E80)
#define CHARSEL_RAW_CRATE_Y   CLIENT_OFFSET(0x9D7E84)
#define CHARSEL_RAW_CRATE_X   CLIENT_OFFSET(0x9D7EA0)

#define CHARSEL_CHARACTER_POSITION_YOFFSET CLIENT_OFFSET(0x9D7C98)

void static_const_create(void);
void static_const_intro(void);

void static_const_char_1(void);
void static_const_char_2(void);

void PatchMe(DWORD address, BYTE value)
{
	DWORD oldProtect;
	void *addr = reinterpret_cast<void *>(address);
	if (VirtualProtect((LPVOID)addr, 1, PAGE_READWRITE, &oldProtect) == FALSE)
	{
		throw ("cannot patch function");
		return;
	}
	*reinterpret_cast<BYTE *>(addr) = value;
	VirtualProtect(addr, 1, oldProtect, &oldProtect);
}
void char_select_stuff(void)
{
	//idols start
	PatchMe(0x400000 + 0x0098ADC6, 0xA0);
	PatchMe(0x400000 + 0x009D7DF0, 0x00);
	PatchMe(0x400000 + 0x009D7DF1, 0x00);
	PatchMe(0x400000 + 0x009D7DF2, 0xA0);
	PatchMe(0x400000 + 0x009D7DF4, 0x00);
	PatchMe(0x400000 + 0x009D7DF5, 0x00);
	PatchMe(0x400000 + 0x009D7DF6, 0xA0);
	PatchMe(0x400000 + 0x009D7DF8, 0x00);
	PatchMe(0x400000 + 0x009D7DF9, 0x00);
	PatchMe(0x400000 + 0x009D7DFA, 0xBE);
	PatchMe(0x400000 + 0x009D7DFC, 0x00);
	PatchMe(0x400000 + 0x009D7DFD, 0x00);
	PatchMe(0x400000 + 0x009D7DFE, 0x50);
	PatchMe(0x400000 + 0x009D7DFF, 0x43);
	PatchMe(0x400000 + 0x009D7E00, 0x00);
	PatchMe(0x400000 + 0x009D7E01, 0x40);
	PatchMe(0x400000 + 0x009D7E02, 0xBE);
	PatchMe(0x400000 + 0x009D7E28, 0x00);
	PatchMe(0x400000 + 0x009D7E29, 0x00);
	PatchMe(0x400000 + 0x009D7E2A, 0x4F);
	PatchMe(0x400000 + 0x009D7E2B, 0x43);
	PatchMe(0x400000 + 0x009D7E7E, 0xBD);
	PatchMe(0x400000 + 0x009D7E84, 0xF0);
	PatchMe(0x400000 + 0x009D7E85, 0x85);
	PatchMe(0x400000 + 0x009D7E86, 0xF7);
	PatchMe(0x400000 + 0x009D7E87, 0x40);
	//idols end
	//idols animations start
	PatchMe(0x400000 + 0x009D7CFC, 0xE3);
	PatchMe(0x400000 + 0x009D7CFD, 0x68);
	PatchMe(0x400000 + 0x009D7CFE, 0x4E);
	PatchMe(0x400000 + 0x009D7CFF, 0x43);
	PatchMe(0x400000 + 0x009D7D00, 0x00);
	PatchMe(0x400000 + 0x009D7D01, 0x00);
	PatchMe(0x400000 + 0x009D7D02, 0xA0);
	PatchMe(0x400000 + 0x009D7D03, 0x41);
	PatchMe(0x400000 + 0x009D7D05, 0x00);
	PatchMe(0x400000 + 0x009D7D06, 0xB9);
	PatchMe(0x400000 + 0x009D7D08, 0xE3);
	PatchMe(0x400000 + 0x009D7D09, 0x68);
	PatchMe(0x400000 + 0x009D7D0A, 0x4E);
	PatchMe(0x400000 + 0x009D7D0B, 0x43);
	PatchMe(0x400000 + 0x009D7D0C, 0x00);
	PatchMe(0x400000 + 0x009D7D0D, 0x00);
	PatchMe(0x400000 + 0x009D7D0E, 0xA0);
	PatchMe(0x400000 + 0x009D7D0F, 0x41);
	PatchMe(0x400000 + 0x009D7D10, 0x00);
	PatchMe(0x400000 + 0x009D7D11, 0x00);
	PatchMe(0x400000 + 0x009D7D12, 0xB9);
	//idols anim end
	//CharSelect Distance
	PatchMe(0x00D8AD3E, (byte)0x70417C87);
	//CharSelect Distance end
	//Region start
	PatchMe(0x400000 + 0x009D7CA6, 0x00);
	PatchMe(0x400000 + 0x009D7CA7, 0x00);
	PatchMe(0x400000 + 0x009D601E, 0x00);
	PatchMe(0x400000 + 0x009D601F, 0x00);
	PatchMe(0x400000 + 0x0045F4FD, 0xBC);
	PatchMe(0x400000 + 0x0045F4FE, 0x5F);
	//region end

#ifdef OLD_MAINPOP
	PatchMe(0x400000 + 0x0045C6F5, 0xE9);
	PatchMe(0x400000 + 0x0045C6F6, 0xCA);
	PatchMe(0x400000 + 0x0045C6F7, 0x00);
	PatchMe(0x400000 + 0x0045C6F8, 0x00);
	PatchMe(0x400000 + 0x0045C6F9, 0x00);
	PatchMe(0x400000 + 0x0045C7CD, 0x09);
	PatchMe(0x400000 + 0x002A2901, 0xBC);
	PatchMe(0x400000 + 0x002A2909, 0x50);
	PatchMe(0x400000 + 0x002A290A, 0xFF);
	PatchMe(0x400000 + 0x002A290B, 0xD0);
	PatchMe(0x400000 + 0x002A290C, 0x8B);
	PatchMe(0x400000 + 0x002A290D, 0x44);
	PatchMe(0x400000 + 0x002A290E, 0x24);
	PatchMe(0x400000 + 0x002A290F, 0x2C);
	PatchMe(0x400000 + 0x002A2910, 0x83);
	PatchMe(0x400000 + 0x002A2911, 0xF8);
	PatchMe(0x400000 + 0x002A2912, 0x08);
	PatchMe(0x400000 + 0x002A2913, 0x0F);
	PatchMe(0x400000 + 0x002A2914, 0x82);
	PatchMe(0x400000 + 0x002A2915, 0x85);
	PatchMe(0x400000 + 0x002A2916, 0x00);
	PatchMe(0x400000 + 0x002A2917, 0x00);
	PatchMe(0x400000 + 0x002A2918, 0x00);
	PatchMe(0x400000 + 0x002A2919, 0x90);
	PatchMe(0x400000 + 0x002A291A, 0x90);
	PatchMe(0x400000 + 0x002A291B, 0x90);
	PatchMe(0x400000 + 0x002A291C, 0x90);
	PatchMe(0x400000 + 0x002A291D, 0x90);
	PatchMe(0x400000 + 0x002A291E, 0x90);
	PatchMe(0x400000 + 0x002A291F, 0x90);
	PatchMe(0x400000 + 0x002A2920, 0x90);
	PatchMe(0x400000 + 0x002A2921, 0x90);
	PatchMe(0x400000 + 0x002A2922, 0x90);
	PatchMe(0x400000 + 0x002A2923, 0x90);
	PatchMe(0x400000 + 0x002A2924, 0x90);
	PatchMe(0x400000 + 0x002A2925, 0x90);
	PatchMe(0x400000 + 0x002A2926, 0x90);
	PatchMe(0x400000 + 0x002A2927, 0x90);
	PatchMe(0x400000 + 0x002A2928, 0x90);
	PatchMe(0x400000 + 0x002A2929, 0x90);
	PatchMe(0x400000 + 0x002A292A, 0x90);
	PatchMe(0x400000 + 0x002A292B, 0x90);
	PatchMe(0x400000 + 0x002A292C, 0x90);
	PatchMe(0x400000 + 0x002A292D, 0x90);
	PatchMe(0x400000 + 0x002A292E, 0x90);
	PatchMe(0x400000 + 0x002A292F, 0x90);
	PatchMe(0x400000 + 0x002A2930, 0x90);
	PatchMe(0x400000 + 0x002A2931, 0x90);
	PatchMe(0x400000 + 0x002A2932, 0x90);
	PatchMe(0x400000 + 0x002A2933, 0x90);
	PatchMe(0x400000 + 0x002A2934, 0x90);
	PatchMe(0x400000 + 0x002A2935, 0x90);
	PatchMe(0x400000 + 0x002A2936, 0x90);
	PatchMe(0x400000 + 0x002A2937, 0x90);
	PatchMe(0x400000 + 0x002A2938, 0x90);
	PatchMe(0x400000 + 0x002A2939, 0x90);
	PatchMe(0x400000 + 0x002A293A, 0x90);
	PatchMe(0x400000 + 0x002A293B, 0x90);
	PatchMe(0x400000 + 0x002A293C, 0x90);
	PatchMe(0x400000 + 0x002A293D, 0x90);
	PatchMe(0x400000 + 0x002A293E, 0x90);
	PatchMe(0x400000 + 0x002A293F, 0x90);
	PatchMe(0x400000 + 0x002A2940, 0x90);
	PatchMe(0x400000 + 0x002A2941, 0x90);
	PatchMe(0x400000 + 0x002A2942, 0x90);
	PatchMe(0x400000 + 0x002A2943, 0x90);
	PatchMe(0x400000 + 0x002A2944, 0x90);
	PatchMe(0x400000 + 0x002A2945, 0x90);
	PatchMe(0x400000 + 0x002A2946, 0x90);
	PatchMe(0x400000 + 0x002A2947, 0x90);
	PatchMe(0x400000 + 0x002A2948, 0x90);
	PatchMe(0x400000 + 0x002A2949, 0x90);
	PatchMe(0x400000 + 0x002A294A, 0x90);
	PatchMe(0x400000 + 0x002A294B, 0x90);
	PatchMe(0x400000 + 0x002A294C, 0x90);
	PatchMe(0x400000 + 0x002A294D, 0x90);
	PatchMe(0x400000 + 0x002A294E, 0x90);
	PatchMe(0x400000 + 0x002A294F, 0x90);
	PatchMe(0x400000 + 0x002A2950, 0x90);
	PatchMe(0x400000 + 0x002A2951, 0x90);
	PatchMe(0x400000 + 0x002A2952, 0x90);
	PatchMe(0x400000 + 0x002A2953, 0x90);
	PatchMe(0x400000 + 0x002A2954, 0x90);
	PatchMe(0x400000 + 0x002A2955, 0x90);
	PatchMe(0x400000 + 0x002A2956, 0x90);
	PatchMe(0x400000 + 0x002A2957, 0x90);
	PatchMe(0x400000 + 0x002A2958, 0x90);
	PatchMe(0x400000 + 0x002A2959, 0x90);
	PatchMe(0x400000 + 0x002A295A, 0x90);
	PatchMe(0x400000 + 0x002A295B, 0x90);
	PatchMe(0x400000 + 0x002A295C, 0x90);
	PatchMe(0x400000 + 0x002A295D, 0x90);
	PatchMe(0x400000 + 0x002A295E, 0x90);
	PatchMe(0x400000 + 0x002A295F, 0x90);
	PatchMe(0x400000 + 0x002A2960, 0x90);
	PatchMe(0x400000 + 0x002A2961, 0x90);
	PatchMe(0x400000 + 0x002A2962, 0x90);
	PatchMe(0x400000 + 0x002A2963, 0x90);
	PatchMe(0x400000 + 0x002A2964, 0x90);
	PatchMe(0x400000 + 0x002A2965, 0x90);
	PatchMe(0x400000 + 0x002A2966, 0x90);
	PatchMe(0x400000 + 0x002A2967, 0x90);
	PatchMe(0x400000 + 0x002A2968, 0x90);
	PatchMe(0x400000 + 0x002A2969, 0x90);
	PatchMe(0x400000 + 0x002A296A, 0x90);
	PatchMe(0x400000 + 0x002A296B, 0x90);
	PatchMe(0x400000 + 0x002A296C, 0x90);
	PatchMe(0x400000 + 0x002A296D, 0x90);
	PatchMe(0x400000 + 0x002A296E, 0x90);
	PatchMe(0x400000 + 0x002A296F, 0x90);
	PatchMe(0x400000 + 0x002A2970, 0x90);
	PatchMe(0x400000 + 0x002A2971, 0x90);
	PatchMe(0x400000 + 0x002A2972, 0x90);
	PatchMe(0x400000 + 0x002A2973, 0x90);
	PatchMe(0x400000 + 0x002A2974, 0x90);
	PatchMe(0x400000 + 0x002A2975, 0x90);
	PatchMe(0x400000 + 0x002A2976, 0x90);
	PatchMe(0x400000 + 0x002A2977, 0x90);
	PatchMe(0x400000 + 0x002A2978, 0x90);
	PatchMe(0x400000 + 0x002A2979, 0x90);
	PatchMe(0x400000 + 0x002A297A, 0x90);
	PatchMe(0x400000 + 0x002A297B, 0x90);
	PatchMe(0x400000 + 0x002A297C, 0x90);
	PatchMe(0x400000 + 0x002A297D, 0x90);
	PatchMe(0x400000 + 0x002A297E, 0x90);
	PatchMe(0x400000 + 0x002A297F, 0x90);
	PatchMe(0x400000 + 0x002A2980, 0x90);
	PatchMe(0x400000 + 0x002A2981, 0x90);
	PatchMe(0x400000 + 0x002A2982, 0x90);
	PatchMe(0x400000 + 0x002A2983, 0x90);
	PatchMe(0x400000 + 0x002A2984, 0x90);
	PatchMe(0x400000 + 0x002A2985, 0x90);
	PatchMe(0x400000 + 0x002A2986, 0x90);
	PatchMe(0x400000 + 0x002A2987, 0x90);
	PatchMe(0x400000 + 0x002A2988, 0x90);
	PatchMe(0x400000 + 0x002A2989, 0x90);
	PatchMe(0x400000 + 0x002A298A, 0x90);
	PatchMe(0x400000 + 0x002A298B, 0x90);
#endif
}


void char_select_override(void)
{

	// We override the constructor list
	client_override_constructor(CHARSEL_INTRO, &static_const_intro);
	client_override_constructor(CHARSEL_CREATE, &static_const_create);

	client_override_constructor(CHARSEL_CHARPOS_1, &static_const_char_1);
	client_override_constructor(CHARSEL_CHARPOS_2, &static_const_char_2);


	DWORD dwProtect = 0;
		// Unprotect first
	if (!VirtualProtect(
		(LPVOID)CHARSEL_CHARACTER_POSITION_YOFFSET,
		sizeof(double),
		PAGE_EXECUTE_READWRITE,
		&dwProtect)) {

		perror("Failed to unprotect memory\n");
		printf("Failed to unprotect memory\n");
		return;
	}

	*((double*)(CHARSEL_CHARACTER_POSITION_YOFFSET)) = 0;

	// aannnd protect
	VirtualProtect((LPVOID)CHARSEL_CHARACTER_POSITION_YOFFSET, sizeof(double), dwProtect, NULL);
	char_select_stuff();
}


void static_const_intro(void) 
{
	Keyframe* intro_start = (Keyframe*)CHARSEL_KEYFRAME_START;
	
	intro_start->position.X = 486.626f;
	intro_start->position.Y = 10.3903f;
	intro_start->position.Z = 224.418f;

	intro_start->rotation.X = 0.099325f;
	intro_start->rotation.Y = 0.752854f;
	intro_start->rotation.Z = 0;

	intro_start->distance = 80.0f;
	intro_start->time = 0; // time is preset and ignored


	
	Keyframe* intro_end = (Keyframe*)CHARSEL_KEYFRAME_END;

	intro_end->position.X = 502.171f;
	intro_end->position.Y = 8.12451f;
	intro_end->position.Z = 241.01f;

	intro_end->rotation.X = 0.099325f;
	intro_end->rotation.Y = 0.752854f;
	intro_end->rotation.Z = 0;

	intro_end->distance = 80.0f;
	intro_end->time = 5.0f; // time is preset and ignored
	
}

void static_const_create(void) {
	Keyframe* create_1 = (Keyframe*)CHARSEL_KEYFRAME_CREATE_1;
	
	create_1->position.X = 502.171f;
	create_1->position.Y = 8.12451f;
	create_1->position.Z = 241.01f;

	create_1->rotation.X = 0.099325f;
	create_1->rotation.Y = 0.752854f;
	create_1->rotation.Z = 0;

	create_1->distance = 80.0f;
	create_1->time = 0.0f; // time is preset and ignored


	Keyframe* create_2 = (Keyframe*)CHARSEL_KEYFRAME_CREATE_2;
	
	create_2->position.X = 504.531f;
	create_2->position.Y = 8.12451f;
	create_2->position.Z = 235.514f;

	create_2->rotation.X = 0.099325f;
	create_2->rotation.Y = 1.16525f;
	create_2->rotation.Z = 0;

	create_2->distance = 80.0;
	create_2->time = 6.0f; // time is preset and ignored


	Keyframe* create_3 = (Keyframe*)CHARSEL_KEYFRAME_CREATE_3;
	
	create_3->position.X = 478.134f;
	create_3->position.Y = 10.7672f;
	create_3->position.Z = 231.172f;

	create_3->rotation.X = 0.099325f;
	create_3->rotation.Y = 1.33341f;
	create_3->rotation.Z = 0;

	create_3->distance = 80.0f;
	create_3->time = 10.0f; // time is preset and ignored


	Keyframe* create_4 = (Keyframe*)CHARSEL_KEYFRAME_CREATE_4;
	
	create_4->position.X = 376.72f;
	create_4->position.Y = 7.73251f;
	create_4->position.Z = 204.31f;

	create_4->rotation.X = 0.8f;
	create_4->rotation.Y = 0.8088f;
	create_4->rotation.Z = 0;

	create_4->distance = 6.7f;
	create_4->time = 15.0f; // time is preset and ignored
}

void static_const_char_1(void) {
	Character3D* character =  (Character3D*)CHARSEL_CHARACTER_POSITION_1;

	character->location.X = 460.835f;
	character->location.Y = 0.626249f;
	character->location.Z = 233.131f;

	character->rotation = -0.95493f;

}

void static_const_char_2(void) {
	Character3D* character =  (Character3D*)CHARSEL_CHARACTER_POSITION_2;

	character->location.X = 490.574f;
	character->location.Y = 0.985927f;
	character->location.Z = 194.903f;

	character->rotation = -0.827606f;

}