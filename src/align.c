#include "align.h"


int ratioInterpolate(double ratio, int fromNumber, int toNumber){
return (int)(fromNumber + ratio*(toNumber-fromNumber));
}

double doubleInterpolate(double ratio, double fromNumber, double toNumber){
return (double)(fromNumber + ratio*(toNumber-fromNumber));
}
