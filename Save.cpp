#include"Save.h"


#include "GUI\input.h"
#include "GUI\Output.h"
#include <sstream>
using namespace std;

Save::Save(ApplicationManager * pAppManager) :Action(pAppManager)
{}

void Save::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Enter File Name");
	FileName=pIn->GetString(pOut);
}

void Save::Execute()
{
	ReadActionParameters();
	ofstream OutputFile;
	OutputFile.open(FileName, ios::out);
	pManager->SaveAll(OutputFile);
	OutputFile.close();
}