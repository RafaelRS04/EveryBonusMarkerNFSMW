#include <windows.h>

#define EVERY_BONUS_MARKER 6

void WriteByteToMemory(DWORD address, BYTE byte) {
    DWORD oldProtection;

    VirtualProtect((LPVOID)address, sizeof byte, PAGE_EXECUTE_READWRITE, &oldProtection);

    *(PBYTE)address = byte;

    VirtualProtect((LPVOID)address, sizeof byte, oldProtection, &oldProtection);
}

void ModifyBonusMarkerCount() {
    /* Selectable Marker Count */
    WriteByteToMemory(0x7B3D7D, EVERY_BONUS_MARKER);

    /* Selectable Marker Count 2 */
    WriteByteToMemory(0x7B3E19, EVERY_BONUS_MARKER);

    /* Selections Remaining */
    WriteByteToMemory(0x7A7A3C, EVERY_BONUS_MARKER);

    /* You can now select X markers from Y (HUD) */
    WriteByteToMemory(0x7A7ABE, EVERY_BONUS_MARKER);
}

BOOL APIENTRY DllMain(HMODULE /* module */, DWORD  reason, LPVOID /* reserved */) {    
    if(reason == DLL_PROCESS_ATTACH) {
        ModifyBonusMarkerCount();
    }

    return TRUE;
}