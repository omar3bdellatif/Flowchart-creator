#include "Statement.h"
#include "..\ApplicationManager.h"
Statement::Statement(int Num, bool CanConn)
	:MaxOutConn(Num), CanInconn(CanConn)
{
	//TODO: set the ID with a unique value
	static int count = 0;
	IsInConnected = false;
	Text = "";
	Selected = false;
	OutputConn[0] = NULL;
	OutputConn[1] = NULL;
	ActualOutConnectors = 0;
	ID = ++count;

}

void Statement::SetSelected(bool s)
{	Selected = s; }

bool Statement::IsSelected() const
{	return Selected; }

void Statement::ReleaseConnector(int i)
{

	if (i >= 0 && i < 2)
	{
		if (MaxOutConn == 2)
		{
			OutputConn[i] = NULL;
		}
		else if (MaxOutConn == 1)
		{
			OutputConn[0] = NULL;
		}
	}

}

int Statement::GetMaxOutConn() const
{
	return MaxOutConn;
}

Connector * Statement::GetConnecter(int i)
{
	if (i >= 0 && i < 2)
	{
		if (MaxOutConn == 2)
		{
			return OutputConn[i];
		}
		else if (MaxOutConn == 1)
		{
			return OutputConn[0];
		}
	}
	return NULL;
}

void Statement::setConnector( Connector*C, int i)
{
	if (i >= 0 && i < 2)
	{
		if (MaxOutConn == 2)
		{
			OutputConn[i]=C;
		}
		else if (MaxOutConn == 1)
		{
			OutputConn[0]=C;
		}
	}
	

}

void Statement::SetIsInConnected(bool B)
{
	IsInConnected = B;
}

bool Statement::GetIsInConnected() const
{
	return IsInConnected;
}

bool Statement::CanBeConnected() const
{
	return CanInconn;
}

Point Statement::getInlet() const
{
	if (this) {
		return Inlet;
	}
	else {
		return Point(0, 0);
	}
}

Point Statement::getOutlet() const
{
	if (this) {
		return Outlet;
	}
	else {
		return Point(0, 0);
	}
}

void Statement::AddActual()
{
	ActualOutConnectors++;
}

int Statement::getID()
{
	return ID;
}
int Statement::GetActOutConn() const
{
	return ActualOutConnectors;
}

void Statement::DecrAct()
{
	ActualOutConnectors--;
}

bool Statement::Simulate(ApplicationManager *pManager)
{
	return true;
}


