/*
* OldSchoolHack GUI
*
* by KN4CK3R https://www.oldschoolhack.me/
*
* See license in OSHGui.hpp
*/

#include "Button.hpp"
#include "../Misc/Exceptions.hpp"
extern OSHGui::Misc::RawDataContainer com_button_leftdata;
extern OSHGui::Misc::RawDataContainer com_button_centerdata;
extern OSHGui::Misc::RawDataContainer com_button_rightdata;
extern OSHGui::Misc::RawDataContainer com_button_left_focusdata;
extern OSHGui::Misc::RawDataContainer com_button_center_focusdata;
extern OSHGui::Misc::RawDataContainer com_button_right_focusdata;

namespace OSHGui {
	//---------------------------------------------------------------------------
	//static attributes
	//---------------------------------------------------------------------------
	const Drawing::SizeI Button::DefaultSize( 92, 24 );
	const Drawing::PointI Button::DefaultLabelOffset( 6, 5 );
	//---------------------------------------------------------------------------
	//Constructor
	//---------------------------------------------------------------------------
	Button::Button()
		: label_( new Label() ) {
		type_ = ControlType::Button;

		label_->SetLocation( DefaultLabelOffset );
		label_->SetBackColor( Drawing::Color::Empty() );
		label_->SetForeColor( Drawing::Color( 255, 201, 201, 201 ) );

		SetSize( DefaultSize );

		ApplyStyle( Application::Instance().GetStyle() );

		this->com_button_left = Drawing::Image::FromMemory(com_button_leftdata);
		this->com_button_center = Drawing::Image::FromMemory(com_button_centerdata);
		this->com_button_right = Drawing::Image::FromMemory(com_button_rightdata);
		this->com_button_left_focus = Drawing::Image::FromMemory(com_button_left_focusdata);
		this->com_button_center_focus = Drawing::Image::FromMemory(com_button_center_focusdata);
		this->com_button_right_focus = Drawing::Image::FromMemory(com_button_right_focusdata);
	}

	//---------------------------------------------------------------------------
	//Getter/Setter
	//---------------------------------------------------------------------------
	void Button::SetAutoSize( bool autoSize ) {
		Control::SetAutoSize( autoSize );

		label_->SetAutoSize( autoSize );
	}

	//---------------------------------------------------------------------------
	void Button::SetSize( const Drawing::SizeI &size ) {
		Control::SetSize( size );

		CalculateLabelLocation();
	}

	//---------------------------------------------------------------------------
	void Button::SetText( const Misc::AnsiString &text ) {
		label_->SetText( text );
		if( autoSize_ ) {
			SetSize( label_->GetSize().InflateEx( DefaultLabelOffset.Left * 2, DefaultLabelOffset.Top * 2 ) );
		}

		CalculateLabelLocation();
	}

	//---------------------------------------------------------------------------
	const Misc::AnsiString &Button::GetText() const {
		return label_->GetText();
	}

	//---------------------------------------------------------------------------
	void Button::SetFont( const Drawing::FontPtr &font ) {
		Control::SetFont( font );

		label_->SetFont( font );
		if( autoSize_ ) {
			SetSize( label_->GetSize().InflateEx( DefaultLabelOffset.Left * 2, DefaultLabelOffset.Top * 2 ) );
		}
	}

	//---------------------------------------------------------------------------
	void Button::SetForeColor( const Drawing::Color &color ) {
		Control::SetForeColor( color );

		label_->SetForeColor( color );
	}

	//---------------------------------------------------------------------------
	//Runtime-Functions
	//---------------------------------------------------------------------------
	void Button::CalculateAbsoluteLocation() {
		Control::CalculateAbsoluteLocation();

		label_->SetParent( this );
	}

	//---------------------------------------------------------------------------
	void Button::CalculateLabelLocation() {
		label_->SetLocation( Drawing::PointI( GetSize().Width / 2.f - label_->GetSize().Width / 2.f,
		                                      GetSize().Height / 2.2f - label_->GetSize().Height / 2.2f ) );
	}

	//---------------------------------------------------------------------------
	void Button::DrawSelf( Drawing::RenderContext &context ) {
		Control::DrawSelf( context );

		label_->Render();
	}

	//---------------------------------------------------------------------------
	void Button::PopulateGeometry() {
		using namespace Drawing;

		Graphics g( *geometry_ );

		auto size = this->GetSize();
		auto sizex = size.Width - 10;
		if (!this->isInside_)
		{
			g.DrawImage(this->com_button_left, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, 0), SizeI(13, 24)));

			size_t i;
			for (i = (sizex / 10); i < sizex; i++)
				g.DrawImage(this->com_button_center, Color::FromRGB(255, 255, 255), PointI(i, 0), RectangleI(PointI(0, 0), SizeI(10, 24)));

			g.DrawImage(this->com_button_right, Color::FromRGB(255, 255, 255), RectangleI(PointI(i, 0), SizeI(10, 24)));
		}
		else
		{
			g.DrawImage(this->com_button_left_focus, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, 0), SizeI(13,24)));
			/*width nrde kafana g�rem i yap�yon test etmek i�in b�le yapt�m :S*/

			size_t i;
			for (i = (sizex / 10); i < sizex; i++)
				g.DrawImage(this->com_button_center_focus, Color::FromRGB(255, 255, 255), PointI(i, 0), RectangleI(PointI(0, 0), SizeI(10, 24)));

			g.DrawImage(this->com_button_right_focus, Color::FromRGB(255, 255, 255), RectangleI(PointI(i, 0), SizeI(10, 24)));
		}
	}

	//---------------------------------------------------------------------------
	//Event-Handling
	//---------------------------------------------------------------------------
	bool Button::OnKeyUp( const KeyboardMessage &keyboard ) {
		if( !Control::OnKeyUp( keyboard ) ) {
			if( keyboard.GetKeyCode() == Key::Return ) {
				clickEvent_.Invoke( this );
			}
		}

		return true;
	}

	//---------------------------------------------------------------------------
}
