#include "UnicodeLabel.h"

#include "../../../GameMain/GameMain.h"


void UnicodeLabel::PopulateGeometry()
{
	if (isVisible_)
	{
		Graphics g(*geometry_);
		g.DrawString(g_StringHelper->ws2s(L"翻譯 Ölçek "), m_Font, Color::FromARGB( 200, 255, 255, 255 ), PointF( 1, 1 ) );

	}
}
UnicodeLabel::UnicodeLabel()
{
	m_Font = FontManager::LoadFontFromFile("C:\\arial-unicode-ms.ttf", 18.0f, false);
	//m_Font = FontManager::LoadFont("Times New Roman",18.0f,false);
}
UnicodeLabel::~UnicodeLabel()
{
}