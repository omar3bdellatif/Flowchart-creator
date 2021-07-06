#include "AddValueAssign.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddValueAssign::AddValueAssign(ApplicationManager *pAppManager):Action(pAppManager)
{}

void AddValueAssign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	//Read the (Position) parameter
	pOut->PrintMessage("Value Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();		

	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter The LHS parameter");
	LHS=pIn->GetVariable(pOut);

	//TODO: Ask the user in the status bar to enter the RHS and set the data member
	pOut->PrintMessage("Please enter The RHS value");
	RHS = pIn->GetValue(pOut);

	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddValueAssign::Execute()
{
	ReadActionParameters();
		
	
	//Calculating left corner of assignement statement block
	if (Position.x > 0 && Position.x <= UI.DrawingAreaWidth&&Position.y >= UI.ToolBarHeight&&Position.y <= UI.height - 50) {
		Point Corner;
		Corner.x = Position.x - UI.ASSGN_WDTH / 2;
		Corner.y = Position.y;

		ValueAssign *pAssign = new ValueAssign(Corner, "", 0);
		//TODO: should set the LHS and RHS of pAssign statement
		//      with the data members set and validated before in ReadActionParameters()
		pAssign->setLHS(LHS);
		pAssign->setRHS(RHS);

		pManager->AddStatement(pAssign);
	}
	else {
		Output *pOut = pManager->GetOutput();
		pOut->PrintMessage("Can't Draw Outside Drawing Area");
	}// Adds the created statement to application manger's statement list
}

