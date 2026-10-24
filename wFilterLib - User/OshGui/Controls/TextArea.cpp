/*
 * OldSchoolHack GUI
 *
 * by KN4CK3R https://www.oldschoolhack.me/
 *
 * See license in OSHGui.hpp
 */

#include "../Controls/TextArea.hpp"
#include "../Misc/Exceptions.hpp"
#include <iostream>

extern OSHGui::Misc::RawDataContainer textareadata;

namespace OSHGui {
	//---------------------------------------------------------------------------
	//static attributes
	//---------------------------------------------------------------------------
	const Drawing::SizeI TextArea::DefaultSize( 239, 107 );
	const Drawing::PointI TextArea::DefaultTextOffset( 7, 5 );
	//---------------------------------------------------------------------------
	//Constructor
	//---------------------------------------------------------------------------
	TextArea::TextArea()
		: textHelper_( GetFont() ),
		  blinkTime_( Misc::TimeSpan::FromMilliseconds( 500 ) ),
		  firstVisibleCharacter_( 0 ),
		  visibleCharacterCount_( 0 ),
		  caretPosition_( 0 ),
		  passwordChar_( '\0' ),
		  showCaret_( true ) {
		type_ = ControlType::TextArea;

		ApplyStyle( Application::Instance().GetStyle() );

		SetSize( DefaultSize );

		cursor_ = Cursors::Get( Cursors::IBeam );

		img_textArea = Drawing::Image::FromMemory(textareadata);
	}

	//---------------------------------------------------------------------------
	//Getter/Setter
	//---------------------------------------------------------------------------
	void TextArea::SetSize( const Drawing::SizeI &size ) {
		const Drawing::SizeI fixxed( size.Width, GetFont()->GetFontHeight() + DefaultTextOffset.Top * 2 );

		Control::SetSize( fixxed );

		textRect_ = Drawing::RectangleI( DefaultTextOffset.Left, DefaultTextOffset.Top,
		                                 GetWidth() - DefaultTextOffset.Left * 2, GetHeight() - DefaultTextOffset.Top * 2 );

		firstVisibleCharacter_ = 0;
		PlaceCaret( textHelper_.GetText().length() );
	}

	//---------------------------------------------------------------------------
	void TextArea::SetFont( const Drawing::FontPtr &font ) {
		Control::SetFont( font );

		SetSize( GetWidth(), 0 );
	}

	//---------------------------------------------------------------------------
	void TextArea::SetText( const Misc::AnsiString &text ) {
		realtext_ = text;
		if( passwordChar_ == '\0' ) {
			textHelper_.SetText( text );
		}
		else {
			textHelper_.SetText( Misc::AnsiString( text.length(), passwordChar_ ) );
		}

		firstVisibleCharacter_ = 0;
		PlaceCaret( text.length() );

		textChangedEvent_.Invoke( this );
	}

	//---------------------------------------------------------------------------
	const Misc::AnsiString &TextArea::GetText() const {
		return realtext_;
	}

	//---------------------------------------------------------------------------
	void TextArea::SetPasswordChar( const Misc::AnsiChar &passwordChar ) {
		this->passwordChar_ = passwordChar;
		SetText( realtext_ );
	}

	//---------------------------------------------------------------------------
	const Misc::AnsiChar &TextArea::GetPasswordChar() const {
		return passwordChar_;
	}

	//---------------------------------------------------------------------------
	TextChangedEvent &TextArea::GetTextChangedEvent() {
		return textChangedEvent_;
	}

	//---------------------------------------------------------------------------
	//Runtime-Functions
	//---------------------------------------------------------------------------
	void TextArea::ShowCaret( bool showCaret ) {
		showCaret_ = showCaret;
	}

	//---------------------------------------------------------------------------
	void TextArea::CalculateAbsoluteLocation() {
		Control::CalculateAbsoluteLocation();

		textRect_ = Drawing::RectangleI( DefaultTextOffset.Left, DefaultTextOffset.Top,
		                                 GetWidth() - DefaultTextOffset.Left * 2, GetHeight() - DefaultTextOffset.Top * 2 );
		PlaceCaret( caretPosition_ );
	}

	//---------------------------------------------------------------------------
	void TextArea::ResetCaretBlink() {
		drawCaret_ = false;
		nextBlinkTime_ = Misc::DateTime();
	}

