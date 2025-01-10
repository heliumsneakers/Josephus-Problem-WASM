#include "logic.h"
#include "raylib.h"
#include "raygui.h"
#include "string.h"
#include <stdint.h>
#include <math.h>

unsigned int result = 0;
unsigned int bitShifted = 0;
int label;
char resultStr[12];
char displayText[50];

bool problemState = false;
bool canCalculate = false;
bool restart = false;

int WIDTH = 800;
int HEIGHT = 600;

// Find the minimum number of bits required for representation of n
int min_bits_required(unsigned int n) {
    return (int)(log2(n) + 1); // Add 1 to include the most significant bit
}

// Cyclical left shift with wrapping within n bits
unsigned int left_shift_wrap(unsigned int value, int n) {
    // Use an n-bit mask to ensure wrapping and prevent bit loss
    unsigned int mask = (1U << n) - 1; // Generate a mask with n bits set
    return ((value << 1) | (value >> (n - 1))) & mask;
}

// Perform the bit shift operation for Josephus calculation
void bit_shift() {
    if (canCalculate) {

        int n = min_bits_required(result);

        bitShifted = left_shift_wrap(result, n);

        canCalculate = false;
    }
}

void Intro(void){

	DrawText("The Josephus Problem:", 190, 200, 20, RED);

	label = GuiLabel((Rectangle){50, 220, WIDTH - 100, 200}, "You and your fellow soldiers are surrounded. They decide on a fair way to end things among them. All soldiers must form a circle. Starting from the first soldier, we kill every second soldier (e.g., 2, 4, 6, 8, 10....). We want no part in this, we wish to survive, so who will be the last surviving soldier for n soldiers?");
	GuiSetStyle(label, TEXT_WRAP_MODE, TEXT_WRAP_WORD);
	GuiSetStyle(label,TEXT_LINE_SPACING, 20);
	GuiSetStyle(label, TEXT_SIZE, 20); 

	ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

	GuiSpinner((Rectangle){ 350,450,150,25 }, "Enter the Number of Soldiers	", &result, 1, 100000, true);

	if (result >= 1){
	sprintf(resultStr, "%d", result);
       	sprintf(displayText, "Soldiers: %s", resultStr);
	DrawText(displayText, 190, 250, 20, BLACK);
	
	GuiToggle((Rectangle){ 355, 250, 150, 25 }, "Begin", &problemState);
	canCalculate = true;
	}
}

void JosephusProblem(void) {
    bit_shift();

    DrawCircle(WIDTH / 2, HEIGHT / 2, 80, RED);


    sprintf(resultStr, "%u", bitShifted);
    sprintf(displayText, "Survivor: #%s", resultStr);
    DrawText(displayText, 340, 295, 15, BLACK);

    if (GuiButton((Rectangle){ 10, 10, 100, 30 }, "Restart")) {
        problemState = false;
        canCalculate = false;
        restart = false;
        result = 0;
        bitShifted = 0;
    }
}

