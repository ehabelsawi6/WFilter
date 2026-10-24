/*
 * OldSchoolHack GUI
 *
 * by KN4CK3R https://www.oldschoolhack.me/
 *
 * See license in OSHGui.hpp
 */

#ifndef OSHGUI_GRAPHICS_HPP
#define OSHGUI_GRAPHICS_HPP

#include "GeometryBuffer.hpp"
#include "ColorRectangle.hpp"
#include "Font.hpp"
#include <vector>

namespace OSHGui {
	namespace Drawing {
		class Image;

		class OSHGUI_EXPORT Graphics {
		public:
			Graphics( GeometryBuffer &buffer );
			~Graphics();

			/**
			 * Legt die Farbe fest, mit der gezeichnet wird.
			 *
			 * \param color die Farbe
			 */
			void SetClip( const RectangleF &clip );

			/**
			 * L�scht den Inhalt der Textur.
			 */
			void Clear();

			void Rotate( const PointF &pivot, const Vector &angles );

			void DrawLine( const Color &color, const PointF &from, const PointF &to );
			/**
			 * F�llt das Rechteck.
			 *
			 * \param color
			 * \param origin
			 * \param size
			 */
			void DrawRectangle( const Color &color, const PointF &origin, const SizeF &size );
			/**
			 * F�llt das Rechteck.
			 *
			 * \param color
			 * \param rectangle
			 */
			void DrawRectangle( const Color &color, const RectangleF &rectangle );
			/**
			 * F�llt das Rechteck.
			 *
			 * \param color
			 * \param rectangle
			 */
			void DrawRectangle( const Color &color, float x, float y, float width, float height );
			/**
			 * F�llt das Rechteck.
			 *
			 * \param color
			 * \param origin
			 * \param size
			 */
			void FillRectangle( const Color &color, const PointF &origin, const SizeF &size );
			/**
			 * F�llt das Rechteck.
			 *
			 * \param color
			 * \param rectangle
			 */
			void FillRectangle( const Color &color, const RectangleF &rectangle );
			/**
			 * F�llt das Rechteck.
			 *
			 * \param color
			 * \param rectangle
			 */
			void FillRectangle( const Color &color, float x, float y, float width, float height );
			/**
			 * F�llt die Textur mit einem Farbverlauf.
			 *
			 * \param colors die Eckfarben
			 * \param origin
			 * \param size
			 */
			void FillRectangleGradient( const ColorRectangle &colors, const PointF &origin, const SizeF &size );
			/**
			 * F�llt die Textur mit einem Farbverlauf.
			 *
			 * \param colors die Eckfarben
			 * \param origin
			 * \param size
			 */
			void FillRectangleGradient( const ColorRectangle &colors, const RectangleF &rectangle );
			/**
			 * F�llt die Textur mit einem Farbverlauf.
			 *
			 * \param colors die Eckfarben
			 * \param origin
			 * \param size
			 */
			void FillRectangleGradient( const ColorRectangle &colors, float x, float y, float width, float height );
			void FillTriangle( const Color &color, float x, float y, float width, float height );
			/**
			 * F�llt den Bereich mit der Farbe, der zwischen den Ecken des Polygons liegt.
			 *
			 * \param vertices
			 */
			void FillPolygon( const std::vector< PointF > &vertices, const Color &color );
			/**
			 * F�llt einen Kreis.
			 *
			 * \param color
			 * \param origin
			 * \param radius
			 */
			void FillCircle( const Color &color, const PointF &origin, float radius );
			/**
			 * F�llt einen Kreis.
			 *
			 * \param color
			 * \param x
			 * \param y
			 * \param radius
			 */
			void FillCircle( const Color &color, float x, float y, float radius );
			/**
			 * F�llt eine Ellipse mit der entsprechenden Gr��e um den Mittelpunkt herum.
			 *
			 * \param color
			 * \param origin
			 * \param size
			 */
			void FillEllipse( const Color &color, const PointF &origin, const SizeF &size );

			void FillEllipse( const Color &color, const RectangleF &region );

			void FillEllipse( const Color &color, float x, float y, float width, float height );

			void DrawString( const Misc::AnsiString &text, const FontPtr &font, const Color &color, const PointF &origin );

			void DrawString( const Misc::AnsiString &text, const FontPtr &font, const Color &color, float x, float y );
			void DrawString( const Misc::UnicodeString &text, const FontPtr &font, const Color &color, const PointF &origin );
			void DrawString( const Misc::UnicodeString &text, const FontPtr &font, const Color &color, float x, float y );
			SizeI Graphics::MeasureString(const Misc::AnsiString &text, const FontPtr &font);

			void DrawImage( const std::shared_ptr< Image > &image, const ColorRectangle &color, const PointF &origin );

			void DrawImage( const std::shared_ptr< Image > &image, const ColorRectangle &color, const PointF &origin,
			                const RectangleF &clip );

			void DrawImage( const std::shared_ptr< Image > &image, const ColorRectangle &color, const RectangleF &area );

			void DrawImage( const std::shared_ptr< Image > &image, const ColorRectangle &color, const RectangleF &area,
			                const RectangleF &clip );

		private:
			GeometryBuffer &buffer;
		};
	}
}

#endif
