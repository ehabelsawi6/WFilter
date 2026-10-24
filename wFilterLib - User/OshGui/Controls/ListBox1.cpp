/*
* OldSchoolHack GUI
*
* by KN4CK3R https://www.oldschoolhack.me/
*
* See license in OSHGui.hpp
*/

#include <locale>
#include "ListBox1.hpp"
#include "ScrollBar.hpp"
#include "../Misc/Exceptions.hpp"
#include "../Misc/Intersection.hpp"
#include "Timer.hpp"
#include "..\QProxyLib\Helpers\CStringHelper.h"

namespace OSHGui {
	//---------------------------------------------------------------------------
	//static attributes
	//---------------------------------------------------------------------------
	const Drawing::SizeI ListBox1::DefaultSize( 120, 106 );
	const Drawing::SizeI ListBox1::DefaultItemAreaPadding( 8, 8 );
	const int ListBox1::DefaultItemPadding( 7 );
	std::mutex mtx;
	//---------------------------------------------------------------------------
	//Constructor
	//---------------------------------------------------------------------------
	ListBox1::ListBox1()
		: selectedIndex_( -1 ),
		  firstVisibleItemIndex_( 0 ),
		  autoScrollEnabled_( false ) {
		type_ = ControlType::ListBox1;

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
	ListBox1::~ListBox1() {
		Clear();
	}

	//---------------------------------------------------------------------------
	//Getter/Setter
	//---------------------------------------------------------------------------
	void ListBox1::SetSize( const Drawing::SizeI &size ) {
		Control::SetSize( size );

		itemAreaSize_ = size.InflateEx( -8, -8 );
		if( scrollBar_->GetVisible() ) {
			itemAreaSize_.Width -= scrollBar_->GetWidth();
		}

		scrollBar_->SetLocation( size.Width-10, 1);
		scrollBar_->SetSize( scrollBar_->GetWidth(), size.Height);

		CheckForScrollBar();
	}

	//---------------------------------------------------------------------------
	void ListBox1::SetFont( const Drawing::FontPtr &font ) {
		Control::SetFont( font );

		CheckForScrollBar();
	}

	//---------------------------------------------------------------------------
	void ListBox1::SetAutoScrollEnabled( bool autoScrollEnabled ) {
		autoScrollEnabled_ = autoScrollEnabled;
	}

	//---------------------------------------------------------------------------
	bool ListBox1::GetAutoScrollEnabled() const {
		return autoScrollEnabled_;
	}

	//---------------------------------------------------------------------------
	ListItem1 *ListBox1::GetItem( int index ) const {
#ifndef OSHGUI_DONTUSEEXCEPTIONS
		if( index < 0 || index >= static_cast<int>( items_.size() ) )
		{
			throw Misc::ArgumentOutOfRangeException( "index" );
		}
#endif

		return items_[ index ];
	}

	//---------------------------------------------------------------------------
	void ListBox1::SetSelectedIndex( int index ) {
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
	void ListBox1::SetTStyle(uint8_t style)
	{
		this->thisType = style;
	}
	//---------------------------------------------------------------------------
	int ListBox1::GetSelectedIndex() const {
		return selectedIndex_;
	}

	//---------------------------------------------------------------------------
	void ListBox1::SetSelectedItem( const Misc::AnsiString &text ) {
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
	ListItem1 *ListBox1::GetSelectedItem() const {
		return GetItem( GetSelectedIndex() );
	}

	//---------------------------------------------------------------------------
	int ListBox1::GetItemsCount() const {
		return items_.size();
	}

	//---------------------------------------------------------------------------
	SelectedIndexChangedEvent &ListBox1::GetSelectedIndexChangedEvent() {
		return selectedIndexChangedEvent_;
	}

	//---------------------------------------------------------------------------
	//Runtime-Functions
	//---------------------------------------------------------------------------
	bool ListBox1::Intersect( const Drawing::PointI &point ) const {
		return Intersection::TestRectangle( absoluteLocation_,
		                                    scrollBar_->GetVisible() ? size_.InflateEx( -scrollBar_->GetWidth(), 0 ) : size_,
		                                    point );
	}

	//---------------------------------------------------------------------------
	void ListBox1::ExpandSizeToShowItems( int count ) {
		const auto itemHeight = GetFont()->GetFontHeight() + DefaultItemPadding;
		const auto newHeight = count * itemHeight;

		SetSize( GetWidth(), newHeight + DefaultItemAreaPadding.Height );
	}

	//---------------------------------------------------------------------------
	void ListBox1::AddItem( const Misc::AnsiString &text ) {
		AddItem( new StringListItem1( text ) );
	}

	//---------------------------------------------------------------------------
	void ListBox1::AddItem( ListItem1 *item ) {
		InsertItem( !items_.empty() ? items_.size() : 0, item );
	}

	//---------------------------------------------------------------------------
	void ListBox1::InsertItem( int index, const Misc::AnsiString &text ) {
		InsertItem( index, new StringListItem1( text ) );
	}

	//---------------------------------------------------------------------------
	void ListBox1::InsertItem( int index, ListItem1 *item ) {

		mtx.lock();
		items_.insert( items_.begin() + index, item );
		mtx.unlock();

		CheckForScrollBar();

		if( autoScrollEnabled_ ) {
			scrollBar_->SetValue( index );
		}

		Invalidate();
	}

	//---------------------------------------------------------------------------
	void ListBox1::RemoveItem( int index ) {
#ifndef OSHGUI_DONTUSEEXCEPTIONS
		if( index < 0 || index >= ( int ) items_.size() )
		{
			throw Misc::ArgumentOutOfRangeException( "index" );
		}
#endif

		mtx.lock();
		items_.erase( items_.begin() + index );
		mtx.unlock();
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
	void ListBox1::Clear() {
		mtx.lock();
		items_.clear();
		mtx.unlock();
		scrollBar_->SetMaximum( 1 );

		selectedIndex_ = -1;

		CheckForScrollBar();

		Invalidate();
	}

	//---------------------------------------------------------------------------
	void ListBox1::CheckForScrollBar() {
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
	void ListBox1::DrawSelf( Drawing::RenderContext &context ) {
		Control::DrawSelf( context );
		if(GetAutoScrollEnabled())
		scrollBar_->Render();
	}

	//---------------------------------------------------------------------------
	void ListBox1::PopulateGeometry() {
		using namespace Drawing;

		Graphics g( *geometry_ );

		if(this->thisType != ListBoxStyle::Chest)
			g.FillRectangle( Color::Black(), PointF( 4, 1 ), GetSize() - SizeF( 2, 2 ) );


		const auto itemX = 4;
		const auto itemY = 5;
		const auto padding = GetFont()->GetFontHeight() + DefaultItemPadding;
		for( int i = 0; i < maxVisibleItems_ && i + firstVisibleItemIndex_ < static_cast<int>( items_.size() ); ++i ) 
		{
			g.DrawRectangle(Color::FromARGB(90, 74, 74, 74), PointF(itemX - 1, itemY + i * padding),
				SizeF(itemAreaSize_.Width + 8, padding));


			if ((firstVisibleItemIndex_ + i == selectedIndex_) && items_[firstVisibleItemIndex_ + i]->GetItemText().length() != 0) {
				g.DrawRectangle(Color::FromARGB(255, 255, 178, 82), PointF(itemX - 1, itemY + i * padding - 1),
					SizeF(itemAreaSize_.Width + 8, padding));
			}

			auto split = CStringHelper::split(items_[firstVisibleItemIndex_ + i ]->GetItemText(), ',');
			auto test = g.MeasureString(split[0], GetFont());
			if (this->thisType == ListBoxStyle::Event)
			{
				/*if ((firstVisibleItemIndex_ + i == selectedIndex_) && items_[firstVisibleItemIndex_ + i]->GetItemText().length() != 0) {
					g.DrawRectangle(Color::FromARGB(255, 255, 178, 82), PointF(itemX - 1, itemY + i * padding - 1),
						SizeF(itemAreaSize_.Width + 8, padding));
				}*/
				test = g.MeasureString(split[0].c_str(), GetFont());
				g.DrawString(split[1].c_str(), GetFont(), Color::White(),
					PointF(itemX + 6, (itemY + 3) + i * padding));
			}
			if (this->thisType == 0 || this->thisType == ListBoxStyle::Player)
			{
				test = g.MeasureString(split[0].c_str(), GetFont());
				g.DrawString(split[0].c_str(), GetFont(), Color::White(),
					PointF(itemX + 13 - (test.Width / 2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[1].c_str(), GetFont());
				g.DrawString(split[1].c_str(), GetFont(), Color::White(),
					PointF(itemX + 162 - (test.Width / 2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[2].c_str(), GetFont());
				g.DrawString(split[2].c_str(), GetFont(), Color::White(),
					PointF(itemX + 320 - (test.Width / 2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[3].c_str(), GetFont());
				g.DrawString(split[3].c_str(), GetFont(), Color::White(),
					PointF(itemX + 412 - (test.Width / 2), (itemY + 3) + i * padding));
			}
			else if (this->thisType == ListBoxStyle::Guild)
			{
				g.DrawString(split[0].c_str(), GetFont(), Color::White(),
					PointF(itemX + 13, (itemY + 3) + i * padding));
				test = g.MeasureString(split[1].c_str(), GetFont());
				g.DrawString(split[1].c_str(), GetFont(), Color::White(),
					PointF(itemX + 75 - (test.Width/2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[2].c_str(), GetFont());
				g.DrawString(split[2].c_str(), GetFont(), Color::White(),
					PointF(itemX + 177 - (test.Width/2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[3].c_str(), GetFont());
				g.DrawString(split[3].c_str(), GetFont(), Color::White(),
					PointF(itemX + 268 - (test.Width / 2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[4].c_str(), GetFont());
				g.DrawString(split[4].c_str(), GetFont(), Color::White(),
					PointF(itemX + 348 - (test.Width / 2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[5].c_str(), GetFont());
				g.DrawString(split[5].c_str(), GetFont(), Color::White(),
					PointF(itemX + 417 - (test.Width/2), (itemY + 3) + i * padding));
			}			
			else if (this->thisType == ListBoxStyle::Union)
			{
				g.DrawString(split[0].c_str(), GetFont(), Color::White(),
					PointF(itemX + 13, (itemY + 3) + i * padding));
				test = g.MeasureString(split[1].c_str(), GetFont());
				g.DrawString(split[1].c_str(), GetFont(), Color::White(),
					PointF(itemX + 110 - (test.Width / 2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[2].c_str(), GetFont());
				g.DrawString(split[2].c_str(), GetFont(), Color::White(),
					PointF(itemX + 277 - (test.Width / 2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[3].c_str(), GetFont());
				g.DrawString(split[3].c_str(), GetFont(), Color::White(),
					PointF(itemX + 398 - (test.Width / 2), (itemY + 3) + i * padding));
			}
			else if (this->thisType == ListBoxStyle::Honor)
			{
				g.DrawString(split[0].c_str(), GetFont(), Color::White(),
					PointF(itemX + 13, (itemY + 3) + i * padding));
				test = g.MeasureString(split[1].c_str(), GetFont());
				g.DrawString(split[1].c_str(), GetFont(), Color::White(),
					PointF(itemX + 124 - (test.Width/2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[2].c_str(), GetFont());
				g.DrawString(split[2].c_str(), GetFont(), Color::White(),
					PointF(itemX + 285 - (test.Width / 2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[3].c_str(), GetFont());
				g.DrawString(split[3].c_str(), GetFont(), Color::White(),
					PointF(itemX + 409 - (test.Width / 2), (itemY + 3) + i * padding));
			}
			else if (this->thisType == ListBoxStyle::UniqueAndJob)
			{
				g.DrawString(split[0].c_str(), GetFont(), Color::White(),
					PointF(itemX + 13, (itemY + 3) + i * padding));
				test = g.MeasureString(split[1].c_str(), GetFont());
				g.DrawString(split[1].c_str(), GetFont(), Color::White(),
					PointF(itemX + 120 - (test.Width / 2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[2].c_str(), GetFont());
				g.DrawString(split[2].c_str(), GetFont(), Color::White(),
					PointF(itemX + 280 - (test.Width / 2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[3].c_str(), GetFont());
				g.DrawString(split[3].c_str(), GetFont(), Color::White(),
					PointF(itemX + 393 - (test.Width / 2), (itemY + 3) + i * padding));
			}
			else if (this->thisType == ListBoxStyle::Custom)
			{
				g.DrawString(split[0].c_str(), GetFont(), Color::White(),
					PointF(itemX + 13, (itemY + 3) + i * padding));
				test = g.MeasureString(split[1].c_str(), GetFont());
				g.DrawString(split[1].c_str(), GetFont(), Color::White(),
					PointF(itemX + 130 - (test.Width / 2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[2].c_str(), GetFont());
				g.DrawString(split[2].c_str(), GetFont(), Color::White(),
					PointF(itemX + 324 - (test.Width / 2), (itemY + 3) + i * padding));
			}
			else if (this->thisType == ListBoxStyle::Chest)
			{
				/*if ((firstVisibleItemIndex_ + i == selectedIndex_) && items_[firstVisibleItemIndex_ + i]->GetItemText().length() != 0) {
					g.DrawRectangle(Color::FromARGB(255, 255, 178, 82), PointF(itemX - 1, itemY + i * padding - 1),
						SizeF(itemAreaSize_.Width + 8, padding));
				}*/
				g.DrawString(split[0].c_str(), GetFont(), Color::White(),
					PointF(itemX + 13, (itemY + 3) + i * padding));
				test = g.MeasureString(split[1], GetFont());
				g.DrawString(split[1].c_str(), GetFont(), Color::White(),
					PointF(((itemX + 135) - (test.Width /2)), (itemY + 3) + i * padding));
				test = g.MeasureString(split[2], GetFont());
				g.DrawString(split[2].c_str(), GetFont(), Color::White(),
					PointF(itemX + 276 - (test.Width / 2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[3], GetFont());
				g.DrawString(split[3].c_str(), GetFont(), Color::White(),
					PointF(itemX + 345 - (test.Width / 2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[4], GetFont());
				g.DrawString(split[4].c_str(), GetFont(), Color::White(),
					PointF(itemX + 460 - (test.Width / 2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[5], GetFont());
				g.DrawString(split[5].c_str(), GetFont(), Color::White(),
					PointF(itemX + 538 - (test.Width/2), (itemY + 3) + i * padding));
			}
			else if (this->thisType == 8 || this->thisType == ListBoxStyle::DynamicShop)
			{
				test = g.MeasureString(split[0].c_str(), GetFont());
				g.DrawString(split[0].c_str(), GetFont(), Color::White(),
					PointF(itemX + 20 - (test.Width / 2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[1].c_str(), GetFont());
				g.DrawString(split[1].c_str(), GetFont(), Color::White(),
					PointF(itemX + 150 - (test.Width / 2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[2].c_str(), GetFont());
				g.DrawString(split[2].c_str(), GetFont(), Color::White(),
					PointF(itemX + 318 - (test.Width / 2), (itemY + 3) + i * padding));
				test = g.MeasureString(split[3].c_str(), GetFont());
				g.DrawString(split[3].c_str(), GetFont(), Color::White(),
					PointF(itemX + 409 - (test.Width / 2), (itemY + 3) + i * padding));
			}

			split.clear();
			split.shrink_to_fit();
		}
	}

	//---------------------------------------------------------------------------
	//Event-Handling
	//---------------------------------------------------------------------------
	void ListBox1::OnMouseClick( const MouseMessage &mouse ) {
		if (this->parent_->GetVisible())
		{
			Control::OnMouseClick(mouse);

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
	void ListBox1::OnMouseScroll( const MouseMessage &mouse ) {

		if (this->parent_->GetVisible())
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
	bool ListBox1::OnKeyDown( const KeyboardMessage &keyboard ) {

		if (this->parent_->GetVisible())
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
	bool ListBox1::OnKeyPress( const KeyboardMessage &keyboard ) {
		if (this->parent_->GetVisible())
		{
			if (!Control::OnKeyPress(keyboard)) {
				if (keyboard.IsAlphaNumeric()) {
					std::locale loc;
					const auto keyChar = std::tolower(keyboard.GetKeyChar(), loc);
					int foundIndex = 0;
					for (auto& c : items_) {
						const auto check = std::tolower(c->GetItemText()[0], loc);
						if (check == keyChar && foundIndex != selectedIndex_) {
							break;
						}

						++foundIndex;
					}

					if (foundIndex < static_cast<int>(items_.size())) {
						SetSelectedIndex(foundIndex);
					}
				}
			}

			return true;
		}
		return false;
	}

	//---------------------------------------------------------------------------
	// StringListItem
	//---------------------------------------------------------------------------
	StringListItem1::StringListItem1( const Misc::AnsiString &_text )
		: text( _text ) { }

	//---------------------------------------------------------------------------
	const Misc::AnsiString &StringListItem1::GetItemText() const {
		return text;
	}

	//---------------------------------------------------------------------------
}
