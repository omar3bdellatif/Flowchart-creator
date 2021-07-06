#include "Read.h"
#include <sstream>

using namespace std;


Read::Read(Point Lcorner, string rVariable ):Statement(1, true)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
	Variable = rVariable;

	UpdateStatementText();

	LeftCorner = Lcorner;

	//No connectors yet

	setOutlet();
	setIntlet();
}

void Read::setVariable(const string &rVariable)
{
	Variable = rVariable;
	UpdateStatementText();
}

void Read::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawIOStat(LeftCorner, UI.PG_WDTH, UI.PG_HI, Text, Selected);

}

Point Read::getLeftCorner() const
{
	return LeftCorner;
}

bool Read::PointInStatement(Point position)
{
	if (position.x >= LeftCorner.x&&position.x <= LeftCorner.x + (1.1)*UI.PG_WDTH&&position.y >= LeftCorner.y&&position.y <= LeftCorner.y + UI.PG_HI) {
		return true;
	}
	return false;
}

void Read::Save(ofstream & OutFile)
{
	OutFile << "READ" << "  " << ID << "  " << LeftCorner.x << "  " << LeftCorner.y << "  " << Variable << endl;
}

void Read::Load(ifstream & Infile)
{
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> Variable;
	setOutlet();
	setIntlet();
	UpdateStatementText();
}

void Read::setOutlet()
{

	Outlet.x = LeftCorner.x + UI.PG_WDTH / 2;
	Outlet.y = LeftCorner.y + UI.PG_HI;
}

void Read::setIntlet()
{
	Inlet.x = LeftCorner.x + UI.PG_WDTH / 2;
	Inlet.y = LeftCorner.y;
}


//This function should be called when LHS or RHS changes
void Read::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << "Read " << Variable;
	Text = T.str();
}

void Read::SetDrawingPoint(Point P)
{
	LeftCorner = P;
	LeftCorner.x = P.x - UI.PG_WDTH / 2;
	LeftCorner.y = P.y;
	Inlet.x = LeftCorner.x + UI.PG_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.PG_HI;
}
Statement * Read::Clone()
{
	Statement* Clone = new Read(Point(0, 0), ((Read*)this)->Variable);
	return Clone;
}

bool Read::CheckVariables(string * &arr, int & c)
{
	if (c == 0)
	{
		arr[0] = Variable;
		c++;
		return true;
	}
	for (int i = 0; i < c; i++)
	{
		if (arr[i] == Variable)
		{
			return true;
		}
	}
	string * temp = new string[c + 1];
	for (int i = 0; i < c; i++)
	{
		temp[i] = arr[i];
	}
	delete[] arr;
	arr = temp;
	arr[c] = Variable;
	c++;
	return true;
}


bool Read::Simulate(ApplicationManager * pManager)
{
	Input * pIn = pManager->GetInput();
	Output * pOut = pManager->GetOutput();
	double V = pIn->GetValue(pOut);

	pManager->AddIntVariable(Variable, V);
	return true;
}

void Read::Edit(ApplicationManager *pManager)
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	Point Position;
	//Read the (Position) parameter
	pOut->PrintMessage("Read Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter The variable to be read");
	Variable = pIn->GetVariable(pOut);
	UpdateStatementText();
}
