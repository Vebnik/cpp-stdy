#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <memoryapi.h>
#pragma comment(lib, "user32")

void sendKeys(){

  INPUT inputs[2] = {};

  inputs[0].type = INPUT_KEYBOARD;
  inputs[0].ki.wVk = VK_SPACE;

  inputs[1].type = INPUT_KEYBOARD;
  inputs[1].ki.wVk = VK_SPACE;
  inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

  SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}

HWND getWindowProcess(LPSTR processName){
  return FindWindowA(NULL, processName);
}

long long getLastPointer(long long baseAddr, long long offset1, long long offset2, long long offset3, long long offset4, long long offset5, long long offset6, long long offset7, HANDLE handleProcess){

  long long nextAddr1 = 0x0;
  long long nextAddr2 = 0x0;
  long long nextAddr3 = 0x0;
  long long nextAddr4 = 0x0;
  long long nextAddr5 = 0x0;
  long long nextAddr6 = 0x0;
  long long nextAddr7 = 0x0;

  long long needAddr = 0x0;

  long long nextVal1 = 0x0;
  long long nextVal2 = 0x0;
  long long nextVal3 = 0x0;
  long long nextVal4 = 0x0;
  long long nextVal5 = 0x0;
  long long nextVal6 = 0x0;
  long long nextVal7 = 0x0;

  nextAddr1 = baseAddr + offset1;

  long long nextVal = 0;

  ReadProcessMemory(handleProcess, (PBYTE *)nextAddr1, &nextVal1, sizeof(nextAddr1), 0);
  nextAddr2 = nextVal1 + offset2;
  
  ReadProcessMemory(handleProcess, (PBYTE *)nextAddr2, &nextVal2, sizeof(nextAddr1), 0);
  nextAddr3 = nextVal2 + offset3;

  ReadProcessMemory(handleProcess, (PBYTE *)nextAddr3, &nextVal3, sizeof(nextAddr1), 0);
  nextAddr4 = nextVal3 + offset4;

  ReadProcessMemory(handleProcess, (PBYTE *)nextAddr4, &nextVal4, sizeof(nextAddr1), 0);
  nextAddr5 = nextVal4 + offset5;

  ReadProcessMemory(handleProcess, (PBYTE *)nextAddr5, &nextVal5, sizeof(nextAddr1), 0);
  nextAddr6 = nextVal5 + offset6;

  ReadProcessMemory(handleProcess, (PBYTE *)nextAddr6, &nextVal6, sizeof(nextAddr1), 0);
  nextAddr7 = nextVal6 + offset7;

  ReadProcessMemory(handleProcess, (PBYTE *)nextAddr7, &nextVal7, sizeof(nextAddr1), 0);

  return nextVal7;
}

void checkValue(HANDLE handleProcess){

  LPVOID addr = VirtualAllocEx(handleProcess, NULL, strlen("F:\\games\\SteamLibrary\\steamapps\\common\\Path of Exile\\PathOfExileSteam.exe"), MEM_COMMIT, PAGE_EXECUTE_READWRITE);

  std::cout << "Target process adderss " << addr << "\n";

  // offset pointer to dynamic hp
  long long offset1 = 0x58;
  long long offset2 = 0xE0;
  long long offset3 = 0x80;
  long long offset4 = 0x250;
  long long offset5 = 0x10;
  long long offset6 = 0x40;
  long long offset7 = 0xB80;
  long long basePointer = 0x02BDB1A8;

  long long baseAddrTest = 0x00400000 + basePointer;

  long long baseAddr = 0x1C1EDA6C990; // target first addres
  
  std::cout << "baseAddrTest " << baseAddrTest << "\n";

  int cnt = 5;

  for (int i = 0; i < cnt; i){

    unsigned int currentHp = getLastPointer(baseAddr,offset1,offset2,offset3,offset4,offset5,offset6,offset7, handleProcess);

    std::cout << "Dynamic HP Value: " << currentHp << "\n";

    if (currentHp < (150.0F / 100.0F * 50)){
      
      sendKeys();
      std::cout << "LOW HP" << currentHp << "\n";
    }

    Sleep(1000);
  }
    
}

int main()
{

  HWND hwnd = getWindowProcess("Path of Exile");

  if (hwnd == NULL) {
    std::cout << "Not found process" << "\n";
    return 0;
  }
    
  DWORD procId;
  GetWindowThreadProcessId(hwnd, &procId);

  HANDLE handleProcess = OpenProcess(PROCESS_ALL_ACCESS, false, procId);

  if (procId == NULL) {
    std::cout << "Not found process" << "\n";
    return 0;
  } else {
    std::cout << "Found process" << "\n";
    checkValue(handleProcess);
  }

}