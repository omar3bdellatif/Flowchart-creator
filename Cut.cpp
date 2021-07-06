#include "Cut.h"
#include "Statements\Statement.h"
#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>


Cut::Cut(ApplicationManager * pManager)
	:Remove(pManager)
{

}

void Cut::ReadActionParameters()
{
	return;
}

void Cut::Execute()
{
	Statement * StatToCut = pManager->GetSelectedStatement();
	if (pManager->GetSelectedStatement())
	{

		Statement * Clip = pManager->GetClipboard();
		if (Clip != NULL)
		{
			delete Clip;
		}
		pManager->SetClipboard(pManager->GetSelectedStatement());
		Remove::Execute();
		return;
	}
	Output * pOut = pManager->GetOutput();
	pOut->PrintMessage("No Statement selected to be Cut ");
}


Cut::~Cut()
{
}
