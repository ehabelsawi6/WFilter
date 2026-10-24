/*
* OldSchoolHack GUI
*
* by KN4CK3R https://www.oldschoolhack.me/
*
* See license in OSHGui.hpp
*/

#include "ScrollBar.hpp"
#include "../Misc/Exceptions.hpp"
#include "../Misc/Intersection.hpp"


//Textures
extern OSHGui::Misc::RawDataContainer com_scroll_bar_bg_data;
extern OSHGui::Misc::RawDataContainer com_scroll_arrow_up_data;
extern OSHGui::Misc::RawDataContainer com_scroll_arrow_up_focus_data;
extern OSHGui::Misc::RawDataContainer com_scroll_arrow_down_data;
extern OSHGui::Misc::RawDataContainer com_scroll_arrow_down_focus_data;
extern OSHGui::Misc::RawDataContainer com_scroll_button_data;
extern OSHGui::Misc::RawDataContainer com_scroll_button_focus_data;


namespace OSHGui {
	//---------------------------------------------------------------------------
	//static attributes
	//---------------------------------------------------------------------------
	const Drawing::SizeI ScrollBar::DefaultSize(16, 110);
	//---------------------------------------------------------------------------
	//Constructor
	//---------------------------------------------------------------------------
	ScrollBar::ScrollBar()
		: drag_(false),
		value_(0),
		pixelsPerTick_(1.0f),
		maximum_(0) {
		type_ = ControlType::ScrollBar;

		upButton_ = new ScrollBarButton(ScrollBarButton::ScrollBarDirection::Up);
		upButton_->GetClickEvent() += ClickEventHandler([this](Control *control)
		{
			if (value_ > 0) {
				SetValueInternal(value_ - 1);
			}
		});
		AddControl(upButton_);

		downButton_ = new ScrollBarButton(ScrollBarButton::ScrollBarDirection::Down);
		downButton_->GetClickEvent() += ClickEventHandler([this](Control *control)
		{
			if (value_ < maximum_) {
				SetValueInternal(value_ + 1);
			}
		});
		AddControl(downButton_);

		SetSize(DefaultSize);
		trackLocation_ = Drawing::PointI(0, upButton_->GetBottom() -1);

		ApplyStyle(Application::Instance().GetStyle());

		SetMaximum(0); //indirect init

		isFocusable_ = false;

		this->img_scroll_bar_bg = Drawing::Image::FromMemory(com_scroll_bar_bg_data);

		this->img_button = Drawing::Image::FromMemory(com_scroll_button_data);
		this->img_button_focus = Drawing::Image::FromMemory(com_scroll_button_focus_data);
	}

	//---------------------------------------------------------------------------
	//Getter/Setter
	//---------------------------------------------------------------------------
	void ScrollBar::SetSize(const Drawing::SizeI &size) {
		Control::SetSize(size);

		upButton_->SetSize(Drawing::SizeI(upButton_->GetWidth(), upButton_->GetHeight()));
		downButton_->SetSize(Drawing::SizeI(downButton_->GetWidth(), downButton_->GetHeight()));

		downButton_->SetLocation(0, (size.Height) - downButton_->GetHeight());

		trackSize_ = Drawing::SizeI(size.Width, (size.Height) - upButton_->GetHeight());

		sliderSize_.Width = size.Width;
		sliderSize_.Height = trackSize_.Height / (maximum_ + 1);
		if (sliderSize_.Height < MinimumSliderHeight) {
			sliderSize_.Height = MinimumSliderHeight;
		}

		SetValueInternal(value_);
	}

	//---------------------------------------------------------------------------
	void ScrollBar::SetForeColor(const Drawing::Color &color) {
		Control::SetForeColor(color);

		upButton_->SetForeColor(color);
		downButton_->SetForeColor(color);
	}

	//---------------------------------------------------------------------------
	void ScrollBar::SetMaximum(int maximum) {
		if (maximum < 0) {
#ifndef OSHGUI_DONTUSEEXCEPTIONS
			throw Misc::ArgumentOutOfRangeException("maximum");
#endif
			return;
		}

		maximum_ = maximum;

		sliderSize_.Height = trackSize_.Height / (maximum + 1);
		if (sliderSize_.Height < MinimumSliderHeight) {
			sliderSize_.Height = MinimumSliderHeight;
		}

		SetValueInternal(value_ > maximum ? maximum : value_);
	}

	//---------------------------------------------------------------------------
	int ScrollBar::GetMaximum() const {
		return maximum_;
	}

