#ifndef QPROXYLIB_ALCHEMYPATCH
#define QPROXYLIB_ALCHEMYPATCH
#include "../../includes.h"
//00d8ba22 -> 6b 1 byte orig 67

class AlchemyPatch
{
public:
	static void Initialize();
	static void PatchAlchemyValue(BYTE val);
	static void PatchAlchemyImagePath(BYTE val1, BYTE val2, BYTE val3);
private:
};
#endif