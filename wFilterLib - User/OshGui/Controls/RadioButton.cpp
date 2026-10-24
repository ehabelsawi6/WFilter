/*
 * OldSchoolHack GUI
 *
 * by KN4CK3R https://www.oldschoolhack.me/
 *
 * See license in OSHGui.hpp
 */

#include "RadioButton.hpp"
#include "Label.hpp"
#include "../Misc/Exceptions.hpp"

extern OSHGui::Misc::RawDataContainer com_radiobutton_offdata;
extern OSHGui::Misc::RawDataContainer com_radiobutton_ondata;
namespace OSHGui {
	//---------------------------------------------------------------------------
	//Constructor
	//---------------------------------------------------------------------------
	RadioButton::RadioButton() {
		type_ = ControlType::RadioButton;
		this->img_normal = Drawing::Image::FromMemory(com_radiobutton_offdata);
		this->img_active = Drawing::Image::FromMemory(com_radiobutton_ondata);
	}

	//---------------------------------------------------------------------------
	//Getter/Setter
	//---------------------------------------------------------------------------
	void RadioButton::SetChecked( bool checked ) {
		if( checked_ != checked ) {
			if( GetParent() != nullptr ) {
				//uncheck other radiobuttons
				for( auto &control : GetParent()->GetControls() ) {
					if( control->GetType() == ControlType::RadioButton ) {
						static_cast< RadioButton* >(control)->SetCheckedInternal( false );
					}
				}

				SetCheckedInternal( checked );
			}
		}
	}

	//---------------------------------------------------------------------------
	void RadioButton::SetCheckedInternal( bool checked ) {
		if( checked_ != checked ) {
			checked_ = checked;

			checkedChangedEvent_.Invoke( this );

			Invalidate();
		}
	}

	//---------------------------------------------------------------------------
	void RadioButton::PopulateGeometry() {
		using namespace Drawing;

		Graphics g( *geometry_ );

		if (checked_) {
			g.DrawImage(img_normal, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, 0), SizeI(16, 16)));
		}
		else
			g.DrawImage(img_active, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, 0), SizeI(16, 16)));
	}

	//---------------------------------------------------------------------------
	//Event-Handling
	//---------------------------------------------------------------------------
	void RadioButton::OnMouseClick( const MouseMessage &mouse ) {
		Control::OnMouseClick( mouse );

		SetChecked( true );
	}

	//---------------------------------------------------------------------------
	bool RadioButton::OnKeyUp( const KeyboardMessage &keyboard ) {
		if( !Control::OnKeyUp( keyboard ) ) {
			if( keyboard.GetKeyCode() == Key::Space ) {
				SetChecked( true );

				clickEvent_.Invoke( this );
			}
		}

		return true;
	}

	//---------------------------------------------------------------------------

}