	//---------------------------------------------------------------------------
	void ScrollBar::SetValue(int value) {
		SetValueInternal(value);
	}

	//---------------------------------------------------------------------------
	int ScrollBar::GetValue() const {
		return value_;
	}

	//---------------------------------------------------------------------------
	ScrollEvent &ScrollBar::GetScrollEvent() {
		return scrollEvent_;
	}

	//---------------------------------------------------------------------------
	//Runtime-Functions
	//---------------------------------------------------------------------------
	void ScrollBar::SetValueInternal(int value) {
		pixelsPerTick_ = (trackSize_.Height - sliderSize_.Height) / (maximum_ > 0 ? (float)maximum_ : 1.0f);

		if (value < 0) {
			value = 0;
		}
		if (value > maximum_) {
			value = maximum_;
		}

		if (value_ != value) {
			ScrollEventArgs args(value, value_);

			value_ = value;

			scrollEvent_.Invoke(this, args);
		}

		if (value == maximum_ && maximum_ != 0)
			sliderLocation_.Top = (trackLocation_.Top + (value * pixelsPerTick_)) - 5.8f;
		else
			sliderLocation_.Top = trackLocation_.Top + (value * pixelsPerTick_);
		sliderAbsoluteLocation_.Top = absoluteLocation_.Top + (sliderLocation_.Top);
/*
		value_ == maximum_ ? downButton_->SetVisible( false ) : downButton_->SetVisible( true );
		value_ == 0 ? upButton_->SetVisible( false ) : upButton_->SetVisible( true );*/

		Invalidate();
	}

	//---------------------------------------------------------------------------
	bool ScrollBar::Intersect(const Drawing::PointI &point) const {
		return Intersection::TestRectangle(absoluteLocation_.OffsetEx(0, upButton_->GetHeight()),
			size_.InflateEx(0, upButton_->GetHeight()), point);
	}

	//---------------------------------------------------------------------------
	void ScrollBar::CalculateAbsoluteLocation() {
		Control::CalculateAbsoluteLocation();

		sliderAbsoluteLocation_ = absoluteLocation_ + sliderLocation_;
		trackAbsoluteLocation_ = absoluteLocation_ + trackLocation_;
	}

	//---------------------------------------------------------------------------
	void ScrollBar::ScrollToTop() {
		SetValue(0);
	}

	//---------------------------------------------------------------------------
	void ScrollBar::ScrollToBottom() {
		SetValue(GetMaximum());
	}

	//---------------------------------------------------------------------------
	void ScrollBar::DrawSelf(Drawing::RenderContext &context) {
		Control::DrawSelf(context);

		upButton_->Render();
		downButton_->Render();
	}

	//---------------------------------------------------------------------------
	void ScrollBar::PopulateGeometry() {
		using namespace Drawing;

		Graphics g(*geometry_);

		//g.FillRectangle( Color::FromARGB( 255, 255, 50, 60 ), trackLocation_, trackSize_ );

		//g.FillRectangle( Color::FromARGB( 255, 67, 67, 77 ), sliderLocation_ + PointF( 1, 1 ), sliderSize_ - SizeF( 2, 2 ) );

		auto shit = 16;
		for (size_t i = 0; i < ((upButton_->GetLocation().Y + downButton_->GetLocation().Y) / 16); i++)
		{
			g.DrawImage(img_scroll_bar_bg, Color::FromRGB(255, 255, 255), upButton_->GetLocation() + PointF(0, shit));
			shit += 16;
		}
		if(!isInside_)
			g.DrawImage(img_button, Color::FromRGB(255,255,255), sliderLocation_);
		else
			g.DrawImage(img_button_focus, Color::FromRGB(255,255,255), sliderLocation_);

		//g.FillRectangle(Color::FromARGB(255, 67, 67, 67), sliderLocation_ + PointF(sliderSize_.Width, 1), SizeF(1, sliderSize_.Height - 2));
		//g.FillRectangle(Color::FromARGB(255, 67, 67, 67), sliderLocation_ + PointF(1, sliderSize_.Height - 1), SizeF(sliderSize_.Width - 2, 1));
		//g.FillRectangle(Color::FromARGB(255, 67, 67, 67), sliderLocation_ + PointF(0, 1), SizeF(1, sliderSize_.Height - 2));
		//g.FillRectangle(Color::FromARGB(255, 67, 67, 67), sliderLocation_ + PointF(1, 0), SizeF(sliderSize_.Width, 1));

	}

