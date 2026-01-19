#include "easings.h"

// Sine
double easeInSine(double x) { 
	return 1 - cos((x * M_PI)/2); 
}
double easeOutSine(double x) { 
	return sin((x * M_PI)/2); 
}
double easeInOutSine(double x) { 
	return -(cos(x * M_PI)-1)/2; 
}

// Quad
double easeInQuad(double x) { 
	return x * x; 
}
double easeOutQuad(double x) { 
	return 1 - (1-x) * (1-x);
}
double easeInOutQuad(double x) { 
	if (x < 0.5) return 2 * x * x;
	else return 1 - pow((-2 * x) + 2, 2) / 2;
}

// Qubic
double easeInQubic(double x) { return x * x * x; }
double easeOutCubic(double x) { return 1 - pow(1-x, 3); }
double easeInOutCubic(double x) {
	if (x < 0.5) return 4 * x * x * x;
	else return 1 - pow((-2 * x) + 2, 3) / 2;
}

// Quart
double easeInQuart(double x) { return x*x*x*x; }
double easeOutQuart(double x) { return 1 - pow(1-x, 4); }
double easeInOutQuart(double x) {
	if (x < 0.5) return 8 * x * x * x * x;
	else return 1 - pow((-2*x + 2), 4) /2;
}

// Quint
double easeInQuint(double x) { return x * x * x * x * x;}
double easeOutQuint(double x) { return 1 - pow(1-x, 5);}
double easeInOutQuint(double x) {
if (x < 0.5) return 16 * x * x * x * x * x;
	else return 1 - pow((-2*x)+2, 5)/2;
}

// Expo
double easeInExpo(double x) { 
if (x == 0.0) return 0.0;
	else return pow(2, (10 * x)-10);
}
double easeOutExpo(double x) {
	if (x == 1.0) return 1.0;
	else return 1 - pow(2, -10*x);
}
double easeInOutExpo(double x) {
	if (x == 0.0) return 0.0;
	else {
		if (x == 1.0) return 1.0;
		else {
			if (x < 0.5) return pow(2, (20*x) -10) /2;
			else return (2 - pow(2, (-20*x)+10)) / 2;
		}
	}
}

// Circ

double easeInCirc(double x) { 
return 1 - sqrt(1-pow(x,2));
}
double easeOutCirc(double x) {
return sqrt(1-pow(x-1,2));
}
double easeInOutCirc(double x) {
	if (x < 0.5) return (1 - sqrt(1-pow(2*x,2)))/2;
	else return (sqrt(1-pow((-2*x)+2, 2)) + 1)/2;
}

// Back
double easeInBack(double x) {
	return (EASING_C3 * x * x * x) - (EASING_C1 * x * x);
}
double easeOutBack(double x) {
	return 1 + (EASING_C3 * pow(x-1, 3)) + (EASING_C1 * pow(x-1,2));
}
double easeInOutBack(double x) {
	if (x < 0.5) return (pow(2*x,2) * ((EASING_C2+1) * 2 * x - EASING_C2)) / 2;
	else return (pow((2*x)-2, 2) * ((EASING_C2+1) * (x*2 - 2) + EASING_C2) + 2) / 2;
}

// Elastic
double easeInElastic(double x) {
	if (x == 0.0) return 0.0;
	else {
		if (x == 1.0) return 1.0;
		else return -pow(2, 10*x-10) * sin((x*10-10.75)*EASING_C4);
	}
}
double easeOutElastic(double x) {
	if (x == 0.0) return 0.0;
	else {
		if (x == 1.0) return 1.0;
		else return pow(2, -10*x) * sin((x*10-0.75) *EASING_C4) + 1;
	}
}
double easeInOutElastic(double x) {
	if (x == 0.0) return 0.0;
	else {
		if (x == 1.0) return 1.0;
		else {
			if (x < 0.5) return -(pow(2,20*x-10)*sin((20*x-11.125)*EASING_C5))/2;
			else return (pow(2, -20*x+10) * sin((20*x-11.125)*EASING_C5)) / 2 +1;
		}
	}
}

// Bounce
double easeOutBounce(double x) {
	if (x < (1/EASING_D1)) return EASING_N1 * x * x;
	else if (x < (2 / EASING_D1)){
		x -= 1.5 / EASING_D1;
		return EASING_N1 * x *x + 0.75;
	}
	else if (x < (2.5 / EASING_D1)){
		x -= 2.25 / EASING_D1;
		return EASING_N1 * x * x + 0.9375;
	}
	else {
		x -= 2.625 / EASING_D1;
		return EASING_N1 * x * x + 0.984375;
	}
}
double easeInBounce(double x) {
	return 1 - easeOutBounce(1-x);
}
double easeInOutBounce(double x) {
	if (x < 0.5) return (1-easeOutBounce(1-2*x)) / 2;
	else return (1+easeOutBounce(2*x-1))/2;
}
