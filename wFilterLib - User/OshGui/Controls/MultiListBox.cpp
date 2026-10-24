/*
* OldSchoolHack GUI
*
* by KN4CK3R https://www.oldschoolhack.me/
*
* See license in OSHGui.hpp
*/

#include <locale>
#include "MultiListBox.hpp"
#include "ScrollBar.hpp"
#include "../Misc/Exceptions.hpp"
#include "../Misc/Intersection.hpp"
#include "Timer.hpp"

namespace OSHGui {
	//---------------------------------------------------------------------------
	//static attributes
	//---------------------------------------------------------------------------
	const Drawing::SizeI MultiListBox::DefaultSize(120, 106);
	const Drawing::SizeI MultiListBox::DefaultItemAreaPadding(8, 8);
	const int MultiListBox::DefaultItemPadding(25);
	//---------------------------------------------------------------------------
	//Constructor
	//---------------------------------------------------------------------------
	MultiListBox::MultiListBox()
		: selectedIndex_(-1),
		firstVisibleItemIndex_(0),
		autoScrollEnabled_(true) {
		type_ = ControlType::MultiListBox;

		scrollBar_ = new ScrollBar();
		scrollBar_->SetVisible(true);
		scrollBar_->GetScrollEvent() += ScrollEventHandler([this](Control *, ScrollEventArgs &args)
		{
			firstVisibleItemIndex_ = args.NewValue;
			Invalidate();
		});
		scrollBar_->GetFocusLostEvent() += FocusLostEventHandler([this](Control *, Control *newFocusedControl)
		{
			if (newFocusedControl != this) {
				OnLostFocus(newFocusedControl);
			}
		});
		AddSubControl(scrollBar_);

		SetSize(DefaultSize);

		maxVisibleItems_ = GetHeight() / (GetFont()->GetFontHeight() + DefaultItemPadding);

		ApplyStyle(Application::Instance().GetStyle());
	}

	//---------------------------------------------------------------------------
	MultiListBox::~MultiListBox() {
		Clear();
	}

	//---------------------------------------------------------------------------
	//Getter/Setter
	//---------------------------------------------------------------------------
	void MultiListBox::SetSize(const Drawing::SizeI &size) {
		Control::SetSize(size);

		itemAreaSize_ = size.InflateEx(8, 8);
		if (scrollBar_->GetVisible()) {
			itemAreaSize_.Width -= scrollBar_->GetWidth();
		}

		scrollBar_->SetLocation(size.Width - 10, 1);
		scrollBar_->SetSize(scrollBar_->GetWidth(), size.Height);

		CheckForScrollBar();
	}

	//---------------------------------------------------------------------------
	void MultiListBox::SetFont(const Drawing::FontPtr &font) {
		Control::SetFont(font);

		CheckForScrollBar();
	}

	//---------------------------------------------------------------------------
	void MultiListBox::SetAutoScrollEnabled(bool autoScrollEnabled) {
		autoScrollEnabled_ = autoScrollEnabled;
	}

	//---------------------------------------------------------------------------
	bool MultiListBox::GetAutoScrollEnabled() const {
		return autoScrollEnabled_;
	}

	void MultiListBox::SetSelectedIndex(int index) {
		if (selectedIndex_ == index) {
			return;
		}

#ifndef OSHGUI_DONTUSEEXCEPTIONS
		if (index < 0 || index >= static_cast<int>(items_.size()))
		{
			throw Misc::ArgumentOutOfRangeException("index");
		}
#endif

		selectedIndex_ = index;

		selectedIndexChangedEvent_.Invoke(this);

		if (index - firstVisibleItemIndex_ >= maxVisibleItems_ || index - firstVisibleItemIndex_ < 0) {
			for (firstVisibleItemIndex_ = 0; firstVisibleItemIndex_ <= index; firstVisibleItemIndex_ += maxVisibleItems_);
			firstVisibleItemIndex_ -= maxVisibleItems_;
			if (firstVisibleItemIndex_ < 0) {
				firstVisibleItemIndex_ = 0;
			}
			scrollBar_->SetValue(firstVisibleItemIndex_);
		}

		Invalidate();
	}

	//---------------------------------------------------------------------------
	int MultiListBox::GetSelectedIndex() const {
		return selectedIndex_;
	}

	//---------------------------------------------------------------------------
	void MultiListBox::SetSelectedItem(const MultiListItem* m_item) {
		auto index = 0;
		for (auto &&item : items_) {
			if (item->index == m_item->index) {
				SetSelectedIndex(index);
				return;
			}
			++index;
		}
	}

	//---------------------------------------------------------------------------
	int MultiListBox::GetItemsCount() const {
		return items_.size();
	}

	//---------------------------------------------------------------------------
	SelectedIndexChangedEvent &MultiListBox::GetSelectedIndexChangedEvent() {
		return selectedIndexChangedEvent_;
	}

	//---------------------------------------------------------------------------
	//Runtime-Functions
	//---------------------------------------------------------------------------
	bool MultiListBox::Intersect(const Drawing::PointI& point) const {
		return Intersection::TestRectangle(absoluteLocation_,
			scrollBar_->GetVisible() ? size_.InflateEx(-scrollBar_->GetWidth(), 0) : size_,
			point);
	}
	//---------------------------------------------------------------------------
	void MultiListBox::ExpandSizeToShowItems(int count) {
		const auto itemHeight = GetFont()->GetFontHeight() + DefaultItemPadding;
		const auto newHeight = count * itemHeight;

		SetSize(GetWidth(), newHeight + DefaultItemAreaPadding.Height);
	}