	//---------------------------------------------------------------------------
	//Event-Handling
	//---------------------------------------------------------------------------
	void ScrollBar::OnMouseDown(const MouseMessage &mouse) {
		Control::OnMouseDown(mouse);

		if (Intersection::TestRectangle(sliderAbsoluteLocation_, sliderSize_, mouse.GetLocation())) {
			drag_ = true;

			OnGotMouseCapture();
		}
	}

	//---------------------------------------------------------------------------
	void ScrollBar::OnMouseMove(const MouseMessage &mouse) {
		Control::OnMouseMove(mouse);

		if (drag_) {
			if (maximum_ >= 1) {
				const auto valuePerPixel = static_cast<float>(maximum_) / (trackSize_.Height - sliderSize_.Height);

				auto yPos = mouse.GetLocation().Y - trackAbsoluteLocation_.Top - sliderSize_.Height / 2;
				if (yPos < 0) {
					yPos = 0;
				}
				else if (yPos + sliderSize_.Height > trackSize_.Height) {
					yPos = trackSize_.Height - sliderSize_.Height;
				}

				SetValueInternal(yPos * valuePerPixel);
			}
		}
	}

	//---------------------------------------------------------------------------
	void ScrollBar::OnMouseUp(const MouseMessage &mouse) {
		Control::OnMouseUp(mouse);

		if (drag_) {
			drag_ = false;

			OnLostMouseCapture();
		}
	}

	//---------------------------------------------------------------------------
	void ScrollBar::OnMouseClick(const MouseMessage &mouse) {
		Control::OnMouseClick(mouse);

		if (!drag_ && maximum_ > 1) {
			if (Intersection::TestRectangle(trackAbsoluteLocation_, trackSize_, mouse.GetLocation())) {
				const auto valuePerPixel = static_cast<float>(maximum_) / (trackSize_.Height - sliderSize_.Height);
				const auto yPos = mouse.GetLocation().Y - trackAbsoluteLocation_.Top - sliderSize_.Height / 2;
				SetValueInternal(yPos * valuePerPixel + 0.5f);
			}
		}
	}

	//---------------------------------------------------------------------------
	void ScrollBar::OnMouseScroll(const MouseMessage &mouse) {
		Control::OnMouseScroll(mouse);

		SetValueInternal(value_ + mouse.GetDelta());
	}

	//---------------------------------------------------------------------------
	//ScrollBar::ScrollBarButton
	//---------------------------------------------------------------------------
	const Drawing::SizeI ScrollBar::ScrollBarButton::DefaultSize(16, 16);
	//---------------------------------------------------------------------------
	ScrollBar::ScrollBarButton::ScrollBarButton(ScrollBarDirection direction)
		: direction_(direction) {
		SetLocation(0, 0);
		SetSize(DefaultSize);
		this->img_scroll_arrow_down = Drawing::Image::FromMemory(com_scroll_arrow_down_data);
		this->img_scroll_arrow_down_focus = Drawing::Image::FromMemory(com_scroll_arrow_down_focus_data);
		this->img_scroll_arrow_up = Drawing::Image::FromMemory(com_scroll_arrow_up_data);
		this->img_scroll_arrow_up_focus = Drawing::Image::FromMemory(com_scroll_arrow_up_focus_data);
	}

	//---------------------------------------------------------------------------
	void ScrollBar::ScrollBarButton::SetSize(const Drawing::SizeI &size) {
		Control::SetSize(size);
	}

	//---------------------------------------------------------------------------
	void ScrollBar::ScrollBarButton::PopulateGeometry() {
		using namespace Drawing;

		Graphics g(*geometry_);

		//const auto color = isInside_ ? GetForeColor() + Color( 0, 50, 50, 60 ) : GetForeColor();

		if (direction_ == ScrollBarDirection::Up) {
			if (!isInside_)
				g.DrawImage(img_scroll_arrow_up, Color::FromRGB(255, 255, 255), iconLocation_);
			else
				g.DrawImage(img_scroll_arrow_up_focus, Color::FromRGB(255, 255, 255), iconLocation_);
		}
		else {
			if (!isInside_)
				g.DrawImage(img_scroll_arrow_down, Color::FromRGB(255, 255, 255), iconLocation_);
			else
				g.DrawImage(img_scroll_arrow_down_focus, Color::FromRGB(255, 255, 255), iconLocation_);

		}
	}

	//---------------------------------------------------------------------------
}
