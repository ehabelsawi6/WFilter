/*
 * OldSchoolHack GUI
 *
 * by KN4CK3R https://www.oldschoolhack.me/
 *
 * See license in OSHGui.hpp
 */

#ifndef OSHGUI_TABCONTROL_HPP
#define OSHGUI_TABCONTROL_HPP

#include <memory>
#include "Control.hpp"

namespace OSHGui
{
	class Label;
	class TabPage;

	/**
	 * Tritt ein, wenn sich der Wert der SelectedIndex-Eigenschaft �ndert.
	 */
	typedef Event<void(Control*)> SelectedIndexChangedEvent;
	typedef EventHandler<void(Control*)> SelectedIndexChangedEventHandler;

	/**
	 * Verwaltet eine Gruppe zusammengeh�riger Registerkarten.
	 */
	class OSHGUI_EXPORT TabControl : public Control
	{
		friend TabPage;

	public:
		using Control::SetSize;

		/**
		 * Konstruktor der Klasse.
		 */
		TabControl();

		/**
		 * Legt die H�he und Breite des Steuerelements fest.
		 *
		 * \param size
		 */
		virtual void SetSize(const Drawing::SizeI &size) override;
		/**
		 * Legt die Fordergrundfarbe des Steuerelements fest.
		 *
		 * \param color
		 */
		virtual void SetForeColor(const Drawing::Color &color) override;
		/**
		 * Legt die Hintergrundfarbe des Steuerelements fest.
		 *
		 * \param color
		 */
		virtual void SetBackColor(const Drawing::Color &color) override;
		/**
		 * Ruft die TabPage mit dem entsprechenden Namen ab.
		 *
		 * \param name der Name
		 * \return Zeiger zur TabPage
		 */
		TabPage* GetTabPage(const Misc::AnsiString &name) const;
		/**
		 * Ruft die TabPage am entsprechenden Index ab.
		 *
		 * \param index
		 * \return Zeiger zur TabPage
		 */
		TabPage* GetTabPage(int index) const;
		/**
		 * Legt den Index der derzeit ausgew�hlten Registerkarte fest.
		 *
		 * \param index
		 */
		void SetSelectedIndex(int index);
		/**
		 * Ruft den Index der derzeit ausgew�hlten Registerkarte ab.
		 *
		 * \return index
		 */
		int GetSelectedIndex() const;
		/**
		 * Legt die derzeit ausgew�hlte Registerkarte fest.
		 *
		 * \param tabPage
		 */
		void SetSelectedTabPage(TabPage *tabPage);
		/**
		 * Ruft die derzeit ausgew�hlte Registerkarte ab.
		 *
		 * \return selectedTabPage
		 */
		TabPage* GetSelectedTabPage() const;
		/**
		 * Ruft das SelectedIndexEvent f�r das Steuerelement ab.
		 *
		 * \return selectedIndexEvent
		 */
		SelectedIndexChangedEvent& GetSelectedIndexChangedEvent();

		/**
		 * F�gt dem TabControl eine neue TabPage hinzu.
		 *
		 * \param tabPage
		 */
		void AddTabPage(TabPage *tabPage);
		/**
		 * Entfernt eine TabPage aus dem TabControl.
		 *
		 * \param tabPage
		 */
		void RemoveTabPage(TabPage *tabPage);

		/**
		 * Berechnet die absolute Position des Steuerelements.
		 */
		virtual void CalculateAbsoluteLocation() override;
		/**
		 * Veranlasst das Steuerelement, sein Aussehen dem Style anzupassen.
		 *
		 * \param style
		 */
		virtual void ApplyStyle(const Drawing::Style &style) override;

	protected:
		virtual void DrawSelf(Drawing::RenderContext &context) override;

	private:
		static const Drawing::SizeI DefaultSize;

		void CalculateButtonLocationAndCount();

		struct TabPageButtonBinding;
		void SelectBinding(TabPageButtonBinding &binding);

		SelectedIndexChangedEvent selectedIndexChangedEvent_;

		class TabControlButton;
		struct TabPageButtonBinding
		{
			int Index;
			TabPage *TabPage;
			TabControlButton *Button;
		};

		class TabControlButton : public Control
		{
		public:
			TabControlButton(TabPageButtonBinding &binding);

			virtual void SetForeColor(const Drawing::Color &color) override;
			void SetText(const Misc::AnsiString &text);
			void SetActive(bool active);

			virtual void CalculateAbsoluteLocation() override;

		protected:
			virtual void DrawSelf(Drawing::RenderContext &context) override;
			virtual void PopulateGeometry() override;

			virtual void OnMouseClick(const MouseMessage &mouse) override;

		private:
			static const Drawing::PointI DefaultLabelOffset;

			TabPageButtonBinding &binding_;
			std::unique_ptr<Label> label_;

			bool active_;

			Drawing::ImagePtr button_img_inactive_left;
			Drawing::ImagePtr button_img_inactive_mid;
			Drawing::ImagePtr button_img_inactive_right;

			Drawing::ImagePtr button_img_inactive_left_hover;
			Drawing::ImagePtr button_img_inactive_mid_hover;
			Drawing::ImagePtr button_img_inactive_right_hover;
			
			Drawing::ImagePtr button_img_inactive_left_active;
			Drawing::ImagePtr button_img_inactive_mid_active;
			Drawing::ImagePtr button_img_inactive_right_active;
		};

		TabPageButtonBinding *selected_;
		std::vector<std::unique_ptr<TabPageButtonBinding>> bindings_;

		class TabControlSwitchButton : public Control
		{
		public:
			enum class TabControlSwitchButtonDirection
			{
				Left,
				Right
			};

			static const Drawing::SizeI DefaultSize;

			TabControlSwitchButton(TabControlSwitchButtonDirection direction);

		protected:
			virtual void PopulateGeometry() override;

		private:
			TabControlSwitchButtonDirection direction_;
		};

		int startIndex_;
		int maxIndex_;
		TabControlSwitchButton *lastSwitchButton_;
		TabControlSwitchButton *nextSwitchButton_;
	};
}

#endif