#include "End.h"
#include <sstream>

using namespace std;

void End::UpdateStatementText()
{
	ostringstream T;
	T << "End";
	Text = T.str();
}

End::End(Point Lcorner):Statement(0, true)
{
	UpdateStatementText();

	LeftCorner = Lcorner;

	setOutlet();
	setIntlet();
}



void End::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawEnd(LeftCorner, UI.EL_WDTH, UI.EL_HI, Selected);

}

Point End::getLeftCorner() const
{
	return LeftCorner;
}

bool End::PointInStatement(Point position)
{
	if (position.x >= LeftCorner.x&&position.x <= LeftCorner.x + UI.EL_WDTH&&position.y >= LeftCorner.y&&position.y <= LeftCorner.y + UI.EL_HI){
		return true;
}
	return false;
}

void End::Save(ofstream & OutFile)
{
	OutFile << "END  " <<ID<<"  "<< LeftCorner.x+(0.5)*UI.EL_WDTH << "  " << LeftCorner.y << endl;
}

void End::Load(ifstream & Infile)
{
	Point P;
	Infile >>ID>>P.x >> P.y;
	 CenterToLeftCorner(P);
	 setOutlet();
	 setIntlet();

}

void End::CenterToLeftCorner(Point C)
{
	Point P;
	LeftCorner.x = C.x - (0.5)*UI.EL_WDTH;
	LeftCorner.y = C.y;
}

void End::setOutlet()
{
	Outlet.x = -1;
	Outlet.y = -1;
}

void End::setIntlet()
{
	Inlet.x = LeftCorner.x + UI.EL_WDTH / 2;
	Inlet.y = LeftCorner.y;
}

void End::SetDrawingPoint(Point P)
{
	LeftCorner = P;
	LeftCorner.x = P.x - UI.EL_WDTH / 2;
	LeftCorner.y = P.y;
	Inlet.x = LeftCorner.x + UI.EL_WDTH / 2;
	Inlet.y = LeftCorner.y - (0.07*UI.EL_HI);
}
Statement * End::Clone()
{
	Statement * Clone = new End(Point(0, 0));
	return Clone;
}

bool End::CheckVariables(string * &arr, int & c)
{
	return true;
}
bool End::Simulate(ApplicationManager *pManager)
{
	return true;
}
void End::Edit(ApplicationManager *pManager)
{
	return;
}
