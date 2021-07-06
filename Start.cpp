#include "Start.h"
#include <sstream>

using namespace std;

void Start::UpdateStatementText()
{
	ostringstream T;
	T << "Start";
	Text = T.str();
}

Start::Start(Point Lcorner):Statement(1, false)
{
	UpdateStatementText();

	LeftCorner = Lcorner;

	//No connectors yet

	setOutlet();
	setIntlet();
}



void Start::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawStart(LeftCorner, UI.EL_WDTH, UI.EL_HI,Selected);

}

Point Start::getLeftCorner() const
{
	return LeftCorner;
}

bool Start::PointInStatement(Point position)
{
	if (position.x >= LeftCorner.x&&position.x <= LeftCorner.x + UI.EL_WDTH&&position.y >= LeftCorner.y&&position.y <= LeftCorner.y + UI.EL_HI) {
		return true;
	}
	return false;
}

void Start::Save(ofstream & OutFile)
{
	OutFile << "START  " << ID << "  " << LeftCorner.x + (0.5)*UI.EL_WDTH <<"  "<<LeftCorner.y << endl;
}

void Start::Load(ifstream & Infile)
{
	Point P;
	Infile >> ID >> P.x >> P.y;
	CenterToLeftCorner(P);
	setOutlet();
	setIntlet();
}

void Start::CenterToLeftCorner(Point C)
{
	Point P;
	LeftCorner.x = C.x - (0.5)*UI.EL_WDTH;
	LeftCorner.y = C.y;
}

void Start::setOutlet()
{
	Outlet.x = LeftCorner.x + UI.EL_WDTH / 2;
	Outlet.y = LeftCorner.y + UI.EL_HI;

}

void Start::setIntlet()
{
	Inlet.x = -1;
	Inlet.y = -1;
}

void Start::SetDrawingPoint(Point P)
{
	LeftCorner = P;

	LeftCorner.x = P.x - UI.EL_WDTH / 2;
	LeftCorner.y = P.y;
	Outlet.x = LeftCorner.x + UI.EL_WDTH / 2;
	Outlet.y = LeftCorner.y + (1.07*UI.EL_HI);
}
Statement * Start::Clone()
{
	Statement * Clone = new Start(Point(0, 0));
	return Clone;
}

bool Start::CheckVariables(string * &arr, int & c)
{
	return false;
}

bool Start::Simulate(ApplicationManager *pManager)
{
	return false;
}

void Start::Edit(ApplicationManager *pManager)
{
	return;
}