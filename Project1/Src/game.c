#include <stdio.h>
#include "cprocessing.h"

#define GOL_GRID_COLS 30
#define GOL_GRID_ROWS 30
#define GOL_GRID_BUFFERS 2

#define GOL_ALIVE 1
#define GOL_DEAD 0

#define TRUE 1
#define FALSE 0

int gIsPaused;
int gGrids[GOL_GRID_BUFFERS][GOL_GRID_ROWS][GOL_GRID_COLS];

int windowSizeX = 1920;
int windowSizeY = 1080;
//declare the cell height & cell length
int cellHeight;
int cellWidth;
//declare position click height and lenght
int MouseClickWidth;
int MouseClickHeight;
/* Feel free to declare your own variables here */
int count;
int currentRow;
int AliveCount;


void game_init(void)
{
    //set my window size to HD cause why not who dont love HD right
    CP_System_SetWindowSize(windowSizeX, windowSizeY);
  
    cellHeight = windowSizeY / GOL_GRID_ROWS;
    cellWidth = windowSizeX / GOL_GRID_COLS;
    
  
    /* Set every grids' cells as 'dead' */
    for (int row = 0; row < GOL_GRID_ROWS; ++row)
    {
        for (int col = 0; col < GOL_GRID_COLS; ++col)
        {
            for (int i = 0; i < GOL_GRID_BUFFERS; ++i)
            {
                gGrids[i][row][col] = GOL_DEAD;
            }
        }
    }

    /*********************************************************
    *  Let's start with gGrids[0] as the 'reference grid'
    *  and gGrids[1] as the 'displaying grid'.
    *
    *  We initialize gGrids[0] with a simple 'glider'.
    *********************************************************/

    gGrids[0][1][2] = GOL_ALIVE;
    gGrids[0][2][3] = GOL_ALIVE;
    gGrids[0][3][1] = GOL_ALIVE;
    gGrids[0][3][2] = GOL_ALIVE;
    gGrids[0][3][3] = GOL_ALIVE;

    /* We start unpaused */
    gIsPaused = TRUE;

    printf("cellHeight : %d\n", cellHeight);
    printf("cellwidth : %d\n", cellWidth);
    /* Initialization of your other variables here */
    count = 0;
    currentRow = 0;
    AliveCount = 0;
}

//check surrounding logic
int CheckSurrounding(int Check, int row, int col)
{
    count = 0;
    if (gGrids[Check][row - 1][col - 1] == GOL_ALIVE && ((row != -1) || (col != -1)))
    {
        count++;
    }
    if (gGrids[Check][row - 1][col] == GOL_ALIVE && (row != -1))
    {
        count++;
    }
    if (gGrids[Check][row - 1][col + 1] == GOL_ALIVE && ((row != -1) || (col < GOL_GRID_COLS)))
    {
        count++;
    }
    if (gGrids[Check][row][col - 1] == GOL_ALIVE && (col != -1))
    {
        count++;
    }
    if (gGrids[Check][row][col + 1] == GOL_ALIVE && (col < GOL_GRID_COLS))
    {
        count++;
    }
    if (gGrids[Check][row + 1][col - 1] == GOL_ALIVE && ((row < GOL_GRID_ROWS) || (col < GOL_GRID_COLS)))
    {
        count++;
    }
    if (gGrids[Check][row + 1][col] == GOL_ALIVE && ((row < GOL_GRID_ROWS) || (col != -1)))
    {
        count++;
    }
    if (gGrids[Check][row + 1][col + 1] == GOL_ALIVE && (row < GOL_GRID_ROWS))
    {
        count++;
    }
    return count;

}

//game logic
void gameplaylogic()
{

    for (int newColumn = 0; newColumn < GOL_GRID_COLS; ++newColumn)
    {
        for (int newRow = 0; newRow < GOL_GRID_ROWS; ++newRow)
        {
            AliveCount = CheckSurrounding(0, newRow, newColumn);
            if ((AliveCount == 2 || AliveCount == 3) && gGrids[0][newRow][newColumn]== GOL_ALIVE)
            {
                gGrids[1][newRow][newColumn] = GOL_ALIVE;
            }
            else if (AliveCount == 3 && gGrids[0][newRow][newColumn] == GOL_DEAD)
            {
                gGrids[1][newRow][newColumn] = GOL_ALIVE;
            }
            else
            {
                gGrids[1][newRow][newColumn] = GOL_DEAD;
            }
        }
    }

    for(int newColumn = 0; newColumn < GOL_GRID_COLS; ++newColumn)
    {
        for (int newRow = 0; newRow < GOL_GRID_ROWS; ++newRow)
        {
            gGrids[0][newRow][newColumn] = gGrids[1][newRow][newColumn];
        }
    }

}

//mouse click
void MouseClick(void)
{
    if (CP_Input_MouseClicked())
    {
        if (gGrids[0][MouseClickWidth][MouseClickHeight] == GOL_DEAD)
        {
            gGrids[0][MouseClickWidth][MouseClickHeight] = GOL_ALIVE;
            
        }
        else if (gGrids[0][MouseClickWidth][MouseClickHeight] == GOL_ALIVE)
        {
            gGrids[0][MouseClickWidth][MouseClickHeight] = GOL_DEAD;

        }

    }
}

//pasue
void PauseGame(void) 
{

    if (CP_Input_KeyTriggered(KEY_ANY))
    {
        gIsPaused = !gIsPaused;

    }

   

}
//render
void renderingGame(void)
{


    //rendering out of the loop 
    for (int row = 0; row < GOL_GRID_ROWS; ++row)
    {
        for (int col = 0; col < GOL_GRID_COLS; ++col)
        {
            for (int i = 0; i < GOL_GRID_BUFFERS; ++i)
            {

                if (gGrids[0][row][col] == GOL_ALIVE)
                {
                    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
                    CP_Graphics_DrawRect(row * cellWidth, col * cellHeight, cellWidth, cellHeight);
                }
                //draw rectangle
                else if (gGrids[0][row][col] == GOL_DEAD)
                {
                    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 0));
                    CP_Graphics_DrawRect(row * cellWidth, col * cellHeight, cellWidth, cellHeight);
                }

            }

        }
    }
}

//update
void game_update(void)
{
    // TODO
    //mouse click position update
    MouseClickWidth = CP_Input_GetMouseX() / cellWidth;
    MouseClickHeight = CP_Input_GetMouseY() / cellHeight;

    //clear background
    CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
    MouseClick();
    if (!gIsPaused)
    {
      gameplaylogic();
    }
    PauseGame();
    renderingGame();
  //  printf(printf("count %d", count));

}

