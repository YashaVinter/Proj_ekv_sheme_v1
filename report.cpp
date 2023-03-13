#pragma once
#include "functions.h"
#include <vector>
#include "Ekv.h"
#include "report.h"


//int Report::m_count = 0;

Report::Report()
{
	// data{};
	data.ekvGen.state = 0;
	data.ekvPos.state = 0;
	data.ekvPar.state = 0;
}



void Report::plusCount()
{
	Report::m_countCommon++;
}