#include "easings.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    for (double i = 0.0; i < 1.0; i += 0.01) {

	easeInSine(i);
	easeOutSine(i);
	easeInOutSine(i);

	// Quad
	easeInQuad(i);
	easeOutQuad(i);
	easeInOutQuad(i);

	// Qubic
	easeInQubic(i);
	easeOutCubic(i);
	easeInOutCubic(i);

	// Quart
	easeInQuart(i);
	easeOutQuart(i);
	easeInOutQuart(i);

	// Quint
	easeInQuint(i);
	easeOutQuint(i);
	easeInOutQuint(i);

	// Expo
	easeInExpo(i);
	easeOutExpo(i);
	easeInOutExpo(i);

	// Circ

	easeInCirc(i);
	easeOutCirc(i);
	easeInOutCirc(i);

	// Back
	easeInBack(i);
	easeOutBack(i);
	easeInOutBack(i);

	// Elastic
	easeInElastic(i);
	easeOutElastic(i);
	easeInOutElastic(i);

	// Bounce
	easeOutBounce(i);
	easeInBounce(i);
	easeInOutBounce(i);
    }
	printf("Test run successfully\n");
    return EXIT_SUCCESS;
}
