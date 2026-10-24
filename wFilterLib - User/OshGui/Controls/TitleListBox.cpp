/*
* OldSchoolHack GUI
*
* by KN4CK3R https://www.oldschoolhack.me/
*
* See license in OSHGui.hpp
*/

#include <locale>
#include "TitleListBox.hpp"
#include "ScrollBar.hpp"
#include "../Misc/Exceptions.hpp"
#include "../Misc/Intersection.hpp"
#include "Timer.hpp"

namespace OSHGui {
	//---------------------------------------------------------------------------
	//static attributes
	//---------------------------------------------------------------------------
	const Drawing::SizeI TitleListBox::DefaultSize( 120, 106 );
	const Drawing::SizeI TitleListBox::DefaultItemAreaPadding( 16, 24 );
	const int TitleListBox::DefaultItemPadding( 18 );
	//---------------------------------------------------------------------------
	//Constructor
	//---------------------------------------------------------------------------
	TitleListBox::TitleListBox()
		: selectedIndex_( -1 ),
		  firstVisibleItemIndex_( 0 ),
		  autoScrollEnabled_( false ) {
		type_ = ControlType::ListBox;

		scrollBar_ = new ScrollBar();
		scrollBar_->SetVisible( false );
		scrollBar_->GetScrollEvent() += ScrollEventHandler( [ this ]( Control *, ScrollEventArgs &args )
		{
			firstVisibleItemIndex_ = args.NewValue;
			Invalidate();
		} );
		scrollBar_->GetFocusLostEvent() += FocusLostEventHandler( [ this ]( Control *, Control *newFocusedControl )
		{
			if( newFocusedControl != this ) {
				OnLostFocus( newFocusedControl );
			}
		} );
		AddSubControl( scrollBar_ );

		SetSize( DefaultSize );

		maxVisibleItems_ = GetHeight() / ( GetFont()->GetFontHeight() + DefaultItemPadding );

		ApplyStyle( Application::Instance().GetStyle() );
	}

	//---------------------------------------------------------------------------
	TitleListBox::~TitleListBox() {
		Clear();
	}

	//---------------------------------------------------------------------------
	//Getter/Setter
	//---------------------------------------------------------------------------
	void TitleListBox::SetSize( const Drawing::SizeI &size ) {
		Control::SetSize( size );

		itemAreaSize_ = size.InflateEx( 8, 8 );
		if( scrollBar_->GetVisible() ) {
			itemAreaSize_.Width -= scrollBar_->GetWidth();
		}

		scrollBar_->SetLocation( size.Width-10, 1);
		scrollBar_->SetSize( scrollBar_->GetWidth(), size.Height);

		CheckForScrollBar();
	}

	//---------------------------------------------------------------------------
	void TitleListBox::SetFont( const Drawing::FontPtr &font ) {
		Control::SetFont( font );

		CheckForScrollBar();
	}

	//---------------------------------------------------------------------------
	void TitleListBox::SetAutoScrollEnabled( bool autoScrollEnabled ) {
		autoScrollEnabled_ = autoScrollEnabled;
	}

	//---------------------------------------------------------------------------
	bool TitleListBox::GetAutoScrollEnabled() const {
		return autoScrollEnabled_;
	}

	//---------------------------------------------------------------------------
	TListItem *TitleListBox::GetItem( int index ) const {
#ifndef OSHGUI_DONTUSEEXCEPTIONS
		if( index < 0 || index >= static_cast<int>( items_.size() ) )
		{
			throw Misc::ArgumentOutOfRangeException( "index" );
		}
#endif

		return items_[ index ];
	}

	//---------------------------------------------------------------------------
	void TitleListBox::SetSelectedIndex( int index ) {
		if( selectedIndex_ == index ) {
			return;
		}

#ifndef OSHGUI_DONTUSEEXCEPTIONS
		if( index < 0 || index >= static_cast<int>( items_.size() ) )
		{
			throw Misc::ArgumentOutOfRangeException( "index" );
		}
#endif

		selectedIndex_ = index;

		selectedIndexChangedEvent_.Invoke( this );

		if( index - firstVisibleItemIndex_ >= maxVisibleItems_ || index - firstVisibleItemIndex_ < 0 ) {
			for( firstVisibleItemIndex_ = 0; firstVisibleItemIndex_ <= index; firstVisibleItemIndex_ += maxVisibleItems_ );
			firstVisibleItemIndex_ -= maxVisibleItems_;
			if( firstVisibleItemIndex_ < 0 ) {
				firstVisibleItemIndex_ = 0;
			}
			scrollBar_->SetValue( firstVisibleItemIndex_ );
		}

		Invalidate();
	}

	//---------------------------------------------------------------------------
	int TitleListBox::GetSelectedIndex() const {
		return selectedIndex_;
	}

