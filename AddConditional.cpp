#include "AddConditional.h"



#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddConditional::AddConditional(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddConditional::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Conditional Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter The LHS parameter");
	LHS = pIn->GetString(pOut);
	int x = ValueOrVariable(LHS);
	while (x == 2) {
		pOut->PrintMessage("Please enter a valid LHS parameter");
		LHS = pIn->GetString(pOut);
		x = ValueOrVariable(LHS);
	}

	pOut->PrintMessage("Please enter an arithmetic comparator");
	Comparator=pIn->GetCompOperator(pOut);

	if (x == 0) {
		pOut->PrintMessage("Please enter the RHS parameter (variable)");
		RHS=pIn->GetVariable(pOut);
	}
	else {
		pOut->PrintMessage("Please enter the RHS parameter");
		RHS = pIn->GetString(pOut);
		x = ValueOrVariable(RHS);
		while (x == 2) {
			pOut->PrintMessage("Please enter a valid RHS parameter");
			RHS = pIn->GetString(pOut);
			x = ValueOrVariable(RHS);
		}
	}
	



	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddConditional::Execute()
{
	ReadActionParameters();
	if (Position.x > 0 && Position.x <= UI.DrawingAreaWidth&&Position.y >= UI.ToolBarHeight&&Position.y <= UI.height - 50) {
		//Calculating left corner of assignement statement block
		Point Corner;
		Corner.x = Position.x - UI.CON_WDTH / 2;
		Corner.y = Position.y + UI.CON_HI / 2;

		Conditional *pAssign = new Conditional(Corner, "", "", Comparator);
		//TODO: should set the LHS and RHS of pAssign statement
		//      with the data members set and validated before in ReadActionParameters()
		pAssign->setLHS(LHS);
		pAssign->setRHS(RHS);


		pManager->AddStatement(pAssign);
	}
	else {
		Output *pOut = pManager->GetOutput();
		pOut->PrintMessage("Can't Draw Outside Drawing Area");
	}			 // Adds the created statement to application manger's statement list
}