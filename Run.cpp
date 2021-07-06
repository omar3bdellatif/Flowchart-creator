#include "Run.h"

#include "GUI\input.h"
#include "GUI\Output.h"
#include <sstream>
using namespace std;

Run::Run(ApplicationManager * ApM)
	:Action(ApM)
{
}

void Run::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
}

void Run::Execute()
{
	Validate V(pManager);
	V.Execute();
	if (!V.IsAllValid())
	{
		pManager->GetOutput()->PrintMessage("Flowchart isn't Valid");
		return;
	}
	Output* pOut=pManager->GetOutput();
	pOut->ClearOutputBar();
	Statement *flow = pManager->GetStart();
	flow = (flow->GetConnecter())->getDstStat();
	while (flow->GetMaxOutConn() != 0)
	{
		bool Case = flow->Simulate(pManager);
		if (flow->GetMaxOutConn() == 1)
		{

			flow = (flow->GetConnecter())->getDstStat();
		}
		else
		{
			if (Case == true)
			{
				flow = (flow->GetConnecter(1))->getDstStat();
			}
			else
			{
				flow = (flow->GetConnecter())->getDstStat();

			}

		}

	}

}

Run::~Run()
{
}