	//---------------------------------------------------------------------------
	void TitleListBox::SetSelectedItem( const Misc::AnsiString &text ) {
		auto index = 0;
		for( auto &&item : items_ ) {
			if( item->GetItemText() == text ) {
				SetSelectedIndex( index );
				return;
			}
			++index;
		}
	}

	//---------------------------------------------------------------------------
	TListItem *TitleListBox::GetSelectedItem() const {
		return GetItem( GetSelectedIndex() );
	}

	//---------------------------------------------------------------------------
	int TitleListBox::GetItemsCount() const {
		return items_.size();
	}

	//---------------------------------------------------------------------------
	SelectedIndexChangedEvent &TitleListBox::GetSelectedIndexChangedEvent() {
		return selectedIndexChangedEvent_;
	}

	//---------------------------------------------------------------------------
	//Runtime-Functions
	//---------------------------------------------------------------------------
	bool TitleListBox::Intersect( const Drawing::PointI &point ) const {
		return Intersection::TestRectangle( absoluteLocation_,
		                                    scrollBar_->GetVisible() ? size_.InflateEx( -scrollBar_->GetWidth(), 0 ) : size_,
		                                    point );
	}

	//---------------------------------------------------------------------------
	void TitleListBox::ExpandSizeToShowItems( int count ) {
		const auto itemHeight = GetFont()->GetFontHeight() + DefaultItemPadding;
		const auto newHeight = count * itemHeight;

		SetSize( GetWidth(), newHeight + DefaultItemAreaPadding.Height );
	}

	//---------------------------------------------------------------------------
	void TitleListBox::AddItem( const Misc::AnsiString &text ) {
		AddItem( new TStringListItem( text ) );
	}

	//---------------------------------------------------------------------------
	void TitleListBox::AddItem( TListItem *item ) {
		InsertItem( !items_.empty() ? items_.size() : 0, item );
	}

	//---------------------------------------------------------------------------
	void TitleListBox::InsertItem( int index, const Misc::AnsiString &text ) {
		InsertItem( index, new TStringListItem( text ) );
	}

	//---------------------------------------------------------------------------
	void TitleListBox::InsertItem( int index, TListItem *item ) {
		items_.insert( items_.begin() + index, item );

		CheckForScrollBar();

		if( autoScrollEnabled_ ) {
			scrollBar_->SetValue( index );
		}

		Invalidate();
	}

	//---------------------------------------------------------------------------
	void TitleListBox::RemoveItem( int index ) {
#ifndef OSHGUI_DONTUSEEXCEPTIONS
		if( index < 0 || index >= ( int ) items_.size() )
		{
			throw Misc::ArgumentOutOfRangeException( "index" );
		}
#endif

		items_.erase( items_.begin() + index );

		if( scrollBar_->GetVisible() ) {
			scrollBar_->SetMaximum( items_.size() - maxVisibleItems_ );
		}
		if( selectedIndex_ >= static_cast< int >(items_.size()) ) {
			selectedIndex_ = items_.size() - 1;

			selectedIndexChangedEvent_.Invoke( this );
		}

		Invalidate();
	}

	//---------------------------------------------------------------------------
	void TitleListBox::Clear() {
		items_.clear();

		scrollBar_->SetMaximum( 1 );

		selectedIndex_ = -1;

		CheckForScrollBar();

		Invalidate();
	}

	//---------------------------------------------------------------------------
	void TitleListBox::CheckForScrollBar() {
		const auto itemHeight = static_cast< int >(GetFont()->GetFontHeight()) + DefaultItemPadding;

		maxVisibleItems_ = std::max( 1, itemAreaSize_.Height / itemHeight );

		if( !items_.empty() && items_.size() * itemHeight > itemAreaSize_.Height ) {
			if( !scrollBar_->GetVisible() ) {
				itemAreaSize_.Width -= scrollBar_->GetWidth();
			}
			scrollBar_->SetMaximum( items_.size() - maxVisibleItems_ );
			scrollBar_->SetVisible( true );
		}
		else if( scrollBar_->GetVisible() ) {
			scrollBar_->SetVisible( false );
			itemAreaSize_.Width += scrollBar_->GetWidth();
		}
	}

	//---------------------------------------------------------------------------
	void TitleListBox::DrawSelf( Drawing::RenderContext &context ) {
		Control::DrawSelf( context );
		if(GetAutoScrollEnabled())
		scrollBar_->Render();
	}

