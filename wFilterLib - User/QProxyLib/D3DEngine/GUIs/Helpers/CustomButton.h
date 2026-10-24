#ifndef UI_CUSTOMBUTTON_DEF
#define UI_CUSTOMBUTTON_DEF
#include "../../../stdafx.h"
#include "../../D3DEngine.h"
using namespace OSHGui;
using namespace OSHGui::Drawing;
class CustomButton : public Button
{
public:
	void UpdateImage(const ImagePtr& img);
	CustomButton(ImagePtr img = nullptr, ImagePtr focus = nullptr, ImagePtr press = nullptr, ImagePtr tooltip_img = nullptr, std::string* tooltip_text = nullptr);
	~CustomButton();
protected:
	virtual void PopulateGeometry() override;

private:
	ImagePtr image;
	ImagePtr image_focus;
	ImagePtr image_press;
	ImagePtr image_tooltip;
	bool isMouseDown;
	void OnMouseDownHandler(Control* control);
	void OnMouseUpHandler(Control* control);
	void OnMouseLeaveHandler(Control* control);
	void OnMouseEnterHandler(Control* control);
	Label* m_Label;
	OSHGui::Drawing::FontPtr m_Font;

};
#endif // !UI_CUSTOMBUTTON_DEF