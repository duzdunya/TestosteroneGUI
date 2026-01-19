#include "colors.h"


char myHexCodes[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void rgbToHex(MYRGB rgb, char hex[7]){
	hex[0] = '#';
	int rgbValues[3] = {rgb.r, rgb.g, rgb.b};
	for (int i=0; i<3; i++){

		int firstIndex = i*2+1;
		int secondIndex = firstIndex + 1; 

		int floorInt = floor(rgbValues[i]/16.0);
		if (floorInt > 15){
			fprintf(stderr,"Error, given number is greater than 255\n");
			break;
		}
		int remainInt = rgbValues[i]-(floorInt*16);

		char selectedFirst = myHexCodes[floorInt];
		char selectedSecond = myHexCodes[remainInt];

//		printf("%d\n",i);
//		printf("%d %d\n",floorInt,remainInt);
//		printf("%c %c\n",selectedFirst,selectedSecond);
		hex[firstIndex] = selectedFirst;
		hex[secondIndex] = selectedSecond;

	}
} 
