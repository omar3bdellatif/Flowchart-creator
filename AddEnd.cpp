#include "AddEnd.h"



#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddEnd::AddEnd(ApplicationManager *pAppManager) :Action(pAppManager)
{}

void AddEnd::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("End Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

}

void AddEnd::Execute()
{
	//Calculating left corner of assignement statement block
	ReadActionParameters();
	if (Position.x > 0 && Position.x <= UI.DrawingAreaWidth&&Position.y >= UI.ToolBarHeight&&Position.y <= UI.height - 50) {
		Point Corner;
		Corner.x = Position.x - UI.EL_WDTH / 2;
		Corner.y = Position.y;

		End *pAssign = new End(Corner);
		//TODO: should set the LHS and RHS of pAssign statement
		//      with the data members set and validated before in ReadActionParameters()


		pManager->AddStatement(pAssign);
	}
	else {
		Output *pOut = pManager->GetOutput();
		pOut->PrintMessage("Can't Draw Outside Drawing Area");
	}// Adds the created statement to application manger's statement list
}