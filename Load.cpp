#include"Load.h"
#include"Start.h"
#include"End.h"
#include"Conditional.h"
#include"VariableAssign.h"
#include"OperatorAssign.h"
#include"Statements\ValueAssign.h"
#include"Write.h"
#include"Read.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include <sstream>
using namespace std;

Load::Load(ApplicationManager * pAppManager) :Action(pAppManager)
{}

void Load::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Enter File Name");
	FileName = pIn->GetString(pOut);
	pOut->ClearStatusBar();
}

void Load::Execute()
{
	ReadActionParameters();
	ifstream inputFile;
	inputFile.open(FileName, ios::in);
	if (inputFile.is_open()) {
		Output * pOut = pManager->GetOutput();
		pOut->ClearDrawArea();
		pManager->EmptyAllLists();
		int x;
		inputFile >> x;
		for (int i = 0; i < x; i++) {
			string S;
			inputFile >> S;
			Point P;
			if (S == "START") {
				Start*stat = new Start(P);
				stat->Load(inputFile);
				pManager->AddStatement(stat);
				continue;
			}
			else if (S == "END") {
				End*stat = new End(P);
				stat->Load(inputFile);
				pManager->AddStatement(stat);
				continue;
			}
			else if (S == "VALUE_ASSIGN") {
				ValueAssign *stat = new ValueAssign(P);
				stat->Load(inputFile);
				pManager->AddStatement(stat);
				continue;
			}
			else if (S == "VRBL_ASSIGN") {
				VariableAssign *stat = new VariableAssign(P);
				stat->Load(inputFile);
				pManager->AddStatement(stat);
				continue;
			}
			else if (S == "COND") {
				Conditional*stat = new Conditional(P);
				stat->Load(inputFile);
				pManager->AddStatement(stat);
				continue;
			}
			else if (S == "READ") {
				Read*stat = new Read(P);
				stat->Load(inputFile);
				pManager->AddStatement(stat);
				continue;
			}
			else if (S == "WRITE") {
				Write*stat = new Write(P);
				stat->Load(inputFile);
				pManager->AddStatement(stat);
				continue;
			}
			else if (S == "OP_ASSIGN") {
				OperatorAssign*stat = new OperatorAssign(P);
				stat->Load(inputFile);
				pManager->AddStatement(stat);
				continue;
			}
			
		}
		inputFile >> x;
		for (int i = 0; i < x; i++) {
			int ID1, ID2;
			Connector*C = new Connector(NULL, NULL, 0);
			C->Load(inputFile, ID1, ID2);
			if (pManager->GetStatementFromID(ID1)) {
				C->setSrcStat(pManager->GetStatementFromID(ID1));
			}
			else {
				delete C;
				continue;
			}
			if (pManager->GetStatementFromID(ID2)) {
				C->setDstStat(pManager->GetStatementFromID(ID2));
			}
			else {
				delete C;
				continue;
			}
			C->setStartAndEnd();
			if (C->getDstStat() && C->getSrcStat()) {
				if (C->getCase() == 0 || C->getCase() == 2) {
					C->getSrcStat()->setConnector(C);
				}
				else {
					C->getSrcStat()->setConnector(C, 1);
				}
				C->getDstStat()->SetIsInConnected(true);
				C->getSrcStat()->AddActual();//!!!!!!!!!!!
				pManager->AddConnector(C);
			}
		}

	}

}