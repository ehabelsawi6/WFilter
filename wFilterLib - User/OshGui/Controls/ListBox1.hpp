/*
 * OldSchoolHack GUI
 *
 * by KN4CK3R https://www.oldschoolhack.me/
 *
 * See license in OSHGui.hpp
 */

#ifndef OSHGUI_RANK1LIST_HPP
#define OSHGUI_RANK1LIST_HPP

#include "Control.hpp"

namespace OSHGui {
	class ScrollBar;
	class ListItem1;
	namespace ListBoxStyle
	{
		enum CStyle
		{
			Player,
			Guild,
			Union,
			Honor,
			UniqueAndJob,
			Custom,
			Chest,
			Event,
			DynamicShop
		};
	}
	/**
	 * Tritt ein, wenn sich der Wert der SelectedIndex-Eigenschaft �ndert.
	 */
	typedef Event< void( Control * ) > SelectedIndexChangedEvent;
	typedef EventHandler< void( Control * ) > SelectedIndexChangedEventHandler;

	/**
	 * Stellt ein Steuerlement zum Anzeigen einer Liste von Elementen dar.
	 */
	class OSHGUI_EXPORT ListBox1 : public Control {
	public:
		using Control::SetSize;

		/**
		 * Konstruktor der Klasse.
		 */
		ListBox1();
		virtual ~ListBox1();

		/**
		 * Legt die H�he und Breite des Steuerelements fest.
		 *
		 * \param size
		 */
		virtual void SetSize( const Drawing::SizeI &size ) override;
		/**
		 * Legt die Schriftart des Texts im Steuerelement fest.
		 *
		 * \param font
		 */
		virtual void SetFont( const Drawing::FontPtr &font ) override;
		/**
		 * Legt fest, ob die ListBox automatisch zum Element scrollen soll, wenn es hinzugef�gt wird.
		 *
		 * \param autoScrollEnabled
		 */
		void SetAutoScrollEnabled( bool autoScrollEnabled );
		/**
		 * Ruft ab, ob die ListBox automatisch zum Element scrollen soll, wenn es hinzugef�gt wird.
		 *
		 * \return autoScrollEnabled
		 */
		bool GetAutoScrollEnabled() const;
		/**
		 * Gibt das Item an der Stelle index zur�ck.
		 *
		 * \param index
		 * \return das Item
		 */
		ListItem1 *GetItem( int index ) const;
		/**
		 * Legt den ausgew�hlten Index fest.
		 *
		 * \param index
		 */
		void SetSelectedIndex( int index );
		void SetTStyle( uint8_t style );
		/**
		 * Gibt den ausgew�hlten Index zur�ck.
		 *
		 * \return der ausgew�hlte Index
		 */
		int GetSelectedIndex() const;
		/**
		 * Legt das ausgew�hlte Item fest.
		 *
		 * \param item
		 */
		void SetSelectedItem( const Misc::AnsiString &item );
		/**
		 * Ruft das ausgew�hlte Item ab.
		 *
		 * \return das Item
		 */
		ListItem1 *GetSelectedItem() const;
		/**
		 * Gibt die Anzahl der Items zur�ck.
		 *
		 * \return Anzahl der Items
		 */
		int GetItemsCount() const;
		/**
		 * Ruft das SelectedIndexEvent f�r das Steuerelement ab.
		 *
		 * \return selectedIndexEvent
		 */
		SelectedIndexChangedEvent &GetSelectedIndexChangedEvent();
		/**
		 * Erweitert die Gr��e damit die angegebene Anzahl an Items sichtbar ist.
		 */
		void ExpandSizeToShowItems( int count );

		/**
		 * F�gt ein neues Item hinzu.
		 *
		 * \param text der Text des Items
		 */
		void AddItem( const Misc::AnsiString &text );
		void AddItem( ListItem1 *item );
		/**
		 * F�gt ein neues Item am gew�hlten Index hinzu.
		 *
		 * \param index
		 * \param text der Text des Items
		 */
		void InsertItem( int index, const Misc::AnsiString &text );
		void InsertItem( int index, ListItem1 *item );
		/**
		 * L�scht das Item am gew�hlten Index.
		 *
		 * \param index
		 */
		void RemoveItem( int index );
		/**
		 * L�scht alle Items.
		 */
		void Clear();

		/**
		 * �berpr�ft, ob sich der Punkt innerhalb des Steuerelements befindet.
		 *
		 * \param point
		 * \return ja / nein
		 */
		virtual bool Intersect( const Drawing::PointI &point ) const override;

		virtual void DrawSelf( Drawing::RenderContext &context ) override;

	protected:
		virtual void PopulateGeometry() override;

		virtual void OnMouseClick( const MouseMessage &mouse ) override;
		virtual void OnMouseScroll( const MouseMessage &mouse ) override;
		virtual bool OnKeyDown( const KeyboardMessage &keyboard ) override;
		virtual bool OnKeyPress( const KeyboardMessage &keyboard ) override;

	private:
		static const Drawing::SizeI DefaultSize;
		static const Drawing::SizeI DefaultItemAreaPadding;
		static const int DefaultItemPadding;

		void CheckForScrollBar();
		std::vector< int > selected_indices;
		int selectedIndex_;
		int firstVisibleItemIndex_;
		int maxVisibleItems_;
		bool autoScrollEnabled_;

		Drawing::RectangleI itemsRect_;
		Drawing::SizeI itemAreaSize_;

		std::vector< ListItem1* > items_;

		SelectedIndexChangedEvent selectedIndexChangedEvent_;

		ScrollBar *scrollBar_;

		uint8_t thisType;
	};

	class OSHGUI_EXPORT ListItem1 {
	public:
		virtual ~ListItem1() = default;

		virtual const Misc::AnsiString &GetItemText() const = 0;
	};

	class OSHGUI_EXPORT StringListItem1 : public ListItem1 {
	public:
		StringListItem1( const Misc::AnsiString &text );

		virtual const Misc::AnsiString &GetItemText() const override;

	protected:
		Misc::AnsiString text;
	};
}

#endif
