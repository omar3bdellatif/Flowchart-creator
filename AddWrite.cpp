#include "AddWrite.h"



#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddWrite::AddWrite(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddWrite::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Write Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter the variable or the message to be written ");
	Variable = pIn->GetString(pOut);
	while (!IsVariable(Variable) && (Variable[0] != '"' || Variable[Variable.length()-1] != '"')) {
		pOut->PrintMessage("Please enter a valid variable or a valid message to be written ");
		Variable = pIn->GetString(pOut);
	}



	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddWrite::Execute()
{
	ReadActionParameters();


	//Calculating left corner of assignement statement block
	if (Position.x > 0 && Position.x <= UI.DrawingAreaWidth&&Position.y >= UI.ToolBarHeight&&Position.y <= UI.height - 50) {
		Point Corner;
		Corner.x = Position.x - UI.PG_WDTH / 2;
		Corner.y = Position.y;

		Write *pAssign = new Write(Corner, "");
		//TODO: should set the LHS and RHS of pAssign statement
		//      with the data members set and validated before in ReadActionParameters()
		pAssign->setVariable(Variable);

		pManager->AddStatement(pAssign);
	} // Adds the created statement to application manger's statement list
	else {
		Output *pOut=pManager->GetOutput();
		pOut->PrintMessage("Can't Draw Outside Drawing Area");
	}
}