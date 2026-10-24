/*
 * OldSchoolHack GUI
 *
 * by KN4CK3R https://www.oldschoolhack.me/
 *
 * See license in OSHGui.hpp
 */

#ifndef OSHGUI_MULTILISTBOX_HPP
#define OSHGUI_MULTILISTBOX_HPP

#include "Control.hpp"
struct MultiListItem
{
	int index;
	OSHGui::Misc::AnsiString item1;
	OSHGui::Misc::AnsiString item2;
	OSHGui::Misc::AnsiString item3;
};
namespace OSHGui {
	class ScrollBar;
	class ListItem;

	/**
	 * Tritt ein, wenn sich der Wert der SelectedIndex-Eigenschaft ändert.
	 */
	typedef Event< void( Control * ) > SelectedIndexChangedEvent;
	typedef EventHandler< void( Control * ) > SelectedIndexChangedEventHandler;

	/**
	 * Stellt ein Steuerlement zum Anzeigen einer Liste von Elementen dar.
	 */
	class OSHGUI_EXPORT MultiListBox : public Control {
	public:
		using Control::SetSize;

		/**
		 * Konstruktor der Klasse.
		 */
		MultiListBox();
		virtual ~MultiListBox();

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
		 * Legt fest, ob die MultiListBox automatisch zum Element scrollen soll, wenn es hinzugefügt wird.
		 *
		 * \param autoScrollEnabled
		 */
		void SetAutoScrollEnabled( bool autoScrollEnabled );
		/**
		 * Ruft ab, ob die MultiListBox automatisch zum Element scrollen soll, wenn es hinzugefügt wird.
		 *
		 * \return autoScrollEnabled
		 */
		bool GetAutoScrollEnabled() const;
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
		void SetSelectedItem(const MultiListItem* m_item);
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
		void AddItem(MultiListItem* item);
		/**
		 * Fügt ein neues Item am gewählten Index hinzu.
		 *
		 * \param index
		 * \param text der Text des Items
		 */
		void InsertItem(int index, MultiListItem* item);
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

		std::vector< MultiListItem* > items_;

		SelectedIndexChangedEvent selectedIndexChangedEvent_;

		ScrollBar *scrollBar_;
	};
}

#endif