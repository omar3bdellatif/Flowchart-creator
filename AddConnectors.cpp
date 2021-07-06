#include "AddConnectors.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include <sstream>
using namespace std;

AddConnectors::AddConnectors(ApplicationManager * pAppManager) :Action(pAppManager)
{}

void AddConnectors::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Choose the source statement");
	pIn->GetPointClicked(Position);
	Src=pManager->GetStatement(Position);
	if (Src) {
		if (Src->GetMaxOutConn() == 2) {
			pOut->PrintMessage("Input '1' if you want to use the right connector or '2' if you want to use the left connector,Click to continue");
			Point P;
			pIn->GetPointClicked(P);
			int x = pIn->GetValue(pOut);
			while (x != 1 && x != 2) {
				pOut->PrintMessage("Please enter a correct value");
				x=pIn->GetValue(pOut);
			}
			Case = x;
		}
		else {
			Case = 0;
		}
	}
	pOut->ClearStatusBar();
	pOut->PrintMessage("Choose the destination statement");
	pIn->GetPointClicked(Position);
	Dest = pManager->GetStatement(Position);
}

void AddConnectors::Execute()
{
	Output*pOut = pManager->GetOutput();	Input *pIn = pManager->GetInput();

	ReadActionParameters();
	pOut->ClearStatusBar();
	if (!Src || !Dest) {
		pOut->PrintMessage("No Source and/or No Destination statements");

		return;
	}
	if (Src == Dest) {
		pOut->PrintMessage("Can't connect a statement to itself");
		return;
	}
	
	if (Src->GetMaxOutConn()==0) {
	
		pOut->PrintMessage("Can't draw a connector from End statements");
	
		return;
	}
	if (!Dest->CanBeConnected()) {

		pOut->PrintMessage("Can't draw a connector to Start statements");

		return;
	}
	if (Case == 0||Case==2) {
		if (Src->GetConnecter(0)) {

			pOut->PrintMessage("Statement already has an Output connector,please delete it first");

			return;
		}
	}
	if (Case == 1) {
		if (Src->GetConnecter(1)) {

			pOut->PrintMessage("Statement already has an Output connector,please delete it first");
	
			return;
		}
	}



	Connector*C = new Connector(Src,Dest,Case);
	if(Case == 0 || Case == 2) {
		Src->setConnector(C);
	}
	else {
		Src->setConnector(C, 1);
	}
	Dest->SetIsInConnected(true);
	Src->AddActual();//!!!!!!!!!!!
	pManager->AddConnector(C);
}
