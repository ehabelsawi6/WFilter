#ifndef CMESSENGER_H
#define CMESSENGER_H
class CMessenger
{
public:
	char pad_0000[8]; //0x0000
	class CGObjPC* CGObjPC; //0x0008
	char pad_000C[28]; //0x000C
}; //Size: 0x0028

#endif