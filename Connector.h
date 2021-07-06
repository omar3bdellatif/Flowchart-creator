#ifndef CONNECTOR_H
#define CONNECTOR_H
#include<string>
#include "GUI\UI_Info.h"
#include "GUI\output.h"
#include"GUI\Output.h"
class Conditional;
class Statement;

class Connector	//a connector that connects two statements (Source & Destination)
{
private:
	Statement *SrcStat;	//The source statement of the connector
	Statement *DstStat;	//The destination statement of the connector
	Point Start;	//Start point of the connector
	Point End;		//End point of the connector
	bool Selected;
	int Case; 
public:
	Connector(Statement* Src, Statement* Dst,int rCase);

	void		setSrcStat(Statement *Src);
	Statement*	getSrcStat()const;	
	void		setDstStat(Statement *Dst);
	Statement*	getDstStat();
	
	void setStartAndEnd();
	void setStartPoint(Point P);
	Point getStartPoint();

	void setEndPoint(Point P);
	Point getEndPoint();

	void Draw(Output* pOut)const;
	void setSelected(bool rSelected);
	bool IsSelected()const;
	bool isInConnector(Point P);
	bool GetSlope(Point A, Point B, double &result);
	void setCase(int rCase = 0);
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile,int &ID1,int&ID2);
	int getCase();
	

};

#endif