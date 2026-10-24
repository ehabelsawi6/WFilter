#ifndef UI_CUSTOMLABEL_DEF
#define UI_CUSTOMLABEL_DEF
#include "../../../stdafx.h"
#include "../../D3DEngine.h"
using namespace OSHGui;
using namespace OSHGui::Drawing;
class CustomLabel : public Label
{
public:
	CustomLabel();
	~CustomLabel();
protected:
	virtual void PopulateGeometry() override;

private:
	OSHGui::Drawing::FontPtr m_Font;

};
#endif // !UI_CustomLabel_DEF