	//---------------------------------------------------------------------------
	void MultiListBox::AddItem(MultiListItem* item) {
		InsertItem(item->index , item);
	}

	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	void MultiListBox::InsertItem(int index, MultiListItem* item) {
		items_.push_back(item);
		CheckForScrollBar();

		if (autoScrollEnabled_) {
			scrollBar_->SetValue(index);
		}

		Invalidate();
	}

	//---------------------------------------------------------------------------
	void MultiListBox::RemoveItem(int index) {
#ifndef OSHGUI_DONTUSEEXCEPTIONS
		if (index < 0 || index >= (int)items_.size())
		{
			throw Misc::ArgumentOutOfRangeException("index");
		}
#endif

		items_.erase(items_.begin() + index);

		if (scrollBar_->GetVisible()) {
			scrollBar_->SetMaximum(items_.size() - maxVisibleItems_);
		}
		if (selectedIndex_ >= static_cast<int>(items_.size())) {
			selectedIndex_ = items_.size() - 1;

			selectedIndexChangedEvent_.Invoke(this);
		}

		Invalidate();
	}

	//---------------------------------------------------------------------------
	void MultiListBox::Clear() {
		items_.clear();

		scrollBar_->SetMaximum(1);

		selectedIndex_ = -1;

		CheckForScrollBar();

		Invalidate();
	}

	//---------------------------------------------------------------------------
	void MultiListBox::CheckForScrollBar() {
		const auto itemHeight = static_cast<int>(GetFont()->GetFontHeight()) + DefaultItemPadding;

		maxVisibleItems_ = std::max(1, itemAreaSize_.Height / itemHeight);

		if (!items_.empty() && items_.size() * itemHeight > itemAreaSize_.Height) {
			if (!scrollBar_->GetVisible()) {
				itemAreaSize_.Width -= scrollBar_->GetWidth();
			}
			scrollBar_->SetMaximum(items_.size() - maxVisibleItems_);
			scrollBar_->SetVisible(true);
		}
		else if (scrollBar_->GetVisible()) {
			scrollBar_->SetVisible(false);
			itemAreaSize_.Width += scrollBar_->GetWidth();
		}
	}

	//---------------------------------------------------------------------------
	void MultiListBox::DrawSelf(Drawing::RenderContext &context) {
		Control::DrawSelf(context);
		if (GetAutoScrollEnabled())
			scrollBar_->Render();
	}
	//---------------------------------------------------------------------------
	void MultiListBox::PopulateGeometry() {
		using namespace Drawing;

		Graphics g(*geometry_);

		//g.FillRectangle(Color::Black(), PointF(1, 1), GetSize() - SizeF(2, 2));


		const auto itemX = 4;
		const auto itemY = 5;
		const auto padding = DefaultItemPadding;
		int i = 0;
		for (i; i < maxVisibleItems_ && i + firstVisibleItemIndex_ < static_cast<int>(items_.size()); ++i) {
			//if (firstVisibleItemIndex_ + i == selectedIndex_) {
			//	g.DrawRectangle(Color::FromARGB(255, 255, 178, 82), PointF(itemX - 1, itemY + i * padding - 1),
			//		SizeF(itemAreaSize_.Width + 8, padding));
			//	g.DrawString(items_[firstVisibleItemIndex_ + i]->item1, GetFont(), Color::White(),
			//		PointF(itemX + 1, itemY + i * padding));
			//	g.DrawString(items_[firstVisibleItemIndex_ + i]->item2, GetFont(), Color::White(),
			//		PointF(itemX + 148, itemY + i * padding));
			//	g.DrawString(items_[firstVisibleItemIndex_ + i]->item3, GetFont(), Color::White(),
			//		PointF(itemX + 190, itemY + i * padding));
			//}
			//else {

				auto state = items_[firstVisibleItemIndex_ + i]->item2;
				//g.DrawRectangle(Color::FromARGB(50, 74, 74, 74), PointF(itemX - 1, itemY + i * padding - 1),
				//	SizeF(itemAreaSize_.Width + 8, padding));
				g.DrawString(items_[firstVisibleItemIndex_ + i]->item1, GetFont(), (state == "Alive") ? Color::Lime() : Color::Gray(),
					PointF(itemX + 3, itemY + i * padding));
				g.DrawString(state, GetFont(), (state == "Alive") ? Color::Lime() : Color::Gray(),
					PointF(itemX + 207, itemY + i * padding));
				g.DrawString(items_[firstVisibleItemIndex_ + i]->item3, GetFont(), (state == "Alive") ? Color::Lime() : Color::Gray(),
					PointF(itemX + 253, itemY + i * padding));
			//}
		}
		//if (items_.size() <= 20)
		//{
		//	for (size_t j = 0; i != 19; j++)
		//	{
		//		i++;
		//		g.DrawRectangle(Color::FromARGB(50, 74, 74, 74), PointF(itemX - 1, itemY + i * padding - 1),
		//			SizeF(itemAreaSize_.Width + 8, padding));
		//	}
		//}
	}

	//---------------------------------------------------------------------------
	//Event-Handling
	//---------------------------------------------------------------------------
	void MultiListBox::OnMouseClick(const MouseMessage &mouse) {
		Control::OnMouseClick(mouse);

		if (Intersection::TestRectangle(absoluteLocation_.OffsetEx(4, 4), itemAreaSize_, mouse.GetLocation())) {
			const auto clickedIndex = firstVisibleItemIndex_ + (mouse.GetLocation().Y - absoluteLocation_.Y - 4) / (GetFont()
				->GetFontHeight() + DefaultItemPadding);
			if (clickedIndex < items_.size()) {
				SetSelectedIndex(clickedIndex);
			}
		}
	}

	//---------------------------------------------------------------------------
	void MultiListBox::OnMouseScroll(const MouseMessage& mouse) {

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
	bool MultiListBox::OnKeyDown(const KeyboardMessage &keyboard) {
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

		return false;
	}
}
