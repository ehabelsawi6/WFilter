/*
 * OldSchoolHack GUI
 *
 * by KN4CK3R https://www.oldschoolhack.me/
 *
 * See license in OSHGui.hpp
 */

#include "TabPage.hpp"
#include "TabControl.hpp"
#include "../Misc/Exceptions.hpp"

extern OSHGui::Misc::RawDataContainer com_bg_tile_mdata;
extern OSHGui::Misc::RawDataContainer frame_g_action_left_downdata;
extern OSHGui::Misc::RawDataContainer frame_g_action_left_sidedata;
extern OSHGui::Misc::RawDataContainer frame_g_action_left_updata;
extern OSHGui::Misc::RawDataContainer frame_g_action_mid_downdata;
extern OSHGui::Misc::RawDataContainer frame_g_action_mid_updata;
extern OSHGui::Misc::RawDataContainer frame_g_action_right_downdata;
extern OSHGui::Misc::RawDataContainer frame_g_action_right_sidedata;
extern OSHGui::Misc::RawDataContainer frame_g_action_right_updata;

namespace OSHGui
{
	//---------------------------------------------------------------------------
	//Constructor
	//---------------------------------------------------------------------------
	TabPage::TabPage()
		: button_(nullptr)
	{
		type_ = ControlType::TabPage;

		img_center_tile = Drawing::Image::FromMemory(com_bg_tile_mdata);
		img_left_up = Drawing::Image::FromMemory(frame_g_action_left_updata);
		img_up_mid = Drawing::Image::FromMemory(frame_g_action_mid_updata);
		img_right_up = Drawing::Image::FromMemory(frame_g_action_right_updata);
		img_left_side = Drawing::Image::FromMemory(frame_g_action_left_sidedata);
		img_right_side = Drawing::Image::FromMemory(frame_g_action_right_sidedata);
		img_down_mid = Drawing::Image::FromMemory(frame_g_action_mid_downdata);
		img_left_down = Drawing::Image::FromMemory(frame_g_action_left_downdata);
		img_right_down = Drawing::Image::FromMemory(frame_g_action_right_downdata);

		containerPanel_ = new Panel();
		containerPanel_->SetLocation(Drawing::PointI(0, 2));
		containerPanel_->SetBackColor(Drawing::Color::Empty());
		AddSubControl(containerPanel_);

		//ApplyStyle(Application::Instance().GetStyle());
	}
	//---------------------------------------------------------------------------
	//Getter/Setter
	//---------------------------------------------------------------------------
	void TabPage::SetSize(const Drawing::SizeI &size)
	{
		Control::SetSize(size);

		containerPanel_->SetSize(size.InflateEx(-4, -4));
	}
	//---------------------------------------------------------------------------
	void TabPage::SetParent(Control *parent)
	{
#ifndef OSHGUI_DONTUSEEXCEPTIONS
		if (parent == nullptr)
		{
			throw Misc::ArgumentNullException("parent");
		}
		if (parent->GetType() != ControlType::TabControl)
		{
			throw Misc::ArgumentException("parent");
		}
#endif

		Panel::SetParent(parent);
	}
	//---------------------------------------------------------------------------
	void TabPage::SetText(const Misc::AnsiString &text)
	{
		if (button_)
		{
			button_->SetText(text);
		}

		text_ = text;

		Invalidate();
	}
	//---------------------------------------------------------------------------
	const Misc::AnsiString& TabPage::GetText() const
	{
		return text_;
	}
	//---------------------------------------------------------------------------
	const std::deque<Control*>& TabPage::GetControls() const
	{
		return containerPanel_->GetControls();
	}
	//---------------------------------------------------------------------------
	//Runtime-Functions
	//---------------------------------------------------------------------------
	void TabPage::AddControl(Control *control)
	{
		containerPanel_->AddControl(control);
	}
	//---------------------------------------------------------------------------
	void TabPage::RemoveControl(Control *control)
	{
		containerPanel_->RemoveControl(control);
	}
	//---------------------------------------------------------------------------
	void TabPage::DrawSelf(Drawing::RenderContext &context)
	{
		Control::DrawSelf(context);

		containerPanel_->Render();
	}
	//---------------------------------------------------------------------------
	void TabPage::PopulateGeometry()
	{
		using namespace Drawing;

		Graphics g(*geometry_);

		auto windowWidth = this->GetSize().Width;;
		auto windowHeight = this->GetSize().Height;

		RectangleI imageRect;
		RectangleI drawRect;
		RectangleI rect = RectangleI(PointI(12, 12), SizeI(windowWidth - 12, windowHeight - 12));
		auto rectLocation = rect.GetLocation();

		for (int x = rectLocation.X; x < rect.GetRight(); x += 128)
		{
			for (int y = rectLocation.Y; y < rect.GetBottom(); y += 128)
			{
				drawRect = RectangleI(x, y, std::min(128, rect.GetRight() - x), std::min(128, rect.GetBottom() - y));
				imageRect = RectangleI(0, 0, drawRect.GetWidth(), drawRect.GetHeight());

				g.DrawImage(img_center_tile, Color::FromRGB(255, 255, 255), drawRect, imageRect);
			}
		}

		g.DrawImage(img_left_up, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, 0), SizeI(12, 12)));

		auto partSizeTop = 12;

		for (auto i = 0; i <= (windowWidth - 12) / 12; i++)
		{
			if (partSizeTop + 12 > windowWidth)
			{
				g.DrawImage(img_up_mid, Color::FromRGB(255, 255, 255), RectangleI(PointI(partSizeTop, 0), SizeI(windowWidth - partSizeTop - 12, 12)));
				partSizeTop = windowWidth - 12;
			}
			else
			{
				g.DrawImage(img_up_mid, Color::FromRGB(255, 255, 255), RectangleI(PointI(partSizeTop-5, 0), SizeI(20, 12)));
				partSizeTop += 12;
			}
		}
		g.DrawImage(img_right_up, Color::FromRGB(255, 255, 255), RectangleI(PointI(windowWidth - 12, 0), SizeI(12, 12)));

		g.DrawImage(img_left_down, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, windowHeight - 12), SizeI(12, 12)));

		auto partSizeBottom = 12;

		for (auto i = 0; i <= ((windowWidth - 12) / 12); i++)
		{
			if (partSizeBottom + 12 > windowWidth)
			{
				g.DrawImage(img_down_mid, Color::FromRGB(255, 255, 255), RectangleI(PointI(partSizeBottom, windowHeight - 12), SizeI(windowWidth - partSizeBottom - 12, 12)));
				partSizeBottom = windowWidth - 12;
			}
			else
			{
				g.DrawImage(img_down_mid, Color::FromRGB(255, 255, 255), RectangleI(PointI(partSizeBottom, windowHeight - 12), SizeI(12, 12)));
				partSizeBottom += 12;
			}
		}

		g.DrawImage(img_right_down, Color::FromRGB(255, 255, 255), RectangleI(PointI(windowWidth - 12, windowHeight - 12), SizeI(12, 12)));

		auto centerLeftBorderPartSize = 10;

		for (auto i = 0; i <= (windowHeight) / 20; i++)
		{
			if (centerLeftBorderPartSize + 20 > windowHeight)
			{
				auto h = windowHeight - centerLeftBorderPartSize - 20;

				g.DrawImage(img_left_side, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, centerLeftBorderPartSize), SizeI(12, h)));
				centerLeftBorderPartSize = windowHeight - 20;
			}
			else
			{
				g.DrawImage(img_left_side, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, centerLeftBorderPartSize), SizeI(12, 20)));
				centerLeftBorderPartSize += 20;
			}
		}

		auto centerRightBorderPartSize = 10;

		for (auto i = 0; i <= (windowHeight) / 20; i++)
		{
			if (centerRightBorderPartSize + 20 > windowHeight)
			{
				g.DrawImage(img_right_side, Color::FromRGB(255, 255, 255), RectangleI(PointI(windowWidth - 12, centerRightBorderPartSize), SizeI(12, windowHeight - centerRightBorderPartSize - 12)));
				centerRightBorderPartSize = windowHeight - 20;
			}
			else
			{
				g.DrawImage(img_right_side, Color::FromRGB(255, 255, 255), RectangleI(PointI(windowWidth - 12, centerRightBorderPartSize), SizeI(12, 20)));
				centerRightBorderPartSize += 20;
			}
		}
	}
	//---------------------------------------------------------------------------
}