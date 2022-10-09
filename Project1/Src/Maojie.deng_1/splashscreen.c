#include "splashscreen.h"
#include <stdio.h>

//null pointer image
 CP_Image testingImage = NULL;
 float currentAlpha = 1;
 int Bool = 0;
 float xmousePosition;
 float ymousePosition;
 int speedoboi = 100;
 int Follow = 0;

 //0 false
 //1 true
void splash_screen_init(void)
{
	//init the winwdow size base on computer resolution from any pcs
	CP_System_SetWindowSize(CP_System_GetDisplayWidth(), CP_System_GetDisplayHeight());
	//init images into testingImage
	testingImage = CP_Image_Load("./Assets/DigiPen_BLACK.png");

	int height = CP_Image_GetHeight(testingImage);
	

	
}

void splash_screen_update(void)
{
	//another method is get ur display height/width
	//float width = CP_System_GetDisplayWidth();
	//float height = CP_System_GetDisplayHeight();

	//CP_Image_Draw(testingImage, width  /2, height /2, width / 2, width / 2, 255);
	CP_Graphics_ClearBackground(CP_Color_Create(10, 10, 10, 10));
	//position for xmouse from inputs CP
	xmousePosition = CP_Input_GetMouseX();
	//position for ymouse from inputs CP
	ymousePosition = CP_Input_GetMouseY();
	//computer screen widths
	int windowWidth = CP_System_GetWindowWidth();
	//computer screen heights
	int windowHeight = CP_System_GetWindowHeight();
	//delta time 
	float dt = CP_System_GetDt();
	// debug the position of the mouse
	// printf("Hello tis is pointer position x: %.2f/n",xmousePosition);
	// printf("Hello tis is pointer position y: %.2f/n", ymousePosition);
	//draw circle
	CP_Graphics_DrawCircle(xmousePosition,ymousePosition, 50.0f);
	
	//draw screens
	CP_Image_Draw(testingImage, windowWidth / 2, windowHeight / 2, windowWidth / 2, windowHeight / 2, currentAlpha);
	if (Bool == 0)
	{
		if (currentAlpha <= 255)
		{
			currentAlpha += speedoboi * dt;
		}
		else if (currentAlpha >= 255)
		{		
				Bool = 1;
		}
	}
	else if (Bool == 1)
	{
		currentAlpha -= speedoboi * dt;

		if (currentAlpha <= 10)
		{
			Bool = 0;
		}
	}
}



void splash_screen_exit(void)
{
	CP_Image_Free(&testingImage);
}
