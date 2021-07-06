#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.width = 1600;///////////////////////
	UI.height = 720;
	UI.wx = 15;
	UI.wy = 15;

	UI.AppMode = DESIGN;	//Design Mode is the default mode

	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 80;
	UI.DrawingAreaWidth = 0.75 * UI.width;

	UI.DrawColor = BLUE;
	UI.HighlightColor = RED;
	UI.MsgColor = RED;

	UI.ASSGN_WDTH = 150;
	UI.ASSGN_HI = 50;
	UI.CON_WDTH = 150;
	UI.CON_HI = 100;
	UI.EL_WDTH = 150;
	UI.EL_HI = 50;
	UI.PG_WDTH = 150;
	UI.PG_HI = 50;


	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Programming Techniques Project");

	pWind->SetPen(RED, 3);
	CreateDesignToolBar();
	CreateStatusBar();
	ClearDrawArea();
	ClearOutputBar();
}


Input* Output::CreateInput()
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar()
{
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
//TODO: Complete this function
void Output::CreateDesignToolBar() //Draws the Design Menu
{
	UI.AppMode = DESIGN;	//Design Mode

							//fill the tool bar 

							//You can draw the tool bar icons in any way you want.
							//Below is one possible way

							//First prepare List of images for each menu item
							//To control the order of these images in the menu, 
							//reoder them in Defs.h ==> enum DrawMenuItem
	string MenuItemImages[DSN_ITM_CNT];
	MenuItemImages[ITM_VALUE_ASSIGN] = "images\\ValueAssign.jpg";
	MenuItemImages[ITM_OPERATOR_ASSIGN] = "images\\OperatorAssign.jpg";////////
	MenuItemImages[ITM_VARIABLE_ASSIGN] = "images\\VariableAssign.jpg";/////////
	MenuItemImages[ITM_COND] = "images\\Condition.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Exit.jpg";
	MenuItemImages[ITM_SAVE] = "images\\Save.jpg";
	MenuItemImages[ITM_END]= "images\\End.jpg";//////////////
	MenuItemImages[ITM_DESIGN_MENU] = "images\\DesignMenu.jpg";
	MenuItemImages[ITM_START] = "images\\Start.jpg";
	MenuItemImages[ITM_READ] = "images\\Read.jpg";
	MenuItemImages[ITM_WRITE] = "images\\Write.jpg";
	MenuItemImages[ITM_CPY] = "images\\Copy.jpg";
	MenuItemImages[ITM_CUT] = "images\\Cut.jpg";
	MenuItemImages[ITM_PST] = "images\\Paste.jpg";
	MenuItemImages[ITM_EDIT] = "images\\Edit.jpg";
	MenuItemImages[ITM_DELETE] = "images\\Delete.jpg";
	MenuItemImages[ITM_S_US] = "images\\SelectUnselect.jpg";
	MenuItemImages[ITM_SWITCH] = "images\\Switch.jpg";
	MenuItemImages[ITM_LOAD] = "images\\LOAD.jpg";
	MenuItemImages[ITM_CONNECT] = "images\\Connect.jpg";



	//TODO: Prepare images for each menu item and add it to the list


	//Draw menu item one image at a time
	for (int i = 0; i<DSN_ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	//Draw a line under the toolbar
	pWind->SetPen(RED, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
//TODO: Complete this function
void Output::CreateSimulationToolBar() //Draws the Simulation Menu
{
	UI.AppMode = SIMULATION;	//Simulation Mode
	ClearToolBar();

	///TODO: add code to create the simulation tool bar

	string MenuItemImages[SIM_ITM_CNT];
	MenuItemImages[ITM_VALIDATE] = "images\\Validate.jpg";
	MenuItemImages[ITM_RUN] = "images\\Run.jpg";
	MenuItemImages[ITM_SWITCH_] = "images\\Switch.jpg";


	for (int i = 0; i<SIM_ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	pWind->SetPen(RED, 2);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);



}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea()
{
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.DrawingAreaWidth, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearOutputBar()
{
	//Create output bar by drawing a filled rectangle
	pWind->SetPen(RED, 2);
	pWind->SetBrush(LIGHTBLUE);
	pWind->DrawRectangle(UI.DrawingAreaWidth, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}

void Output::ClearToolBar()
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, pWind->GetWidth(), UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.25), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////

//======================================================================================//
//								Statements Drawing Functions								//
//======================================================================================//

//Draw assignment statement and write the "Text" on it
void Output::DrawAssign(Point Left, int width, int height, string Text, bool Selected)
{
	//check if the given point is a valid one




	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color

										//Draw the statement block rectangle
	pWind->DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height);

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 4, Left.y + height / 4, Text);
}

void Output::DrawConditionalStat(Point Left, int width, int height, string Text, bool Selected) {


	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	int X[4] = { Left.x,Left.x + (width / 2),Left.x + width,Left.x + (width / 2) };
	int Y[4] = { Left.y,Left.y + (height / 2),Left.y,Left.y - (height / 2) };

	pWind->DrawPolygon(X, Y, 4);

	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 4, Left.y, Text);

}

void Output::DrawStart(Point Left, int width, int height, bool Selected) {
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	pWind->DrawEllipse(Left.x, Left.y, Left.x + width, Left.y + height);

	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 4, Left.y + height / 4, "START");
}

void Output::DrawEnd(Point Left, int width, int height, bool Selected) {
	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	pWind->DrawEllipse(Left.x, Left.y, Left.x + width, Left.y + height);

	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 4, Left.y + height / 4, "END");
}

