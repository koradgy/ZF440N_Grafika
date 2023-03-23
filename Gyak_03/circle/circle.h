#ifndef CIRCLE_H
#define CIRCLE_H

#include<SDL2/SDL.h>

/**
 * Data of a circle object in Descartes coordinate system
 */
typedef struct Circle
{
	double x;
	double y;
	double radius;
	SDL_Color color;
} Circle;

/**
 * Set the data of the circle
 */
void set_circle_data(Circle* circle, double x, double y, double radius, SDL_Color color);

/**
 * Calculate the area of the circle.
 */
double calc_circle_area(const Circle* circle);

#endif // CIRCLE_H
