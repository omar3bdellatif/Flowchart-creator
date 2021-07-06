#include "Connector.h"
#include"Conditional.h"
#include"GUI\Output.h"



Connector::Connector(Statement* Src, Statement* Dst,int rCase)	
//When a connector is created, it must have a source statement and a destination statement
//There are NO FREE connectors in the flowchart
{
	Case = rCase;
	SrcStat = Src;
	DstStat = Dst;
	Selected = false;
	Point P;
	P.x = 0; P.y = 0;
	setStartAndEnd();
	
}

void Connector::setSrcStat(Statement *Src)
{	SrcStat = Src;	}

Statement* Connector::getSrcStat()const
{	return SrcStat;	}

void Connector::setDstStat(Statement *Dst)
{	DstStat = Dst;	}

Statement* Connector::getDstStat()
{	return DstStat;	}




void Connector::setStartAndEnd()
{
	if (Case == 2) {
		setStartPoint(((Conditional*)SrcStat)->getFalseOutlet());
	}
	else {

		setStartPoint(SrcStat->getOutlet());
	}
	setEndPoint(DstStat->getInlet());
}

void Connector::setStartPoint(Point P)
{	Start = P;	}

Point Connector::getStartPoint()
{	return Start;	}

void Connector::setEndPoint(Point P)
{	End = P;	}

Point Connector::getEndPoint()
{	return End;	}

void Connector::Draw(Output* pOut) const
{	
	pOut->DrawConnector(Start, End, Selected, Case);

}

void Connector::setSelected(bool rSelected)
{
	Selected = rSelected;
}

bool Connector::IsSelected() const
{
	return Selected;
}

