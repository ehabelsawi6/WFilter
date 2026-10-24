/*
 * OldSchoolHack GUI
 *
 * by KN4CK3R https://www.oldschoolhack.me/
 *
 * See license in OSHGui.hpp
 */

#ifndef OSHGUI_TITLE_LISTBOX_HPP
#define OSHGUI_TITLE_LISTBOX_HPP

#include "Control.hpp"

namespace OSHGui {
	class ScrollBar;
	class TListItem;

	/**
	 * Tritt ein, wenn sich der Wert der SelectedIndex-Eigenschaft ändert.
	 */
	typedef Event< void( Control * ) > SelectedIndexChangedEvent;
	typedef EventHandler< void( Control * ) > SelectedIndexChangedEventHandler;

	/**
	 * Stellt ein Steuerlement zum Anzeigen einer Liste von Elementen dar.
	 */
	class OSHGUI_EXPORT TitleListBox : public Control {
	public:
		using Control::SetSize;

		/**
		 * Konstruktor der Klasse.
		 */
		TitleListBox();
		virtual ~TitleListBox();

		/**
		 * Legt die Höhe und Breite des Steuerelements fest.
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
		 * Legt fest, ob die ListBox automatisch zum Element scrollen soll, wenn es hinzugefügt wird.
		 *
		 * \param autoScrollEnabled
		 */
		void SetAutoScrollEnabled( bool autoScrollEnabled );
		/**
		 * Ruft ab, ob die ListBox automatisch zum Element scrollen soll, wenn es hinzugefügt wird.
		 *
		 * \return autoScrollEnabled
		 */
		bool GetAutoScrollEnabled() const;
		/**
		 * Gibt das Item an der Stelle index zurück.
		 *
		 * \param index
		 * \return das Item
		 */
		TListItem *GetItem( int index ) const;
		/**
		 * Legt den ausgewählten Index fest.
		 *
		 * \param index
		 */
		void SetSelectedIndex( int index );
		/**
		 * Gibt den ausgewählten Index zurück.
		 *
		 * \return der ausgewählte Index
		 */
		int GetSelectedIndex() const;
		/**
		 * Legt das ausgewählte Item fest.
		 *
		 * \param item
		 */
		void SetSelectedItem( const Misc::AnsiString &item );
		/**
		 * Ruft das ausgewählte Item ab.
		 *
		 * \return das Item
		 */
		TListItem *GetSelectedItem() const;
		/**
		 * Gibt die Anzahl der Items zurück.
		 *
		 * \return Anzahl der Items
		 */
		int GetItemsCount() const;
		/**
		 * Ruft das SelectedIndexEvent für das Steuerelement ab.
		 *
		 * \return selectedIndexEvent
		 */
		SelectedIndexChangedEvent &GetSelectedIndexChangedEvent();
		/**
		 * Erweitert die Größe damit die angegebene Anzahl an Items sichtbar ist.
		 */
		void ExpandSizeToShowItems( int count );

		/**
		 * Fügt ein neues Item hinzu.
		 *
		 * \param text der Text des Items
		 */
		void AddItem( const Misc::AnsiString &text );
		void AddItem( TListItem *item );
		/**
		 * Fügt ein neues Item am gewählten Index hinzu.
		 *
		 * \param index
		 * \param text der Text des Items
		 */
		void InsertItem( int index, const Misc::AnsiString &text );
		void InsertItem( int index, TListItem *item );
		/**
		 * Löscht das Item am gewählten Index.
		 *
		 * \param index
		 */
		void RemoveItem( int index );
		/**
		 * Löscht alle Items.
		 */
		void Clear();

		/**
		 * Überprüft, ob sich der Punkt innerhalb des Steuerelements befindet.
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

		std::vector< TListItem* > items_;

		SelectedIndexChangedEvent selectedIndexChangedEvent_;

		ScrollBar *scrollBar_;
	};

	class OSHGUI_EXPORT TListItem {
	public:
		virtual ~TListItem() = default;

		virtual const Misc::AnsiString &GetItemText() const = 0;
	};

	class OSHGUI_EXPORT TStringListItem : public TListItem {
	public:
		TStringListItem( const Misc::AnsiString &text );

		virtual const Misc::AnsiString &GetItemText() const override;

	protected:
		Misc::AnsiString text;
	};
}

#endif
