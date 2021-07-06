#include "AddOperatorAssign.h"



#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddOperatorAssign::AddOperatorAssign(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddOperatorAssign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Operator Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter The LHS parameter");
	LHS = pIn->GetVariable(pOut);

	//TODO: Ask the user in the status bar to enter the RHS and set the data member
	pOut->PrintMessage("Please enter The RHS parameter,click anywhere to continue");
	Point P;
	pIn->GetPointClicked(P);
	pOut->PrintMessage("Please enter the parameter to the left of the arithmetic operator");
	string temp1;
	RHS1 = pIn->GetString(pOut);
	while (ValueOrVariable(RHS1) ==2) {
		pOut->PrintMessage("Please enter a valid parameter to the right of the arithmetic operator");
		RHS1 = pIn->GetString(pOut);
	}
	pOut->PrintMessage("Please enter an arithmetic operator");
	int x=pIn->GetArithOperator(pOut);
	string temp;
	if (x == 0) {
		arithmeticoperator = '+';
	}
	else if (x == 1) {
		arithmeticoperator = '-';
	}
	else if (x == 2) {
		arithmeticoperator = '*';
	}
	else {
		arithmeticoperator = '/';
	}

	pOut->PrintMessage("Please enter the parameter to the right of the arithmetic operator");
	string temp2;
	RHS3 = pIn->GetString(pOut);
	while (ValueOrVariable(RHS3) != 0 && ValueOrVariable(RHS3) != 1) {
		pOut->PrintMessage("Please enter a valid parameter to the right of the arithmetic operator");
		RHS3 = pIn->GetString(pOut);
	}
	RHS = temp1 + temp + temp2;


	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddOperatorAssign::Execute()
{
	ReadActionParameters();


	//Calculating left corner of assignement statement block
	if (Position.x > 0 && Position.x <= UI.DrawingAreaWidth&&Position.y >= UI.ToolBarHeight&&Position.y <= UI.height - 50) {
		Point Corner;
		Corner.x = Position.x - UI.ASSGN_WDTH / 2;
		Corner.y = Position.y;

		OperatorAssign *pAssign = new OperatorAssign(Corner, "", "");
		//TODO: should set the LHS and RHS of pAssign statement
		//      with the data members set and validated before in ReadActionParameters()
		pAssign->setLHS(LHS);
		pAssign->setRHS1(RHS1);
		pAssign->setOperator(arithmeticoperator);
		pAssign->setRHS3(RHS3);

		pManager->AddStatement(pAssign);
	}
	else {
		Output *pOut = pManager->GetOutput();
		pOut->PrintMessage("Can't Draw Outside Drawing Area");
	}// Adds the created statement to application manger's statement list
}