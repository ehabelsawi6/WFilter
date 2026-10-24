/*
 * OldSchoolHack GUI
 *
 * by KN4CK3R https://www.oldschoolhack.me/
 *
 * See license in OSHGui.hpp
 */

#include "Form.hpp"
#include "../Application.hpp"
#include "../FormManager.hpp"
#include "../Misc/Exceptions.hpp"
#include "Label.hpp"
#include "Panel.hpp"
#include <math.h>
#include <windows.h>
extern OSHGui::Misc::RawDataContainer right_up_borderdata;
extern OSHGui::Misc::RawDataContainer left_up_borderdata;
extern OSHGui::Misc::RawDataContainer up_centerdata;
extern OSHGui::Misc::RawDataContainer left_bottom_begindata;
extern OSHGui::Misc::RawDataContainer right_bottom_enddata;
extern OSHGui::Misc::RawDataContainer bottom_centerdata;
extern OSHGui::Misc::RawDataContainer left_borderdata;
extern OSHGui::Misc::RawDataContainer right_borderdata;
extern OSHGui::Misc::RawDataContainer contentdata;
extern OSHGui::Misc::RawDataContainer com_windowclosedata;
extern OSHGui::Misc::RawDataContainer com_windowclose_focusdata;
extern OSHGui::Misc::RawDataContainer com_windowclose_pressdata;
namespace OSHGui
{
	//---------------------------------------------------------------------------
	//static attributes
	//---------------------------------------------------------------------------
	const Drawing::PointI Form::DefaultLocation(50, 50);
	const Drawing::SizeI Form::DefaultSize(300, 300);
	//---------------------------------------------------------------------------
	//Constructor
	//---------------------------------------------------------------------------
	Form::Form()
		: isModal_(false),
		dialogResult_(DialogResult::None)
	{
		type_ = ControlType::Form;

		parent_ = nullptr;//this;
		isVisible_ = false;
		isEnabled_ = false;
		isFocusable_ = false;
		hasPanel_ = true;
		containerPanel_ = new Panel();
		containerPanel_->SetLocation(Drawing::PointI(DefaultBorderPadding, DefaultBorderPadding + CaptionBar::DefaultCaptionBarHeight));
		containerPanel_->SetBackColor(Drawing::Color::Empty());
		AddSubControl(containerPanel_);

		SetLocation(DefaultLocation);
		SetSize(DefaultSize);

		using namespace Drawing;
		this->top_left = Image::FromMemory(left_up_borderdata);
		this->top_right = Image::FromMemory(right_up_borderdata);
		this->top_center = Image::FromMemory(up_centerdata);
		this->bottom_left = Image::FromMemory(left_bottom_begindata);
		this->bottom_right = Image::FromMemory(right_bottom_enddata);
		this->bottom_center = Image::FromMemory(bottom_centerdata);
		this->centerLeft = Image::FromMemory(left_borderdata);
		this->centerRight = Image::FromMemory(right_borderdata);
		this->center = Image::FromMemory(contentdata);
		ApplyStyle(Application::Instance().GetStyle());
	}

	bool Form::IsActivated()
	{
		return isFocusable_;
	}

