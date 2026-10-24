#include "CustomButton.h"
#include "../../../GameMain/GameMain.h"

void CustomButton::PopulateGeometry()
{
	if (this->image && isVisible_)
	{
		Graphics g(*geometry_);
		if (this->isMouseDown && this->image_press || this->isInside_)
		{
			if (this->image_tooltip)
			{
				g.DrawImage(this->image_tooltip, Color::FromRGB(255, 255, 255), RectangleI(PointI(-image_tooltip->GetSize().Width, (this->GetSize().Height / 2) - (this->image_tooltip->GetSize().Height / 2)), this->image_tooltip->GetSize()));
				g.DrawString(this->m_Label->GetText(), this->m_Font, Color::White(), PointI(-((image_tooltip->GetSize().Width) + (m_Label->GetSize().Width / 2)) + (this->m_Label->GetSize().Width / 2) + 12, (this->GetSize().Height / 2) - (this->image_tooltip->GetSize().Height / 2) + (this->m_Label->GetSize().Height / 2)));
			}

		}
		if (this->isMouseDown && this->image_press)
			g.DrawImage(this->image_press, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, 0), this->image->GetSize()));
		else if (this->isInside_ && this->image_focus)
		{
			g.DrawImage(this->image_focus, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, 0), this->image->GetSize()));
		}
		else
			g.DrawImage(this->image, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, 0), this->image->GetSize()));
	}

}
void CustomButton::OnMouseLeaveHandler(Control* control)
{
	this->isMouseDown = false;
}
void CustomButton::OnMouseUpHandler(Control* control)
{
	this->isMouseDown = false;
}
void CustomButton::OnMouseEnterHandler(Control* control)
{
	if (this->isMouseDown)
		this->Focus();
}
void CustomButton::OnMouseDownHandler(Control* control)
{
	this->isMouseDown = true;
}
CustomButton::CustomButton(ImagePtr img, ImagePtr focus, ImagePtr press, ImagePtr tooltip_img, std::string* tooltip_text)
{
	this->image = img;
	this->image_focus = focus;
	this->image_press = press;
	this->image_tooltip = tooltip_img;
	if (image_tooltip)
	{
		this->m_Label = new Label();
		this->m_Label->SetText(tooltip_text->c_str());
		m_Font = FontManager::LoadFont("Tahoma", 10, false); //Arial, 9PT, no anti-aliasing
	}
	this->SetSize(img->GetSize());
	this->GetMouseDownEvent() += MouseDownEventHandler(std::bind(&CustomButton::OnMouseDownHandler, this, std::placeholders::_1));
	this->GetMouseUpEvent() += MouseUpEventHandler(std::bind(&CustomButton::OnMouseUpHandler, this, std::placeholders::_1));
	this->GetMouseLeaveEvent() += MouseLeaveEventHandler(std::bind(&CustomButton::OnMouseLeaveHandler, this, std::placeholders::_1));
	this->GetMouseEnterEvent() += MouseEnterEventHandler(std::bind(&CustomButton::OnMouseEnterHandler, this, std::placeholders::_1));
	this->GetClickEvent() += ClickEventHandler([&](Control* sender) {
		g_CGEffSoundBody->GetSoundBody()->DoSound(L"snd_button_click");
		});
}
void CustomButton::UpdateImage(const ImagePtr& newImg)
{
	this->SetVisible(false);
	this->image = newImg;
	this->SetVisible(true);
}
CustomButton::~CustomButton()
{
	printf("Am i destroyed?\n");
}