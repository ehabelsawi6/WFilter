#include "CustomLabel.h"


void CustomLabel::PopulateGeometry()
{
	if (isVisible_)
	{
		Graphics g(*geometry_);
		auto text = this->GetText();
		auto maxTextLength = 54;
		auto textWrapAvg = round(text.length() / maxTextLength);
		
		auto location = this->GetLocation();
		auto lineHeight = 0;
		for (size_t i = 0; i <= textWrapAvg; i++)
		{
			std::string sub = text.substr(i * maxTextLength, maxTextLength);
			g.DrawString(sub, this->m_Font, this->GetForeColor(), PointF(location.X, (location.Y + (lineHeight))));
			lineHeight += 14;
		}
	}
}
CustomLabel::CustomLabel()
{
	m_Font = FontManager::LoadFont("Tahoma", 8, false);
}
CustomLabel::~CustomLabel()
{
}