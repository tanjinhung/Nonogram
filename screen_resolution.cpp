#include "windows.h"
#include <windows.h>
#include <iostream>

int main(int argc, char const *argv[])
{
    DEVMODE dm;
    dm.dmSize = sizeof(dm);
    for (int iModeNum = 0; EnumDisplaySettings(NULL, iModeNum, &dm) != 0; iModeNum++)
    {
        std::cout << "Mode #" << iModeNum << " = " << dm.dmPelsWidth << "x" << dm.dmPelsHeight << std::endl;
    }
    
    return 0;
}
