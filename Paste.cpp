#include "Paste.h"
#include "Statements\Statement.h"
#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>



Paste::Paste(ApplicationManager * pManager)
	:Action(pManager)
{
}

void Paste::ReadActionParameters()
{
	Output * pOut = pManager->GetOutput();
	Input * pIn = pManager->GetInput();
	pOut->PrintMessage("Click anywhere to Paste the Statement");
	pIn->GetPointClicked(Position);

}

void Paste::Execute()
{
	if (pManager->GetClipboard())
	{
		ReadActionParameters();
		Statement * Clone = (pManager->GetClipboard())->Clone();
		Clone->SetDrawingPoint(Position);
		pManager->AddStatement(Clone);
	}
	else
	{
		Output * pOut = pManager->GetOutput();
		pOut->PrintMessage("No Statement in clipboard to paste ");
	}
}


Paste::~Paste()
{
}
