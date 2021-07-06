#include "Edit.h"
#include "Statements\Statement.h"
#include "GUI\input.h"
#include "GUI\Output.h"

Edit::Edit(ApplicationManager *pManager)
	:Action(pManager)
{
}

void Edit::ReadActionParameters()
{
}


void Edit::Execute()
{
	Statement * pStat = pManager->GetSelectedStatement();
	if (pStat != NULL)
	{
		pStat->Edit(pManager);
		pStat->SetSelected(false);
		pManager->SetSelectedStatement(NULL);
		return;
	}
	else
	{
		Output *pOut = pManager->GetOutput();
		pOut->PrintMessage("No Statement selected to Edit");
	}
}

Edit::~Edit()
{
}
