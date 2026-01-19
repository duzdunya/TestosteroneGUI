#ifndef H_EASINGS
#define H_EASINGS

#include <math.h>
#define EASING_C1 1.70158
#define EASING_C2 2.59490 
#define EASING_C3 2.70158
#define EASING_C4 2.09439510239
#define EASING_C5 1.3962634016
#define EASING_N1 7.5625
#define EASING_D1 2.75

//c2 = c1 * 1.525;
//c3 = c1 +1
//c4 = (2*PI)/3
//c5 = (2*PI)/4.5

// Sine
double easeInSine(double x); 
double easeOutSine(double x); 
double easeInOutSine(double x); 

// Quad
double easeInQuad(double x); 
double easeOutQuad(double x); 
double easeInOutQuad(double x); 

// Qubic
double easeInQubic(double x); 
double easeOutCubic(double x); 
double easeInOutCubic(double x); 

// Quart
double easeInQuart(double x); 
double easeOutQuart(double x); 
double easeInOutQuart(double x); 

// Quint
double easeInQuint(double x); 
double easeOutQuint(double x); 
double easeInOutQuint(double x); 

// Expo
double easeInExpo(double x); 
double easeOutExpo(double x); 
double easeInOutExpo(double x); 

// Circ

double easeInCirc(double x); 
double easeOutCirc(double x); 
double easeInOutCirc(double x); 

// Back
double easeInBack(double x); 
double easeOutBack(double x); 
double easeInOutBack(double x); 

// Elastic
double easeInElastic(double x); 
double easeOutElastic(double x); 
double easeInOutElastic(double x); 

// Bounce
double easeOutBounce(double x); 
double easeInBounce(double x); 
double easeInOutBounce(double x); 

#endif
