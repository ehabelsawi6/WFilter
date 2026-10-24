#pragma once

#pragma once

#include "CNIFWnd.h"
#include "CNIFGauge.h"
#include "CNIFStatic.h"

class CNIFUnderMenuBar : public CNIFWnd {
	// 1192 - 840 = 352
public:
	char padx[8];

	CNIFGauge* gauge_skillexp; // 350
	CNIFStatic* lbl_percentage; // 354
	CNIFStatic* lbl_spcount; // 358
	CNIFStatic* lbl_exp_bar_scaler; // 35C
	CNIFStatic* lbl_360; // 360
	CNIFStatic* lbl_percent_bar; // 364 
	CNIFStatic* lbl_level; // 368 
	CNIFGauge* gauges[10]; // 36C

	char pad_cnifundermenubar[352 - 36 - (10 * 4)];


	void Update();
};