	//---------------------------------------------------------------------------
	void TitleListBox::PopulateGeometry() {
		using namespace Drawing;

		Graphics g(*geometry_);

		const auto itemX = 4;
		const auto itemY = 5;
		const auto padding = GetFont()->GetFontHeight() + DefaultItemPadding;
		for (int i = 0; i < maxVisibleItems_ && i + firstVisibleItemIndex_ < static_cast<int>(items_.size()); ++i)
		{
			if (firstVisibleItemIndex_ + i == selectedIndex_)
			{
				g.FillRectangle(Color::Gray(), PointF(itemX - 3, itemY + i * padding - 1), SizeF(1, padding-2));
				g.FillRectangle(Color::Gray(), PointF(itemX+220, itemY + i * padding - 1), SizeF(1, padding-2));
			}
			auto titleStr = items_[firstVisibleItemIndex_ + i]->GetItemText();
			if (titleStr != "<No Title>")
			{
				g.DrawString("<" + titleStr + "> [Name]", GetFont(), GetForeColor(), PointF(itemX + 40 + 1, itemY + 5 + i * padding));
			}
			else
			g.DrawString(titleStr, GetFont(), GetForeColor(), PointF(itemX + 40 + 1, itemY + 5 + i * padding));
		}
	}

	//---------------------------------------------------------------------------
	//Event-Handling
	//---------------------------------------------------------------------------
	void TitleListBox::OnMouseClick( const MouseMessage &mouse ) {

		if (this->parent_->GetVisible()  && isVisible_)
		{
		Control::OnMouseClick( mouse );
			if (Intersection::TestRectangle(absoluteLocation_.OffsetEx(4, 4), itemAreaSize_, mouse.GetLocation())) {
				const auto clickedIndex = firstVisibleItemIndex_ + (mouse.GetLocation().Y - absoluteLocation_.Y - 4) / (GetFont()
					->GetFontHeight() + DefaultItemPadding);
				if (clickedIndex < items_.size()) {
					SetSelectedIndex(clickedIndex);
				}
			}
		}
	}

	//---------------------------------------------------------------------------
	void TitleListBox::OnMouseScroll( const MouseMessage &mouse ) {

		if (this->parent_->GetVisible()  && isVisible_)
		{
			Control::OnMouseScroll(mouse);

			int newScrollValue = scrollBar_->GetValue() + mouse.GetDelta();
			if (newScrollValue < 0) {
				newScrollValue = 0;
			}
			else if (newScrollValue > items_.size() - maxVisibleItems_) {
				newScrollValue = items_.size() - maxVisibleItems_;
			}
			scrollBar_->SetValue(newScrollValue);
		}
	}

	//---------------------------------------------------------------------------
	bool TitleListBox::OnKeyDown( const KeyboardMessage &keyboard ) {

		if (this->parent_->GetVisible()  && isVisible_)
		{
			if (!Control::OnKeyDown(keyboard)) {
				switch (keyboard.GetKeyCode()) {
				case Key::Up:
				case Key::Down:
				case Key::Home:
				case Key::End:
				case Key::PageUp:
				case Key::PageDown: {
					int newSelectedIndex = selectedIndex_;

					switch (keyboard.GetKeyCode()) {
					case Key::Up:
						--newSelectedIndex;
						break;
					case Key::Down:
						++newSelectedIndex;
						break;
					case Key::Home:
						newSelectedIndex = 0;
						break;
					case Key::End:
						newSelectedIndex = items_.size() - 1;
						break;
					case Key::PageUp:
						newSelectedIndex += maxVisibleItems_;
						break;
					case Key::PageDown:
						newSelectedIndex -= maxVisibleItems_;
						break;
					}

					if (newSelectedIndex < 0) {
						newSelectedIndex = 0;
					}
					if (newSelectedIndex >= (int)items_.size()) {
						newSelectedIndex = items_.size() - 1;
					}

					SetSelectedIndex(newSelectedIndex);

					return true;
				}
				}
			}
		}
		return false;
	}

	//---------------------------------------------------------------------------
	bool TitleListBox::OnKeyPress( const KeyboardMessage &keyboard ) {
		if( !Control::OnKeyPress( keyboard ) ) {
			if( keyboard.IsAlphaNumeric() ) {
				std::locale loc;
				const auto keyChar = std::tolower( keyboard.GetKeyChar(), loc );
				int foundIndex = 0;
				for( auto &c : items_ ) {
					const auto check = std::tolower( c->GetItemText()[ 0 ], loc );
					if( check == keyChar && foundIndex != selectedIndex_ ) {
						break;
					}

					++foundIndex;
				}

				if( foundIndex < static_cast< int >(items_.size()) ) {
					SetSelectedIndex( foundIndex );
				}
			}
		}

		return true;
	}

	//---------------------------------------------------------------------------
	// StringListItem
	//---------------------------------------------------------------------------
	TStringListItem::TStringListItem( const Misc::AnsiString &_text )
		: text( _text ) { }

	//---------------------------------------------------------------------------
	const Misc::AnsiString &TStringListItem::GetItemText() const {
		return text;
	}

	//---------------------------------------------------------------------------
}
