#include "Write.h"
#include <sstream>

using namespace std;


Write::Write(Point Lcorner, string rVariable):Statement(1, true)
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

void Write::setVariable(const string &rVariable)
{
	Variable = rVariable;
	UpdateStatementText();
}

void Write::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawIOStat(LeftCorner, UI.PG_WDTH, UI.PG_HI, Text, Selected);

}

Point Write::getLeftCorner() const
{
	return LeftCorner;
}

bool Write::PointInStatement(Point position)
{
	if (position.x >= LeftCorner.x&&position.x <= LeftCorner.x + (1.1)*UI.PG_WDTH&&position.y >= LeftCorner.y&&position.y <= LeftCorner.y + UI.PG_HI) {
		return true;
	}
	return false;
}

void Write::Save(ofstream & OutFile)
{
	OutFile << "WRITE  " << ID << "  " << LeftCorner.x << "  " << LeftCorner.y << "  " << Variable << endl;
}

void Write::Load(ifstream & Infile)
{
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> Variable;
	setOutlet();
	setIntlet();
	UpdateStatementText();
}

void Write::setOutlet()
{
	Outlet.x = LeftCorner.x + UI.PG_WDTH / 2;
	Outlet.y = LeftCorner.y + UI.PG_HI;
}

void Write::setIntlet()
{
	Inlet.x = LeftCorner.x + UI.PG_WDTH / 2;
	Inlet.y = LeftCorner.y;

}



//This function should be called when LHS or RHS changes
void Write::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << "Write " << Variable;
	Text = T.str();
}

void Write::SetDrawingPoint(Point P)
{
	LeftCorner = P;
	LeftCorner.x = P.x - UI.PG_WDTH / 2;
	LeftCorner.y = P.y;
	Inlet.x = LeftCorner.x + UI.PG_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.PG_HI;
}


Statement * Write::Clone()
{
	Statement* Clone = new Write(Point(0, 0), ((Write*)this)->Variable);
	return Clone;
}


bool Write::CheckVariables(string * &arr, int &c)
{
	if (Variable[0] == '"')
		return true;
	else
	{
		if (c == 0)
		{
			return false;
		}
		for (int i = 0; i < c; i++)
		{
			if (Variable == arr[i])
				return true;
		}
	}
	return false;
}


bool Write::Simulate(ApplicationManager *pManager)
{
	static int y = UI.ToolBarHeight + 10;
	Input * pIn = pManager->GetInput();
	Output * pOut = pManager->GetOutput();
	string Var;
	int x;
	x = UI.DrawingAreaWidth + ((UI.width - UI.DrawingAreaWidth) / 2);

	if (Variable[0] != '"')
	{
		Var = Variable + " = " + to_string(pManager->ReturnValue(Variable));
		pOut->DrawString(x, y, Var);
	}
	else
	{
		pOut->DrawString(x, y, Variable);
	}
	y += 10;
	return true;
}
void Write::Edit(ApplicationManager *pManager)
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	Point Position;
	//Read the (Position) parameter
	pOut->PrintMessage("Write Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter the variable or the message to be written ");
	Variable = pIn->GetString(pOut);
	while (!IsVariable(Variable) && (Variable[0] != '"' || Variable[Variable.length() - 1] != '"')) {
		pOut->PrintMessage("Please enter a valid variable or a valid message to be written ");
		Variable = pIn->GetString(pOut);
	}
	setVariable(Variable);
	UpdateStatementText();
}
