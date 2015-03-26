
#include "App.h"
using namespace std;

//
const int width = 640; // ширина окна
const int height = 480; // высота окна






int main(int argc, char *argv[]){
    
    App::instance().init(width, height);
    App::instance().Run();
    App::instance().ShutDown();
    return 0;
}
//
//
//