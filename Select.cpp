#include "Select.h"


#include "GUI\input.h"
#include "GUI\Output.h"
#include <sstream>
using namespace std;

Select::Select(ApplicationManager * pAppManager):Action(pAppManager)
{}

void Select::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Select/Unselect Statement: Choose which statement you want to select");
	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();
}

void Select::Execute()
{
	ReadActionParameters();
	Statement*Test=pManager->GetStatement(Position);
	if (Test) {
		if (Test->IsSelected()) {
			Test->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
			return;
		}
		else {
			Test->SetSelected(true);
			if (pManager->GetSelectedStatement()) {
				pManager->GetSelectedStatement()->SetSelected(false);
				pManager->SetSelectedStatement(NULL);
			}
			else if (pManager->GetSelectedConnector()) {
				pManager->GetSelectedConnector()->setSelected(false);
				pManager->SetSelectedConnector(NULL);
			}
			pManager->SetSelectedStatement(Test);
			return;
		}
	}
	Connector*Test2 = pManager->GetConnector(Position);
	if (Test2) {
		if (Test2->IsSelected()) {
			Test2->setSelected(false);
			pManager->SetSelectedConnector(NULL);
			return;
		}
		else {
			Test2->setSelected(true);
			if (pManager->GetSelectedStatement()) {
				pManager->GetSelectedStatement()->SetSelected(false);
				pManager->SetSelectedStatement(NULL);
			}
			else if (pManager->GetSelectedConnector()) {
				pManager->GetSelectedConnector()->setSelected(false);
				pManager->SetSelectedConnector(NULL);
			}
			pManager->SetSelectedConnector(Test2);
			return;
		}
	}
}
