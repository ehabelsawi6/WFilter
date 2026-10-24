/*
 * OldSchoolHack GUI
 *
 * by KN4CK3R https://www.oldschoolhack.me/
 *
 * See license in OSHGui.hpp
 */

#ifndef OSHGUI_TABPAGE_HPP
#define OSHGUI_TABPAGE_HPP

#include "Panel.hpp"
#include "TabControl.hpp"

namespace OSHGui
{
	/**
	 * Wird zum Gruppieren von Auflistungen von Steuerelementen verwendet.
	 */
	class OSHGUI_EXPORT TabPage : public Panel
	{
		friend TabControl;

	public:
		using Panel::SetSize;

		/**
		 * Konstruktor der Klasse.
		 */
		TabPage();

		/**
		 * Legt die H�he und Breite des Steuerelements fest.
		 *
		 * \param size
		 */
		virtual void SetSize(const Drawing::SizeI &size) override;
		/**
		 * Legt das �bergeordnete Steuerelement fest.
		 * Kann nur ein TabControl sein!
		 *
		 * \param parent
		 */
		virtual void SetParent(Control *parent) override;
		/**
		 * Legt den Text fest.
		 *
		 * \param text
		 */
		void SetText(const Misc::AnsiString &text);
		/**
		 * Ruft den Text ab.
		 *
		 * \return der Text
		 */
		const Misc::AnsiString& GetText() const;
		/**
		 * Gibt eine Liste der untergeordneten Steuerelemente zur�ck.
		 *
		 * \return parent
		 */
		virtual const std::deque<Control*>& GetControls() const override;

		/**
		 * F�gt ein untergeordnetes Steuerelement hinzu.
		 *
		 * \param control
		 */
		virtual void AddControl(Control *control) override;
		/**
		 * Entfernt ein untergeordnetes Steuerelement.
		 *
		 * \param control
		 */
		virtual void RemoveControl(Control *control) override;

	protected:
		virtual void DrawSelf(Drawing::RenderContext &context) override;
		virtual void PopulateGeometry();

	private:
		Misc::AnsiString text_;
		Drawing::ImagePtr img_center_tile;
		Drawing::ImagePtr img_left_up;
		Drawing::ImagePtr img_up_mid;
		Drawing::ImagePtr img_right_up;
		Drawing::ImagePtr img_left_side;
		Drawing::ImagePtr img_right_side;
		Drawing::ImagePtr img_left_down;
		Drawing::ImagePtr img_down_mid;
		Drawing::ImagePtr img_right_down;

		Panel *containerPanel_;
		TabControl::TabControlButton *button_;
	};
}

#endif