/*
 * OldSchoolHack GUI
 *
 * by KN4CK3R https://www.oldschoolhack.me/
 *
 * See license in OSHGui.hpp
 */

#include "Panel.hpp"
#include "../Misc/Exceptions.hpp"


extern OSHGui::Misc::RawDataContainer com_bg_tile_cdata;
extern OSHGui::Misc::RawDataContainer ub_pet_wnd_left_downdata;
extern OSHGui::Misc::RawDataContainer ub_pet_wnd_left_sidedata;
extern OSHGui::Misc::RawDataContainer ub_pet_wnd_left_updata;
extern OSHGui::Misc::RawDataContainer ub_pet_wnd_mid_downdata;
extern OSHGui::Misc::RawDataContainer ub_pet_wnd_mid_updata;
extern OSHGui::Misc::RawDataContainer ub_pet_wnd_right_downdata;
extern OSHGui::Misc::RawDataContainer ub_pet_wnd_right_sidedata;
extern OSHGui::Misc::RawDataContainer ub_pet_wnd_right_updata;
namespace OSHGui {
	void Panel::SetPanelDrawable(bool enabled)
	{
		this->drawable = enabled;
	}
	//---------------------------------------------------------------------------
	//static attributes
	//---------------------------------------------------------------------------
	const Drawing::SizeI Panel::DefaultSize( 200, 200 );
	//---------------------------------------------------------------------------
	//Constructor
	//---------------------------------------------------------------------------
	Panel::Panel() {
		type_ = ControlType::Panel;

		SetSize( DefaultSize );

		ApplyStyle( Application::Instance().GetStyle() );

		isFocusable_ = false;

		img_center_tile = Drawing::Image::FromMemory(com_bg_tile_cdata);
		img_left_up = Drawing::Image::FromMemory(ub_pet_wnd_left_updata);
		img_up_mid = Drawing::Image::FromMemory(ub_pet_wnd_mid_updata);
		img_right_up = Drawing::Image::FromMemory(ub_pet_wnd_right_updata);
		img_left_side = Drawing::Image::FromMemory(ub_pet_wnd_left_sidedata);
		img_right_side = Drawing::Image::FromMemory(ub_pet_wnd_right_sidedata);
		img_down_mid = Drawing::Image::FromMemory(ub_pet_wnd_mid_downdata);
		img_left_down = Drawing::Image::FromMemory(ub_pet_wnd_left_downdata);
		img_right_down = Drawing::Image::FromMemory(ub_pet_wnd_right_downdata);
		drawable = true;
	}

	//---------------------------------------------------------------------------
	//Runtime-Functions
	//---------------------------------------------------------------------------
	void Panel::PopulateGeometry() {
		if (drawable)
		{
			using namespace Drawing;

			Graphics g(*geometry_);
			auto windowWidth = this->GetSize().Width;;
			auto windowHeight = this->GetSize().Height;
			if (windowHeight > 0 && windowWidth > 0)
			{
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
						g.DrawImage(img_up_mid, Color::FromRGB(255, 255, 255), RectangleI(PointI(partSizeTop - 6, 0), SizeI(windowWidth - partSizeTop - 12, 12)));
						partSizeTop = windowWidth - 12;
					}
					else
					{
						g.DrawImage(img_up_mid, Color::FromRGB(255, 255, 255), RectangleI(PointI(partSizeTop, 0), SizeI(12, 12)));
						partSizeTop += 12;
					}
				}
				g.DrawImage(img_right_up, Color::FromRGB(255, 255, 255), RectangleI(PointI(windowWidth - 12, 0), SizeI(12, 12)));

				auto centerLeftBorderPartSize = 10;

				for (auto i = 0; i <= (windowHeight) / 12; i++)
				{
					if (centerLeftBorderPartSize + 12 > windowHeight)
					{
						auto h = windowHeight - centerLeftBorderPartSize - 12;

						g.DrawImage(img_left_side, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, centerLeftBorderPartSize), SizeI(12, h)));
						centerLeftBorderPartSize = windowHeight - 12;
					}
					else
					{
						g.DrawImage(img_left_side, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, centerLeftBorderPartSize), SizeI(12, 12)));
						centerLeftBorderPartSize += 12;
					}
				}

				g.DrawImage(img_left_down, Color::FromRGB(255, 255, 255), RectangleI(PointI(0, windowHeight - 12), SizeI(12, 12)));

				auto centerRightBorderPartSize = 10;

				for (auto i = 0; i <= (windowHeight) / 12; i++)
				{
					if (centerRightBorderPartSize + 12 > windowHeight)
					{
						g.DrawImage(img_right_side, Color::FromRGB(255, 255, 255), RectangleI(PointI(windowWidth - 12, centerRightBorderPartSize), SizeI(12, windowHeight - centerRightBorderPartSize - 12)));
						centerRightBorderPartSize = windowHeight - 12;
					}
					else
					{
						g.DrawImage(img_right_side, Color::FromRGB(255, 255, 255), RectangleI(PointI(windowWidth - 12, centerRightBorderPartSize), SizeI(12, 12)));
						centerRightBorderPartSize += 12;
					}
				}

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
			}
		}
	}

	//---------------------------------------------------------------------------
}
