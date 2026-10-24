/*
 * OldSchoolHack GUI
 *
 * by KN4CK3R https://www.oldschoolhack.me/
 *
 * See license in OSHGui.hpp
 */

#ifndef OSHGUI_PANEL_HPP
#define OSHGUI_PANEL_HPP

#include "Control.hpp"

namespace OSHGui {
	/**
	 * Wird zum Gruppieren von Auflistungen von Steuerelementen verwendet.
	 */
	class OSHGUI_EXPORT Panel : public Control {
	public:
		/**
		 * Konstruktor der Klasse.
		 */
		Panel();
		void SetPanelDrawable(bool enabled);

	protected:
		virtual void PopulateGeometry() override;

	private:
		static const Drawing::SizeI DefaultSize;
		Drawing::ImagePtr img_center_tile;
		Drawing::ImagePtr img_left_up;
		Drawing::ImagePtr img_up_mid;
		Drawing::ImagePtr img_right_up;
		Drawing::ImagePtr img_left_side;
		Drawing::ImagePtr img_right_side;
		Drawing::ImagePtr img_left_down;
		Drawing::ImagePtr img_down_mid;
		Drawing::ImagePtr img_right_down;
		bool drawable;
	};
}

#endif
