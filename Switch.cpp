#include "Switch.h"



Switch::Switch(ApplicationManager * P)
	:Action(P)
{
}

void Switch::ReadActionParameters()
{
}


void Switch::Execute()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	if (UI.AppMode == DESIGN)
	{
		pOut->CreateSimulationToolBar();
	}
	else
	{
		pOut->CreateDesignToolBar();
	}
}

Switch::~Switch()
{
}
