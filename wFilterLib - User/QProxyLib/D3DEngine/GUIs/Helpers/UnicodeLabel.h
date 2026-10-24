#ifndef UI_UnicodeLabel_DEF
#define UI_UnicodeLabel_DEF
#include "../../../stdafx.h"
#include "../../D3DEngine.h"
using namespace OSHGui;
using namespace OSHGui::Drawing;
class UnicodeLabel : public Label
{
public:
    UnicodeLabel();
    ~UnicodeLabel();
protected:
    virtual void PopulateGeometry() override;

private:
    OSHGui::Drawing::FontPtr m_Font;

};
#endif // !UI_CustomLabel_DEF