void Output::DrawIOStat(Point Left, int width, int height, string Text, bool Selected) {


	if (Selected)
		pWind->SetPen(UI.HighlightColor, 3);
	else
		pWind->SetPen(UI.DrawColor, 3);

	int X[4] = { Left.x,Left.x + width,Left.x + width - (0.1*width),Left.x - (0.1*width) };
	int Y[4] = { Left.y,Left.y,Left.y + height,Left.y + height };

	pWind->DrawPolygon(X, Y, 4);

	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 3, Left.y + height / 4, Text);
}





//TODO: Add similar functions for drawing all other statements.
//		e.g. DrawCondtionalStat(......), DrawStart(......), DrawEnd(.......), ...etc
//		Decide the parameters that should be passed to each of them

//TODO: Add DrawConnector function

void Output::DrawConnector(Point Start, Point End, bool Selected, int Case) {
	if (Selected) {
		pWind->SetPen(UI.HighlightColor, 2);
	}
	else {
		pWind->SetPen(UI.DrawColor, 2);
	}
	if (Case == 0) {
		if (Start.x == End.x&&End.y > Start.y) {
			pWind->DrawLine(Start.x, Start.y, End.x, End.y);
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);
			return;
		}
		if ((Start.x < End.x&&Start.y + 5 < End.y) || (Start.x > End.x&&Start.y + 5 < End.y)) {
			pWind->DrawLine(Start.x, Start.y, Start.x, Start.y + 5);
			pWind->DrawLine(Start.x, Start.y + 5, End.x, Start.y + 5);
			pWind->DrawLine(End.x, Start.y + 5, End.x, End.y);
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);
			return;
		}
		if ((End.x > Start.x&&Start.y + 5 >= End.y&&End.x>(Start.x + UI.ASSGN_WDTH))) {
			pWind->DrawLine(Start.x, Start.y, Start.x, Start.y + 5);
			pWind->DrawLine(Start.x, Start.y + 5, End.x - (0.5)*UI.ASSGN_WDTH, Start.y + 5);
			pWind->DrawLine(End.x - (0.5)*UI.ASSGN_WDTH, Start.y + 5, End.x - (0.5)*UI.ASSGN_WDTH, End.y - 5);
			pWind->DrawLine(End.x - (0.5)*UI.ASSGN_WDTH, End.y - 5, End.x, End.y - 5);
			pWind->DrawLine(End.x, End.y - 5, End.x, End.y);
			//draw triangle,also you might want to test that 5 value
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);

			return;
		}
		if (End.x < Start.x&&End.x < Start.x - UI.ASSGN_WDTH&&Start.y+5 >= End.y) {
			pWind->DrawLine(Start.x, Start.y, Start.x, Start.y + 5);
			pWind->DrawLine(Start.x, Start.y +5, End.x + (0.5)*UI.ASSGN_WDTH, Start.y + 5);
			pWind->DrawLine(End.x + (0.5)*UI.ASSGN_WDTH, Start.y + 5, End.x + (0.5)*UI.ASSGN_WDTH, End.y-5);
			pWind->DrawLine(End.x + (0.5)*UI.ASSGN_WDTH, End.y - 5, End.x, End.y - 5);
			pWind->DrawLine(End.x, End.y - 5, End.x, End.y);
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);
			return;
		}
		if (End.x == Start.x&&End.y < Start.y) {

			pWind->DrawLine(Start.x, Start.y, Start.x, Start.y + 5);
			pWind->DrawLine(Start.x, Start.y + 5, Start.x + (0.75)*UI.ASSGN_WDTH, Start.y + 5);
			pWind->DrawLine(Start.x + (0.75)*UI.ASSGN_WDTH, Start.y + 5, Start.x + (0.75)*UI.ASSGN_WDTH, End.y - 5);
			pWind->DrawLine(Start.x + (0.75)*UI.ASSGN_WDTH, End.y - 5, End.x, End.y -5);
			pWind->DrawLine(End.x, End.y - 5, End.x, End.y);
			//triangle,5
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);

			return;
		}
		if (End.x > Start.x&&End.x <= Start.x + UI.ASSGN_WDTH&&End.y <= Start.y+5) {

			pWind->DrawLine(Start.x, Start.y, Start.x, Start.y + (1.25)*UI.ASSGN_HI);
			pWind->DrawLine(Start.x, Start.y + (1.25)*UI.ASSGN_HI, End.x+(0.5)*UI.ASSGN_WDTH, Start.y + (1.25)*UI.ASSGN_HI);
			pWind->DrawLine(End.x + (0.5)*UI.ASSGN_WDTH, Start.y + (1.25)*UI.ASSGN_HI, End.x + (0.5)*UI.ASSGN_WDTH, End.y - 5);
			pWind->DrawLine(End.x + (0.5)*UI.ASSGN_WDTH, End.y - 5, End.x, End.y -5);
			pWind->DrawLine(End.x, End.y - 5, End.x, End.y);
			//triangle
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);

			return;
		}
		if (End.x < Start.x&&End.x >= Start.x - UI.ASSGN_WDTH&&End.y <= Start.y+5) {
			pWind->DrawLine(Start.x, Start.y, Start.x, Start.y + (1.25)*UI.ASSGN_HI);
			pWind->DrawLine(Start.x, Start.y + (1.25)*UI.ASSGN_HI, End.x - (0.5)*UI.ASSGN_WDTH, Start.y + (1.25)*UI.ASSGN_HI);
			pWind->DrawLine(End.x - (0.5)*UI.ASSGN_WDTH, Start.y + (1.25)*UI.ASSGN_HI, End.x - (0.5)*UI.ASSGN_WDTH, End.y - 5);
			pWind->DrawLine(End.x - (0.5)*UI.ASSGN_WDTH, End.y - 5, End.x, End.y - 5);
			pWind->DrawLine(End.x, End.y - 5, End.x, End.y);
			//triangle
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);
			return;
		}
		pWind->DrawLine(Start.x, Start.y, End.x, End.y);
		return;
	}
	else if (Case == 1)  {//True connector
		if (End.x<Start.x&&End.x >= Start.x - UI.CON_WDTH&&End.y>Start.y) {
			pWind->DrawLine(Start.x, Start.y, Start.x, End.y - 5);
			pWind->DrawLine(Start.x, End.y - 5, End.x, End.y - 5);
			pWind->DrawLine(End.x, End.y - 5, End.x, End.y);
			//triangle
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);

			return;
		}
		if (Start.x == End.x&&End.y > Start.y) {
			pWind->DrawLine(Start.x, Start.y, End.x, End.y);
			//triangle
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);

			return;
		}
		if (Start.x < End.x&&End.y > Start.y) {
			pWind->DrawLine(Start.x, Start.y, End.x, Start.y);
			pWind->DrawLine(End.x, Start.y, End.x, End.y);
			//triangle
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);

			return;
		}
		if (Start.x < End.x&&End.y <= Start.y) {
			pWind->DrawLine(Start.x, Start.y, Start.x, End.y - 5);
			pWind->DrawLine(Start.x, End.y - 5, End.x, End.y - 5);
			pWind->DrawLine(End.x, End.y - 5, End.x, End.y);
			//triangle
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);

			return;
		}
		if (End.x<Start.x&&End.y>(Start.y - (0.5)*UI.CON_HI)) {
			pWind->DrawLine(Start.x, Start.y,Start.x, Start.y - UI.CON_HI - 10);
			pWind->DrawLine(Start.x, Start.y - UI.CON_HI - 10, End.x, Start.y - UI.CON_HI - 10);
			pWind->DrawLine(End.x, Start.y - UI.CON_HI - 10, End.x, End.y);
			//triangle
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);
			return;
		}
		if (End.x <= Start.x&&End.y <= (Start.y - (0.5)*UI.CON_HI)) {
			pWind->DrawLine(Start.x, Start.y, Start.x +(0.5)*UI.CON_WDTH+ 5, Start.y);
			pWind->DrawLine(Start.x + (0.5)*UI.CON_WDTH + 5, Start.y, Start.x + (0.5)*UI.CON_WDTH + 5, End.y-5);
			pWind->DrawLine(Start.x + (0.5)*UI.CON_WDTH + 5, End.y - 5, End.x, End.y - 5);
			pWind->DrawLine(End.x, End.y - 5, End.x, End.y);
			//triangle revise!!!!!!!!!
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);

			return;
		}
	
		pWind->DrawLine(Start.x, Start.y, End.x, End.y);
		return;

	}
	if (Case == 2) {//false connector
		if (End.x > Start.x&&End.x <= (Start.x + UI.CON_WDTH) && End.y > Start.y) {
			pWind->DrawLine(Start.x, Start.y, Start.x, End.y - 5);
			pWind->DrawLine(Start.x, End.y - 5, End.x, End.y - 5);
			pWind->DrawLine(End.x, End.y - 5, End.x, End.y);
			//tri
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);

			return;
		}
		if (Start.x == End.x&&End.y > Start.y) {
			pWind->DrawLine(Start.x, Start.y, End.x, End.y);
			//traingle
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);
			return;
		}
		if (Start.x > End.x&&Start.y < End.y) {
			pWind->DrawLine(Start.x, Start.y, End.x, Start.y);
			pWind->DrawLine(End.x, Start.y, End.x, End.y);
			//tri
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);

			return;
		}
		if (Start.x > End.x&&End.y <= Start.y) {
			pWind->DrawLine(Start.x, Start.y, Start.x, End.y - 5);
			pWind->DrawLine(Start.x, End.y - 5, End.x, End.y - 5);
			pWind->DrawLine(End.x, End.y - 5, End.x, End.y);
			//tri
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);
			return;
		}
		if (Start.x <= End.x&&End.y <= Start.y - (0.5)*UI.CON_HI) {
			pWind->DrawLine(Start.x, Start.y, Start.x - (0.5)*UI.CON_WDTH - 5, Start.y);
			pWind->DrawLine(Start.x - (0.5)*UI.CON_WDTH - 5, Start.y, Start.x - (0.5)*UI.CON_WDTH - 5, End.y - 5);
			pWind->DrawLine(Start.x - (0.5)*UI.CON_WDTH - 5, End.y - 5, End.x, End.y - 5);
			pWind->DrawLine(End.x, End.y - 5, End.x, End.y);
			//tri
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);

			return;
		}
		if (End.x > Start.x&&End.y > (Start.y - (0.5)*UI.CON_HI)) {
			pWind->DrawLine(Start.x, Start.y, Start.x, Start.y - UI.CON_HI - 5);
			pWind->DrawLine(Start.x, Start.y - UI.CON_HI - 5, End.x, Start.y - UI.CON_HI - 5);
			pWind->DrawLine(End.x, Start.y - UI.CON_HI - 5, End.x, End.y);
			//tri
			pWind->DrawTriangle(End.x, End.y, End.x + 5, End.y - 5, End.x - 5, End.y - 5);

			return;
		}
	
		pWind->DrawLine(Start.x, Start.y, End.x, End.y);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{

}
