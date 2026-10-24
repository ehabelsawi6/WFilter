#ifndef CGCHARAUTONAVIGATOR_H
#define CGCHARAUTONAVIGATOR_H

class CGCharAutoNavigator
{
public:
	char pad_0000[4]; //0x0000
	class CGObjPC* CObjPC; //0x0004
	char pad_0008[20]; //0x0008
}; //Size: 0x001C

#endif