	//---------------------------------------------------------------------------
	void TextArea::PlaceCaret( int position ) {
		if( position < 0 ) {
			position = 0;
		}
		caretPosition_ = position;

		Drawing::PointI caretPositionTrail;
		const Drawing::PointI firstVisibleCharacterPosition = textHelper_.GetCharacterPosition( firstVisibleCharacter_ );
		const Drawing::PointI newCaretPosition = textHelper_.GetCharacterPosition( position );

		//if the new caretPosition is bigger than the text length
		if( position > textHelper_.GetLength() ) {
			caretPosition_ = position = textHelper_.GetLength();
			caretPositionTrail = newCaretPosition;
		}
		else {
			caretPositionTrail = textHelper_.GetCharacterPosition( position, true );
		}

		//if the new caretPosition is smaller than the textRect
		if( newCaretPosition.Left <= firstVisibleCharacterPosition.Left ) {
			if( position > 1 ) {
				firstVisibleCharacter_ = position - 2;
			}
			else {
				firstVisibleCharacter_ = position;
			}
		}
		else if( caretPositionTrail.Left > firstVisibleCharacterPosition.Left + textRect_.GetWidth() )
			//if the new caretPosition is bigger than the textRect
		{
			const auto newFirstVisibleCharacterPositionLeft = caretPositionTrail.Left - textRect_.GetWidth();
			auto newFirstVisibleCharacter = textHelper_.GetClosestCharacterIndex(
				Drawing::PointI( newFirstVisibleCharacterPositionLeft, 0 ) );

			const Drawing::PointI newFirstVisibleCharacterPosition = textHelper_.
				GetCharacterPosition( newFirstVisibleCharacter );
			if( newFirstVisibleCharacterPosition.Left < newFirstVisibleCharacterPositionLeft ) {
				++newFirstVisibleCharacter;
			}

			firstVisibleCharacter_ = newFirstVisibleCharacter;
		}

		const Drawing::SizeI strWidth = textHelper_.GetStringSize( firstVisibleCharacter_,
		                                                           caretPosition_ - firstVisibleCharacter_ );
		caretRect_ = Drawing::RectangleI( textRect_.GetLeft() + strWidth.Width, textRect_.GetTop(), 1,
		                                  textRect_.GetHeight() );

		ResetCaretBlink();
		visibleCharacterCount_ = CalculateVisibleCharacters();

		Invalidate();
	}

	//---------------------------------------------------------------------------
	void TextArea::InjectTime( const Misc::DateTime &time ) {
		if( time > nextBlinkTime_ ) {
			drawCaret_ = !drawCaret_;
			nextBlinkTime_ = time.Add( blinkTime_ );

			Invalidate();
		}
	}

