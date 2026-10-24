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
// along with this program.  If not, see <http://www.gnu.org/licenses/>

#include "static_constructor.h"

#include <Windows.h>
#include <stdio.h>

extern HMODULE sro_client;

#define STATIC_CONSTRUCTOR_LIST_START 0x98065C
#define STATIC_CONSTRUCTOR_LIST_END   0x981800
#define STATIC_CONSTRUCTOR_LIST_SIZE (STATIC_CONSTRUCTOR_LIST_END - STATIC_CONSTRUCTOR_LIST_START)



int client_override_constructor(int id, static_constructor function) {
	DWORD dwProtect = 0;

	if (id < 0) {
		return 0;
	}

	if (id > STATIC_CONSTRUCTOR_LIST_SIZE) {
		return 0;
	}

	static_constructor* list = (static_constructor*)((int)sro_client + STATIC_CONSTRUCTOR_LIST_START);
	
	//printf("[StaticConst] Have list at %08x\n", list);

	//printf("[StaticConst] Unprotecting %d bytes of memory at %08x\n", sizeof(static_constructor*), &list[id]);

	// Unprotect first
	if (!VirtualProtect(
		(LPVOID)(&(list[id])),
		sizeof(static_constructor*),
		PAGE_EXECUTE_READWRITE,
		&dwProtect)) {

		perror("Failed to unprotect memory\n");
		printf("Failed to unprotect memory\n");
		return 0;
	}
	
	list[id] = function;
	
	// aannnd protect
	VirtualProtect(
		(LPVOID)(&(list[id])),
		sizeof(static_constructor*), dwProtect, NULL);

	return 1;
}