	//---------------------------------------------------------------------------
	//Getter/Setter
	//---------------------------------------------------------------------------
	void Form::SetSize(const Drawing::SizeI& size)
	{
		Control::SetSize(size);
		if (this->hasCaptionBar_)
			captionBar_->SetSize(size);
		if (size.Height > 0 && size.Width > 0)
			containerPanel_->SetSize(size.InflateEx(-DefaultBorderPadding * 2, -DefaultBorderPadding * 2 - CaptionBar::DefaultCaptionBarHeight));
		else
			containerPanel_->SetSize(0, 0);

		if (!this->hasPanel_)
			containerPanel_->SetPanelDrawable(false);
	}
	//---------------------------------------------------------------------------
	void Form::SetText(const Misc::AnsiString& text)
	{
		if (hasCaptionBar_)
			captionBar_->SetText(text);
	}
	//---------------------------------------------------------------------------
	const Misc::AnsiString& Form::GetText() const
	{
		return captionBar_->GetText();
	}
	//---------------------------------------------------------------------------
	void Form::SetForeColor(const Drawing::Color& color)
	{
		Control::SetForeColor(color);
		if (hasCaptionBar_)
			captionBar_->SetForeColor(color);
	}
	//---------------------------------------------------------------------------
	const std::deque<Control*>& Form::GetControls() const
	{
		return containerPanel_->GetControls();
	}
	//---------------------------------------------------------------------------
	void Form::SetDialogResult(DialogResult result)
	{
		dialogResult_ = result;
	}
	//---------------------------------------------------------------------------
	DialogResult Form::GetDialogResult() const
	{
		return dialogResult_;
	}
	//---------------------------------------------------------------------------
	FormClosingEvent& Form::GetFormClosingEvent()
	{
		return formClosingEvent_;
	}
	//---------------------------------------------------------------------------
	bool Form::IsModal() const
	{
		return isModal_;
	}
	//---------------------------------------------------------------------------
	//Runtime-Functions
	//---------------------------------------------------------------------------
	void Form::AddControl(Control* control)
	{
		containerPanel_->AddControl(control);
	}
	//void Form::RemoveControl(Control* control)
	//{
	//	containerPanel_->RemoveControl(control);
	//}
	//---------------------------------------------------------------------------
	void Form::Show(const std::shared_ptr<Form>& instance)
	{
		instance_ = std::weak_ptr<Form>(instance);
		sInstance = instance;
		Application::Instance().formManager_.RegisterForm(instance);

		SetVisible(true);
		SetEnabled(true);

		//CalculateAbsoluteLocation();
	}
	//---------------------------------------------------------------------------
	void Form::ShowDialog(const std::shared_ptr<Form>& instance)
	{
		ShowDialog(instance, std::function<void()>());
	}
	//---------------------------------------------------------------------------
	void Form::ShowDialog(const std::shared_ptr<Form>& instance, const std::function<void()>& closeFunction)
	{
		isModal_ = true;

		instance_ = std::weak_ptr<Form>(instance);

		Application::Instance().formManager_.RegisterForm(instance_.lock(), closeFunction);

		SetVisible(true);
		SetEnabled(true);

		CalculateAbsoluteLocation();
	}
	//---------------------------------------------------------------------------
	void Form::Close()
	{  
		bool canClose = true;
		if (canClose)
		{
			for (const auto &ctrl : GetControls())
			{
				ctrl->SetEnabled(false);
				RemoveControl(ctrl);
			}
			this->SetEnabled(false);
			if (GetVisible())
				SetVisible(false);
			formClosingEvent_.Invoke(this, canClose);
			Application::Instance().formManager_.UnregisterForm(instance_.lock());
		}
	}
	void Form::SetPanelEnabled(bool Enabled)
	{
		this->hasPanel_ = Enabled;
	}
	void Form::SetCaptionBar(bool hasCaption)
	{
		this->hasCaptionBar_ = hasCaption;

		if (this->hasCaptionBar_)
		{
			captionBar_ = new CaptionBar();
			captionBar_->SetLocation(Drawing::PointI(0, 0));
			AddSubControl(captionBar_);
		}
	}
	void Form::DrawSelf(Drawing::RenderContext& context)
	{
		Control::DrawSelf(context);
		if (hasCaptionBar_)
			captionBar_->Render();
		containerPanel_->Render();
	}
	//---------------------------------------------------------------------------
	void Form::PopulateGeometry()
	{
		using namespace Drawing;
		Graphics g(*geometry_);
		auto windowWidth = this->GetSize().Width;;
		auto windowHeight = this->GetSize().Height;
		if (windowWidth == 0 || windowHeight == 0)
			return;
		RectangleI imageRect;
		RectangleI drawRect;
		RectangleI rect = RectangleI(PointI(8, 21), SizeI(windowWidth - 8, windowHeight - 21));
		auto rectLocation = rect.GetLocation();

		for (int x = rectLocation.X; x < rect.GetRight(); x += 128)
		{
			for (int y = rectLocation.Y; y < rect.GetBottom(); y += 128)
			{
				drawRect = RectangleI(x, y, std::min(128, rect.GetRight() - x), std::min(128, rect.GetBottom() - y));
				imageRect = RectangleI(0, 0, drawRect.GetWidth(), drawRect.GetHeight());

				g.DrawImage(this->center, Color::FromRGB(255, 255, 255), drawRect, imageRect);
			}
		}

		g.DrawImage(top_left, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, 0), SizeI(13, 42)));

		auto partSizeTop = 13;

		for (auto i = 0; i <= (windowWidth - 26) / 35; i++)
		{
			if (partSizeTop + 35 > windowWidth)
			{
				g.DrawImage(top_center, Color::FromRGB(255, 255, 255), RectangleI(PointI(partSizeTop, 0), SizeI(windowWidth - partSizeTop - 13, 42)));
				partSizeTop = windowWidth - 13;
			}
			else
			{
				g.DrawImage(top_center, Color::FromRGB(255, 255, 255), RectangleI(PointI(partSizeTop, 0), SizeI(35, 42)));
				partSizeTop += 35;
			}
		}
		g.DrawImage(top_right, Color::FromRGB(255, 255, 255), RectangleI(PointI(windowWidth - 13, 0), SizeI(13, 42)));
		g.DrawImage(bottom_left, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, windowHeight - 14), SizeI(14, 14)));

		auto partSizeBottom = 14;

		for (auto i = 0; i <= ((windowWidth - 28) / 35); i++)
		{
			if (partSizeBottom + 35 > windowWidth)
			{
				g.DrawImage(bottom_center, Color::FromRGB(255, 255, 255), RectangleI(PointI(partSizeBottom, windowHeight - 14), SizeI(windowWidth - partSizeBottom - 14, 14)));
				partSizeBottom = windowWidth - 14;
			}
			else
			{
				g.DrawImage(bottom_center, Color::FromRGB(255, 255, 255), RectangleI(PointI(partSizeBottom, windowHeight - 14), SizeI(35, 14)));
				partSizeBottom += 35;
			}
		}

		g.DrawImage(bottom_right, Color::FromRGB(255, 255, 255), RectangleI(PointI(windowWidth - 14, windowHeight - 14), SizeI(14, 14)));

		auto centerLeftBorderPartSize = 42;

		for (auto i = 0; i <= (windowHeight - (42 + 14)) / 66; i++)
		{
			if (centerLeftBorderPartSize + 66 > windowHeight)
			{
				auto h = windowHeight - centerLeftBorderPartSize - 8;

				g.DrawImage(centerLeft, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, centerLeftBorderPartSize), SizeI(8, h)));
				centerLeftBorderPartSize = windowHeight - 14;
			}
			else
			{
				g.DrawImage(centerLeft, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, centerLeftBorderPartSize), SizeI(8, 66)));
				centerLeftBorderPartSize += 66;
			}
		}

		auto centerRightBorderPartSize = 42;

		for (auto i = 0; i <= (windowHeight - (42 + 14)) / 66; i++)
		{
			if (centerRightBorderPartSize + 66 > windowHeight)
			{
				g.DrawImage(centerRight, Color::FromRGB(255, 255, 255), RectangleI(PointI(windowWidth - 8, centerRightBorderPartSize), SizeI(8, windowHeight - centerRightBorderPartSize - 8)));
				centerRightBorderPartSize = windowHeight - 14;
			}
			else
			{
				g.DrawImage(centerRight, Color::FromRGB(255, 255, 255), RectangleI(PointI(windowWidth - 8, centerRightBorderPartSize), SizeI(8, 66)));
				centerRightBorderPartSize += 66;
			}
		}

	}
	//---------------------------------------------------------------------------
	//Form::Captionbar::Button
	//---------------------------------------------------------------------------
	const Drawing::SizeI Form::CaptionBar::CaptionBarButton::DefaultSize(16, 16);
	const Drawing::PointI Form::CaptionBar::CaptionBarButton::DefaultCrossOffset(16, 16);
	//---------------------------------------------------------------------------
	Form::CaptionBar::CaptionBarButton::CaptionBarButton()
	{
		this->isFocusable_ = true;
		this->SetSize(DefaultSize);
		this->closebutton = Drawing::Image::FromMemory(com_windowclosedata);
		this->closebutton_default = this->closebutton;
		this->closebutton_focus = Drawing::Image::FromMemory(com_windowclose_focusdata);
		this->closebutton_press = Drawing::Image::FromMemory(com_windowclose_pressdata);
	}
	//---------------------------------------------------------------------------
	//void Form::CaptionBar::CaptionBarButton::CalculateAbsoluteLocation()
	//{
	//	Control::CalculateAbsoluteLocation();

	//	crossAbsoluteLocation_ = absoluteLocation_ + DefaultCrossOffset;

	//	geometry_->SetTranslation(Drawing::Vector(crossAbsoluteLocation_.X, crossAbsoluteLocation_.Y, 0.0f));
	//}
	//---------------------------------------------------------------------------
	void Form::CaptionBar::CaptionBarButton::OnMouseDown(const MouseMessage& mouse)
	{
		Control::OnMouseDown(mouse);
		this->isClicked_ = true;
	}
	//---------------------------------------------------------------------------
	void Form::CaptionBar::CaptionBarButton::OnMouseUp(const MouseMessage& mouse)
	{
		Control::OnMouseUp(mouse);
		auto owner = static_cast<Form*>(parent_->GetParent());
		this->isClicked_ = false;
		owner->Close();
	}
	void Form::CaptionBar::CaptionBarButton::OnMouseLeave(const MouseMessage& mouse)
	{
		Control::OnMouseLeave(mouse);
		this->isClicked_ = false;
	}
	//---------------------------------------------------------------------------
	void Form::CaptionBar::CaptionBarButton::PopulateGeometry()
	{
		using namespace Drawing;
		Graphics g(*geometry_);
		if (isClicked_)
			g.DrawImage(closebutton_press, Color::FromRGB(255, 255, 255), PointI(0, 0), RectangleI(PointI(0, 0), SizeI(16, 16)));
		else if (isInside_)
			g.DrawImage(closebutton_focus, Color::FromRGB(255, 255, 255), PointI(0, 0), RectangleI(PointI(0, 0), SizeI(16, 16)));
		else
			g.DrawImage(closebutton, Color::FromRGB(255, 255, 255), PointI(0, 0), RectangleI(PointI(0, 0), SizeI(16, 16)));
	}
	//---------------------------------------------------------------------------
	//Form::Captionbar
	//---------------------------------------------------------------------------
	const Drawing::PointI Form::CaptionBar::DefaultTitleOffset(4, 4);
	//---------------------------------------------------------------------------
	Form::CaptionBar::CaptionBar()
	{
		isFocusable_ = false;
		drag_ = false;
		titleLabel_ = new Label();
		titleLabel_->SetBackColor(Drawing::Color::Empty());
		AddSubControl(titleLabel_);

		closeButton_ = new CaptionBarButton();
		closeButton_->SetBackColor(Drawing::Color::Empty());
		closeButton_->SetSize(16, 16);

		AddSubControl(closeButton_);
	}
	//---------------------------------------------------------------------------
	void Form::CaptionBar::SetSize(const Drawing::SizeI& size)
	{
		Control::SetSize(Drawing::SizeI(size.Width, DefaultCaptionBarHeight));

		OSHGui::Drawing::Graphics g(*geometry_);

		auto labelSize = this->titleLabel_->GetSize();

		titleLabel_->SetLocation(Drawing::PointI(((size.Width - labelSize.Width - this->titleLabel_->GetText().length()) / 2), 9));
		closeButton_->SetLocation(Drawing::PointI(size.Width - CaptionBarButton::DefaultSize.Width - DefaultButtonPadding + 5, 9));
	}
	//---------------------------------------------------------------------------
	void Form::CaptionBar::SetText(const Misc::AnsiString& text)
	{
		titleLabel_->SetText(text);
		auto size = this->GetSize();
		auto labelSize = this->titleLabel_->GetSize();
		titleLabel_->SetLocation(Drawing::PointI(Drawing::PointI(((size.Width - labelSize.Width - this->titleLabel_->GetText().length()) / 2), 9)));
	}
	//---------------------------------------------------------------------------
	const Misc::AnsiString& Form::CaptionBar::GetText() const
	{
		return titleLabel_->GetText();
	}
	//---------------------------------------------------------------------------
	void Form::CaptionBar::SetForeColor(const Drawing::Color& color)
	{
		Control::SetForeColor(color);

		closeButton_->SetForeColor(color);
		titleLabel_->SetForeColor(color);
	}
	//---------------------------------------------------------------------------
	void Form::CaptionBar::DrawSelf(Drawing::RenderContext& context)
	{
		Control::DrawSelf(context);

		titleLabel_->Render();
		closeButton_->Render();
	}
	//---------------------------------------------------------------------------
	void Form::CaptionBar::OnMouseDown(const MouseMessage& mouse)
	{
		Control::OnMouseDown(mouse);
		drag_ = true;
		OnGotMouseCapture();
		dragStart_ = mouse.GetLocation();
	}
	//---------------------------------------------------------------------------
	void Form::CaptionBar::OnMouseMove(const MouseMessage& mouse)
	{
		Control::OnMouseMove(mouse);
		this->closeButton_->closebutton = this->closeButton_->closebutton_default;
		if (drag_)
		{
			GetParent()->SetLocation(GetParent()->GetLocation() + (mouse.GetLocation() - dragStart_));
			dragStart_ = mouse.GetLocation();
		}
	}
	//---------------------------------------------------------------------------
	void Form::CaptionBar::OnMouseUp(const MouseMessage& mouse)
	{
		Control::OnMouseUp(mouse);

		if (drag_)
		{
			drag_ = false;
			OnLostMouseCapture();
		}
	}
	//---------------------------------------------------------------------------
}