	//---------------------------------------------------------------------------
	void TextArea::PopulateGeometry() {
		using namespace Drawing;

		Graphics g( *geometry_ );

		g.DrawImage(img_textArea, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, 0), img_textArea->GetSize()));


		if( showCaret_ ) {
			if( isFocused_ && drawCaret_ ) {
				g.FillRectangle( GetForeColor(), caretRect_ );
			}
		}

		g.DrawString( this->GetText().substr( firstVisibleCharacter_, visibleCharacterCount_ ), GetFont(),
		              GetForeColor(), textRect_.GetLocation() );

		this->lineCount_ = 1 + floor(this->textHelper_.GetStringSize(0, this->textHelper_.GetText().length()).Width / (DefaultSize.Width - 12));
		int nextstrindex = -1, PosX = 0, PosY = 0, plannedindex = -1;
		for (int i = 0; i < this->lineCount_; i++)
		{
			plannedindex = this->textHelper_.GetClosestCharacterIndex(Drawing::PointF((PosX + ((DefaultSize.Width - 12) * (i + 1)) + this->textHelper_.GetStringSize(0, 1).Width), PosY));
			
			PosX = this->textRect_.GetLeft();
			PosY = this->textRect_.GetTop();
			if (i > 0)
			{/*
				if (i != 5)
				{
					std::cout << "theres a multiline!!! nextstrindex : " << nextstrindex << " plannedindex : " << plannedindex << " the negatived : " << (plannedindex - nextstrindex) << " total length : " << this->textHelper_.GetText().length() << std::endl;
				}*/
				g.DrawString(this->textHelper_.GetText().substr(nextstrindex-1, ((plannedindex) - (nextstrindex))), GetFont(), GetForeColor(), PosX, (PosY + ((i * (DefaultTextOffset.Y+6)))));
			}
			nextstrindex = plannedindex;
		}

		g.DrawString(std::to_string(this->textHelper_.GetStringSize(0, this->textHelper_.GetText().length()).Width), GetFont(), Color::Red(), 0, 210);
		g.DrawString(std::to_string((DefaultSize.Width - 12)), GetFont(), Color::Red(), 0, 250);
	}

	//---------------------------------------------------------------------------
	//Event-Handling
	//---------------------------------------------------------------------------
	void TextArea::OnMouseDown( const MouseMessage &mouse ) {
		Control::OnMouseDown( mouse );

		const Drawing::SizeI strWidth = textHelper_.GetStringSize( 0, firstVisibleCharacter_ );
		PlaceCaret( textHelper_.GetClosestCharacterIndex(
			mouse.GetLocation() - absoluteLocation_ + Drawing::PointI( strWidth.Width - 7, 0 ) ) - 1 );
	}

	//---------------------------------------------------------------------------
	void TextArea::NumbersOnly()
	{
		this->isNumbersOnly_ = true;
	}
	//---------------------------------------------------------------------------
	bool TextArea::OnKeyDown( const KeyboardMessage &keyboard ) {
		Control::OnKeyDown( keyboard );
		if (this->isNumbersOnly_ && !keyboard.IsAlphaNumeric())
			return false;
		switch( keyboard.GetKeyCode() ) {
		case Key::Delete:
			if( caretPosition_ < textHelper_.GetLength() ) {
				textHelper_.Remove( caretPosition_, 1 );
				realtext_.erase( caretPosition_, 1 );
				PlaceCaret( caretPosition_ );

				OnTextChanged();
			}
			break;
		case Key::Back:
			if( caretPosition_ > 0 && textHelper_.GetLength() > 0 ) {
				textHelper_.Remove( caretPosition_ - 1, 1 );
				realtext_.erase( caretPosition_ - 1, 1 );
				PlaceCaret( caretPosition_ - 1 );

				OnTextChanged();
			}
			break;
		case Key::Left:
			PlaceCaret( caretPosition_ - 1 );
			break;
		case Key::Right:
			PlaceCaret( caretPosition_ + 1 );
			break;
		case Key::Home:
			PlaceCaret( 0 );
			break;
		case Key::End:
			PlaceCaret( textHelper_.GetLength() );
			break;
		}

		return false;
	}

	//---------------------------------------------------------------------------
	bool TextArea::OnKeyPress( const KeyboardMessage &keyboard ) {
		if( !Control::OnKeyPress( keyboard ) ) {
			KeyEventArgs args( keyboard );
			if( keyboard.GetKeyCode() != Key::Return ) {
				if( keyboard.IsAlphaNumeric() ) {
					realtext_.insert( caretPosition_, 1, keyboard.GetKeyChar() );
					if( passwordChar_ == '\0' ) {
						textHelper_.Insert( caretPosition_, keyboard.GetKeyChar() );
					}
					else {
						textHelper_.Insert( caretPosition_, passwordChar_ );
					}
					PlaceCaret( ++caretPosition_ );

					OnTextChanged();
				}
			}
		}

		return true;
	}

	//---------------------------------------------------------------------------
	void TextArea::OnTextChanged() {
		textChangedEvent_.Invoke( this );
		visibleCharacterCount_ = CalculateVisibleCharacters();

		if (floor(this->textHelper_.GetStringSize(0, this->textHelper_.GetText().length()).Width / (DefaultSize.Width - 12)) > 1)
		{
			int PosX = 0, PosY = 0;
			PosX = this->textRect_.GetLeft();
			PosY = this->textRect_.GetTop();
			int nextlinebeginningindex = this->textHelper_.GetClosestCharacterIndex(Drawing::PointF((PosX + (DefaultSize.Width - 12) + this->textHelper_.GetStringSize(0, 1).Width), PosY));
			std::string fulltext = this->textHelper_.GetText();
			this->SetText(this->textHelper_.GetText().substr(0, nextlinebeginningindex));
			this->textHelper_.SetText(fulltext);
		}
	}

	//---------------------------------------------------------------------------
	int TextArea::CalculateVisibleCharacters() {
		int visibleCharacters = textHelper_.GetLength() - firstVisibleCharacter_;

		if( textHelper_.GetStringSize( firstVisibleCharacter_, visibleCharacters ).Width > textRect_.GetWidth() ) {
			const auto averageWidth = textHelper_.GetSize().Width / static_cast< float >(textHelper_.GetLength());
			visibleCharacters = static_cast< float >(textRect_.GetWidth()) / averageWidth;

			if( textHelper_.GetStringSize( firstVisibleCharacter_, visibleCharacters ).Width > textRect_.GetWidth() ) {
				while( textHelper_.GetStringSize( firstVisibleCharacter_, --visibleCharacters ).Width > textRect_.GetWidth() );
			}
			else {
				while( textHelper_.GetStringSize( firstVisibleCharacter_, ++visibleCharacters ).Width <= textRect_.GetWidth() );
				--visibleCharacters;
			}
		}

		return visibleCharacters;
	}

	//---------------------------------------------------------------------------
}