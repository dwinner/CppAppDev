/**
 * hotel.h -- constants and declarations for hotel.c
 */

#pragma once
#define QUIT       5
#define HOTEL1    80.00
#define HOTEL2   125.00
#define HOTEL3   155.00
#define HOTEL4   200.00
#define DISCOUNT   0.95
#define STARS "**********************************"

/**
 * @brief Shows list of choices
 *		@return void
 */
int menu(void);

/**
 * @brief Returns number of nights desired
 *		@return Number of nights desired
 */
int getnights(void);

/**
 * @brief Calculates price from rate, nights and displays result
 *		@param rate Rate
 *		@param nights Nights
 */
void showprice(double rate, int nights);
