#include "Copy.h"
#include "Statements\Statement.h"
#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>


Copy::Copy(ApplicationManager *pManager)
	:Action(pManager)
{
}

void Copy::ReadActionParameters()
{
	return;
}

void Copy::Execute()
{
	Statement * StatToCopy = pManager->GetSelectedStatement();
	if (StatToCopy != NULL)
	{
		Statement * Clone = StatToCopy->Clone();
		Statement * Clip = pManager->GetClipboard();
		if (Clip != NULL)
		{
			delete Clip;
		}
		pManager->SetClipboard(Clone);
		pManager->SetSelectedStatement( NULL);
		StatToCopy->SetSelected(false);
	}
	else
	{
		Output * pOut = pManager->GetOutput();
		pOut->PrintMessage("No Statement selected to be copied");
	}
}


Copy::~Copy()
{
}
