/*
* OldSchoolHack GUI
*
* by KN4CK3R https://www.oldschoolhack.me/
*
* See license in OSHGui.hpp
*/

#include "CheckBox.hpp"
#include "Label.hpp"
#include "../Misc/Exceptions.hpp"
#include "Timer.hpp"
extern OSHGui::Misc::RawDataContainer com_checkbutton_offdata;
extern OSHGui::Misc::RawDataContainer com_checkbutton_ondata;
namespace OSHGui {
	//---------------------------------------------------------------------------
	//static attributes
	//---------------------------------------------------------------------------
	const Drawing::PointI CheckBox::DefaultLabelOffset( 20, -1 );
	//---------------------------------------------------------------------------
	//Constructor
	//---------------------------------------------------------------------------
	CheckBox::CheckBox()
		: checked_( false ),
		  label_( new Label() ) {
		type_ = ControlType::CheckBox;

		SetSize( DefaultCheckBoxSize, DefaultCheckBoxSize );
		SetAutoSize( true );

		label_->SetLocation(16, 1.5f);
		label_->SetBackColor( Drawing::Color::Empty() );
		label_->SetStyle( 1 );

		ApplyStyle( Application::Instance().GetStyle() );

		this->img_normal = Drawing::Image::FromMemory(com_checkbutton_offdata);
		this->img_active = Drawing::Image::FromMemory(com_checkbutton_ondata);
	}

	//---------------------------------------------------------------------------
	//Getter/Setter
	//---------------------------------------------------------------------------
	void CheckBox::SetChecked( bool checked ) {
		if( checked_ != checked ) {
			checked_ = checked;

			checkedChangedEvent_.Invoke( this );

			Invalidate();
		}
	}

	//---------------------------------------------------------------------------
	bool CheckBox::GetChecked() const {
		return checked_;
	}

	//---------------------------------------------------------------------------
	void CheckBox::SetText( const Misc::AnsiString &text ) {
		const auto offset = label_->GetLocation();

		label_->SetText( text );
		if( autoSize_ ) {
			size_ = label_->GetSize().InflateEx( offset.Left, offset.Top );
			if( size_.Height < DefaultCheckBoxSize ) {
				size_.Height = DefaultCheckBoxSize;
			}
		}
	}

	//---------------------------------------------------------------------------
	const Misc::AnsiString &CheckBox::GetText() const {
		return label_->GetText();
	}

	//---------------------------------------------------------------------------
	void CheckBox::SetFont( const Drawing::FontPtr &font ) {
		Control::SetFont( font );

		label_->SetFont( font );
		if( autoSize_ ) {
			size_ = label_->GetSize();
			if( GetFont()->GetFontHeight() < DefaultCheckBoxSize ) {
				checkBoxLocation_ = Drawing::PointI( 0, 0 );
				auto y = static_cast< int >(DefaultCheckBoxSize / 2.0f - GetFont()->GetFontHeight() / 2.0f + 0.5f);
				label_->SetLocation( Drawing::PointI( DefaultLabelOffset.Left, y ) );
			}
			else {
				label_->SetLocation( DefaultLabelOffset );
				auto y = static_cast< int >(GetFont()->GetFontHeight() / 2.0f - DefaultCheckBoxSize / 2.0f + 0.5f);
				checkBoxLocation_ = Drawing::PointI( 0, y );
			}
		}
	}

	//---------------------------------------------------------------------------
	void CheckBox::SetForeColor( const Drawing::Color &color ) {
		Control::SetForeColor( color );

		label_->SetForeColor( Drawing::Color::FromARGB( 255, 205, 205, 205 ) );
	}

	//---------------------------------------------------------------------------
	CheckedChangedEvent &CheckBox::GetCheckedChangedEvent() {
		return checkedChangedEvent_;
	}

	//---------------------------------------------------------------------------
	//Runtime-Functions
	//---------------------------------------------------------------------------
	void CheckBox::CalculateAbsoluteLocation() {
		Control::CalculateAbsoluteLocation();

		checkBoxAbsoluteLocation_ = absoluteLocation_ + checkBoxLocation_;

		label_->SetParent( this );
	}

	//---------------------------------------------------------------------------
	void CheckBox::DrawSelf( Drawing::RenderContext &context ) {
		Control::DrawSelf( context );

		label_->Render();
	}

	//---------------------------------------------------------------------------
	void CheckBox::PopulateGeometry() {
		using namespace Drawing;

		Graphics g( *geometry_ );

		if( checked_ ) {
			g.DrawImage(img_normal, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, 0), SizeI(16, 16)));
		}
		else
			g.DrawImage(img_active, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, 0), SizeI(16, 16)));
	}

	//---------------------------------------------------------------------------
	//Event-Handling
	//---------------------------------------------------------------------------
	void CheckBox::OnMouseClick( const MouseMessage &mouse ) {
		Control::OnMouseClick( mouse );

		SetChecked( !GetChecked() );
	}

	//---------------------------------------------------------------------------
	bool CheckBox::OnKeyUp( const KeyboardMessage &keyboard ) {
		if( !Control::OnKeyUp( keyboard ) ) {
			if( keyboard.GetKeyCode() == Key::Space ) {
				SetChecked( !GetChecked() );
			}
		}

		return true;
	}

	//---------------------------------------------------------------------------
}
