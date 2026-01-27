#include "testo.h"

int main(){
TESTO_Struct app = createTESTO("Example", 700, 500);
initTESTO(&app);
runTESTO(&app);
clearTESTO(&app);
return 0;
}