bool Connector::isInConnector(Point P)
{
	if (Case == 0) {
		if (Start.x == End.x&&End.y > Start.y) {
			if (P.x <= Start.x+2&& P.x >= Start.x-2) {
				if (P.y >= Start.y&&P.y <= End.y)
					return true;
			}
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;
		}
		if ((Start.x < End.x&&Start.y + 5 < End.y)) {
			if (P.x <= Start.x+2&& P.x >= Start.x - 2) {
				if (P.y >= Start.y&&P.y <= Start.y + 5)
					return true;
			}
			if (P.y <= Start.y + 7&& P.y >= Start.y + 3) {
				if (P.x >= Start.x&&P.x <= End.x) {
					return true;
				}
			}
			if (P.x <= End.x+2&& P.x >= End.x - 2) {
				if (P.y >= Start.y&&P.y <= End.y)
					return true;
			}
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;;
		}
		if ((Start.x > End.x&&Start.y + 5 < End.y)) {
			if (P.x <= Start.x + 2 && P.x >= Start.x - 2) {
				if (P.y >= Start.y&&P.y <= Start.y + 5)
					return true;
			}
			if (P.y <= Start.y + 7 && P.y >= Start.y + 3) {
				if (P.x <= Start.x&&P.x >= End.x) {
					return true;
				}
			}
			if (P.x <= End.x + 2 && P.x >= End.x - 2) {
				if (P.y >= Start.y&&P.y <= End.y)
					return true;
			}
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;;

		}
		if ((End.x > Start.x&&Start.y + 5 >= End.y&&End.x > (Start.x + UI.ASSGN_WDTH))) {
			if (P.x <= Start.x+2&& P.x >= Start.x - 2) {
				if (P.y >= Start.y&&P.y <= Start.y + 5)
					return true;
			}
			if (P.y <= Start.y + 7&& P.y >= Start.y + 3) {
				if (P.x >= Start.x&&P.x <= End.x - (0.5)*UI.ASSGN_WDTH)
					return true;
			}
			if (P.x <= End.x - (0.5)*UI.ASSGN_WDTH+2&& P.x >= End.x - (0.5)*UI.ASSGN_WDTH - 2) {
				if (P.y <= Start.y + 5 && P.y >= End.y - 5)
					return true;
			}
			if (P.y <= End.y - 3&& P.y >= End.y - 7) {
				if (P.x >= End.x - (0.5)*UI.ASSGN_WDTH&&P.x <= End.x)
					return true;
			}
			if (P.x <= End.x+2&& P.x >= End.x-2) {
				if (P.y >= End.y - 5 && P.y <= End.y)
					return true;
			}
			//draw triangle,also you might want to test that 5 value
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;
		}
		if (End.x < Start.x&&End.x < Start.x - UI.ASSGN_WDTH&&Start.y + 5 >= End.y) {
			if (P.x <= Start.x+2&& P.x >= Start.x-2) {
				if (P.y >= Start.y&&P.y <= Start.y + 5)
					return true;
			}
			if (P.y <= Start.y + 7&& P.y >= Start.y + 3) {
				if (P.x <= Start.x&&P.x >= End.x + (0.5)*UI.ASSGN_WDTH)
					return true;
			}
			if (P.x <= End.x + (0.5)*UI.ASSGN_WDTH+2&& P.x >= End.x + (0.5)*UI.ASSGN_WDTH - 2) {
				if (P.y <= Start.y + 5 && P.y >= End.y - 5)
					return true;
			}
			if (P.y <= End.y - 3&& P.y >= End.y - 7) {
				if (P.x <= End.x + (0.5)*UI.ASSGN_WDTH&&P.x >= End.x)
					return true;
			}
			if (P.x <= End.x+2&& P.x >= End.x-2) {
				if (P.y >= End.y - 5 && P.y <= End.y)
					return true;
			}
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;;
		}
		if (End.x == Start.x&&End.y < Start.y) {

			if (P.x <= Start.x+2&& P.x >= Start.x-2) {
				if (P.y >= Start.y&&P.y <= Start.y + 5)
					return true;
			}
			if (P.y <= Start.y + 7&&P.y >= Start.y + 3) {
				if (P.x >= Start.x&&P.x <= Start.x + (0.75)*UI.ASSGN_WDTH)
					return true;
			}
			if (P.x <= Start.x + (0.75)*UI.ASSGN_WDTH+2&& P.x >= Start.x + (0.75)*UI.ASSGN_WDTH - 2) {
				if (P.y < Start.y + 5 && P.y >= End.y - 5) {
					return true;
				}
			}
			if (P.y <= End.y - 3&&P.y>=End.y-7) {
				if (P.x <= Start.x + (0.75)*UI.ASSGN_WDTH&&P.x >= End.x)
					return true;
			}
			if (P.x <= End.x+2&&P.x>=End.x-2) {
				if (P.y <= End.y&&P.y >= End.y - 5)
					return true;
			}
			//triangle,5
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;
		}
		if (End.x > Start.x&&End.x <= Start.x + UI.ASSGN_WDTH&&End.y <= Start.y + 5) {
			if (P.x <= Start.x+2&& P.x >= Start.x - 2) {
				if (P.y >= Start.y&&P.y <= Start.y + (1.25)*UI.ASSGN_HI)
					return true;
			}
			if (P.y <= Start.y + (1.25)*UI.ASSGN_HI+2&& P.y >= Start.y + (1.25)*UI.ASSGN_HI - 2)
				if (P.x >= Start.x&&P.x <= End.x + (0.5)*UI.ASSGN_WDTH)
					return true;
			if (P.x <= End.x + (0.5)*UI.ASSGN_WDTH+2&& P.x >= End.x + (0.5)*UI.ASSGN_WDTH - 2) {
				if (P.y <= Start.y + (1.25)*UI.ASSGN_HI&&P.y >= End.y - 5)
					return true;
			}
			if (P.y <= End.y - 3&& P.y >= End.y - 7) {
				if (P.x <= End.x + (0.5)*UI.ASSGN_WDTH&&P.x >= End.x)
					return true;
			}
			if (P.x <= End.x+2&& P.x >= End.x - 2) {
				if (P.y >= End.y - 5 && P.y <= End.y)
					return true;
			}
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;
		}
		if (End.x < Start.x&&End.x >= Start.x - UI.ASSGN_WDTH&&End.y <= Start.y + 5) {
			if (P.x <= Start.x+2&& P.x >= Start.x - 2) {
				if (P.y >= Start.y&&P.y <= Start.y + (1.25)*UI.ASSGN_HI)
					return true;
			}
			if (P.y <= Start.y + (1.25)*UI.ASSGN_HI+2&& P.y >= Start.y + (1.25)*UI.ASSGN_HI - 2) {
				if (P.x <= Start.x&&P.x >= End.x - (0.5)*UI.ASSGN_WDTH)
					return true;
			}
			if (P.x <= End.x - (0.5)*UI.ASSGN_WDTH+2&&P.y>= End.x - (0.5)*UI.ASSGN_WDTH-2) {
				if (P.y <= Start.y + (1.25)*UI.ASSGN_HI&&P.y >= End.y - 5)
					return true;
			}
			if (P.y <= End.y - 3&& P.y >= End.y - 7) {
				if (P.x >= End.x - (0.5)*UI.ASSGN_WDTH&&P.x <= End.x)
					return true;
			}
			if (P.x <= End.x+2&& P.x >= End.x - 2) {
				if (P.y >= End.y - 5 && P.y <= End.y - 5)
					return true;
			}
			//triangle
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;
		}
		double X, Y;
		if (GetSlope(P, Start, X) && GetSlope(P, End, Y)) {
			if (X == (-1 * Y)) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (!GetSlope(P, Start, X)&&!GetSlope(P,End,Y)) {
			return true;
		}
		else if ((Start.x == P.x&&Start.y == P.y) || (End.x == P.x&&End.y == P.y)) {
			return true;
		}
		else {
			return false;
		}
	}

		
	else if (Case == 1) {
		if (End.x<Start.x&&End.x >= Start.x - UI.CON_WDTH&&End.y>Start.y) {
			if (P.x <= Start.x+2&& P.x >= Start.x-2) {
				if (P.y >= Start.y&&P.y <= End.y - 5)
					return true;
			}
			if (P.y <= End.y - 3&&P.y>=End.y-7) {
				if (P.x <= Start.x&&P.x >= End.x)
					return true;
			}
			if (P.x <= End.x+2&&P.x>=End.x-2) {
				if (P.y >= End.y - 5 && P.y <= End.y)
					return true;
			}
			//triangle
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;
		}
		if (Start.x == End.x&&End.y > Start.y) {
			if (P.x <= Start.x+2&&P.x>=Start.x-2) {
				if (P.y >= Start.y&&P.y <= End.y)
					return true;
			}
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;
		}
		if (Start.x < End.x&&End.y > Start.y) {
			if (P.y <= Start.y+2&&P.y>=Start.y-2) {
				if (P.x >= Start.x&&P.x <= End.x)
					return true;
			}
			if (P.x <= End.x+2&&P.x>=End.x-2) {
				if (P.y >= Start.y&&P.y <= End.y)
					return true;
			}
			//triangle
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;
		}
		if (Start.x < End.x&&End.y <= Start.y) {
			if (P.x <= Start.x+2&&P.x>=Start.x-2) {
				if (P.y <= Start.y&&P.y >= End.y - 5)
					return true;
			}
			if (P.y <= End.y + 7&& P.y >= End.y + 3) {
				if (P.x >= Start.x&&P.x <= End.x)
					return true;
			}
			if (P.x <= End.x+2&&P.x>=End.x-2) {
				if (P.y >= End.y - 5 && P.y <= End.y)
					return true;
			}
			//triangle
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;
		}
		if (End.x<Start.x&&End.y>(Start.y - (0.5)*UI.CON_HI)) {
			if (P.x <= Start.x+2&& P.x >= Start.x - 2) {
				if (P.y <= Start.y&&P.y >= Start.y - UI.CON_HI - 10)
					return true;
			}
			if (P.y <= Start.y - UI.CON_HI - 8&& P.y >= Start.y - UI.CON_HI - 12) {
				if (P.x <= Start.x&&P.x >= End.x)
					return true;
			}
			if (P.x <= End.x+2&&P.x>=End.x-2) {
				if (P.y >= Start.y - UI.CON_HI - 10 && P.y <= End.y)
					return true;
			}
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;
		}
		if (End.x <= Start.x&&End.y <= (Start.y - (0.5)*UI.CON_HI)) {
			if (P.y <= Start.y+2 && P.y >= Start.y - 2) {
				if (P.x >= Start.x&&P.x <= Start.x + (0.5)*UI.CON_WDTH + 5)
					return true;
			}
			if (P.x <= Start.x + (0.5)*UI.CON_WDTH+2&& P.x >= Start.x + (0.5)*UI.CON_WDTH -2) {
				if (P.y <= Start.y&&P.y >= End.y - 5) {
					return true;
				}
			}
			if (P.y <= End.y - 3&& P.y >= End.y - 7) {
				if (P.x <= Start.x + (0.5)*UI.CON_WDTH + 5 && P.x >= End.x) {
					return true;
				}
			}
			if (P.x <= End.x+2&& P.x >= End.x - 2) {
				if (P.y >= End.y - 5 && P.y <= End.y)
					return true;
			}
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;
		}
		
		double X, Y;
		if (GetSlope(P, Start, X) && GetSlope(P, End, Y)) {
			if (X == (-1 * Y)) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (!GetSlope(P, Start, X) && !GetSlope(P, End, Y)) {
			return true;
		}
		else if ((Start.x == P.x&&Start.y == P.y) || (End.x == P.x&&End.y == P.y)) {
			return true;
		}
		else {
			return false;
		}

	}
	if (Case == 2) {//false connector
		if (End.x > Start.x&&End.x <= (Start.x + UI.CON_WDTH) && End.y > Start.y) {
			if (P.x <= Start.x+2&& P.x >= Start.x - 2) {
				if (P.y >= Start.y&&P.y <= End.y - 5)
					return true;
			}
			if (P.y <= End.y - 3 && P.y >= End.y - 7) {
				if (P.x >= Start.x&&P.x <= End.x)
					return true;
			}
			if (P.x <= End.x+2&& P.x <= End.x - 2) {
				if (P.y >= End.y - 5 && P.y <= End.y)
					return true;
			}
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;
		}
		if (Start.x == End.x&&End.y > Start.y) {
			if (P.x <= Start.x+2&&P.x>=Start.x-2) {
				if (P.y >= Start.y&&P.y <= End.y)
					return true;
			}
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;
		}
		if (Start.x > End.x&&Start.y < End.y) {
			if (P.y <= Start.y+2&&P.y>=Start.y-2) {
				if (P.x <= Start.x&&P.x >= End.x)
					return true;
			}
			if (P.x <= End.x+2&&P.y>=End.x-2) {
				if (P.y >= Start.y&&P.y <= End.y)
					return true;
			}
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;
		}
		if (Start.x > End.x&&End.y <= Start.y) {
			if (P.x <= Start.x+2&&P.x>=Start.x-2) {
				if (P.y <= Start.y&&P.y >= End.y - 5)
					return true;
			}
			if (P.y <= End.y - 3&& P.y >= End.y - 7) {
				if (P.x <= Start.x&&P.x >= End.x)
					return true;
			}
			if (P.x <= End.x+2&& P.x >= End.x-2) {
				if (P.y >= End.y - 5 && P.y <= End.y)
					return true;
			}
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;
		}
		if (Start.x <= End.x&&End.y <= Start.y - (0.5)*UI.CON_HI) {
			if (P.y <= Start.y+2&& P.y >= Start.y-2) {
				if (P.x <= Start.x&&P.x >= Start.x - (0.5)*UI.CON_WDTH - 5)
					return true;
			}
			if (P.x <= Start.x - (0.5)*UI.CON_WDTH - 3&& P.x >= Start.x - (0.5)*UI.CON_WDTH - 7) {
				if (P.y <= Start.y&&P.y >= End.y - 5)
					return true;
			}
			if (P.y <= End.y - 3&&P.y>=End.y-7) {
				if (P.x >= Start.x - (0.5)*UI.CON_WDTH - 5 && P.x <= End.x)
					return true;
			}
			if (P.x <= End.x+2&&P.x>=End.x-2) {
				if (P.y >= End.y - 5 && P.y <= End.y)
					return true;
			}
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;
		}
		if (End.x > Start.x&&End.y > (Start.y - (0.5)*UI.CON_HI)) {
			if (P.x <= Start.x+2&P.x>=Start.x-2) {
				if (P.y <= Start.y&&P.y >= Start.y - UI.CON_HI - 5)
					return true;
			}
			if (P.y <= Start.y - UI.CON_HI - 3&& P.y >= Start.y - UI.CON_HI - 7) {
				if (P.x >= Start.x&&P.x <= End.x)
					return true;
			}
			if (P.x <= End.x+2&&P.x>=End.x-2) {
				if (P.y >= Start.y - UI.CON_HI - 5 && P.y <= End.y)
					return true;
			}
			if (P.x >= End.x - 5 && P.x <= End.x + 5 && P.y <= End.y&&P.y >= End.y - 5)
				return true;
			return false;
		}
	
		double X, Y;
		if (GetSlope(P, Start, X) && GetSlope(P, End, Y)) {
			if (X == (-1 * Y)) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (!GetSlope(P, Start, X) && !GetSlope(P, End, Y)) {
			return true;
		}
		else if ((Start.x == P.x&&Start.y == P.y) || (End.x == P.x&&End.y == P.y)) {
			return true;
		}
		else {
			return false;
		}

	}
	
}

bool Connector::GetSlope(Point A, Point B, double & result)
{
	if (A.x == B.x) {
		return false;
	}
	result = (double)(B.y - A.y) / (B.x - A.x);
	return true;
}

void Connector::setCase(int rCase)
{
	if (rCase == 0 || rCase == 1 || rCase == 2) {
		Case = rCase;
	}
}

void Connector::Save(ofstream & OutFile)
{
	OutFile << SrcStat->getID() << "  " << DstStat->getID() << "  " << Case << endl;
	
}

void Connector::Load(ifstream & Infile, int & ID1, int & ID2)
{
	Infile >> ID1 >> ID2 >> Case;
}

int Connector::getCase()
{
	return Case;
}

