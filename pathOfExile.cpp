#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <memoryapi.h>
#include <libloaderapi.h>

void sendKeys(WORD kbButton){

  INPUT inputs[2] = {};

  inputs[0].type = INPUT_KEYBOARD;
  inputs[0].ki.wVk = kbButton;

  inputs[1].type = INPUT_KEYBOARD;
  inputs[1].ki.wVk = kbButton;
  inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

  SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}

HMODULE getProcessModule(DWORD lpProcessId, LPCSTR lpModule){

  HMODULE hResult = NULL;
  HANDLE hSnapshot;
  MODULEENTRY32 me32;

  hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, lpProcessId);

  if (hSnapshot != INVALID_HANDLE_VALUE)
  {
      me32.dwSize = sizeof(MODULEENTRY32);
      if (Module32First(hSnapshot, &me32))
      {
          do
          {
              if (!stricmp(me32.szModule, lpModule))
              {
                  hResult = me32.hModule;
                  break;
              }
          }
          while (Module32Next(hSnapshot, &me32));
      }
      CloseHandle(hSnapshot);
  }

  return hResult;
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

void checkValue(HANDLE handleProcess, long long baseAddress, DWORD procId){

  LPMODULEINFO lpmodinfo;
  
  HMODULE hModule = getProcessModule(procId, "ReShade64.dll");
  //bool GetModuleInformation(handleProcess, hModule, &lpmodinfo, sizeof(lpmodinfo));

  std::cout << "-----------------" << "\n";
  std::cout << "HMODULE " << hModule << "\n";
  std::cout << "LPMODULEINFO " << lpmodinfo << "\n";
  std::cout << "-----------------" << "\n";

  // offset pointer to dynamic es ReShade64.dll
  long long esOffset1 = 0x50;
  long long esOffset2 = 0x48;
  long long esOffset3 = 0x68;
  long long esOffset4 = 0x270;
  long long esOffset5 = 0x40;
  long long esOffset6 = 0x0;
  long long esOffset7 = 0x20C;
  long long esBasePointer = 0x02BDB1A8;

  // offset pointer to dynamic mp
  long long mpOffset1 = 0x88;
  long long mpOffset2 = 0x28;
  long long mpOffset3 = 0x40;
  long long mpOffset4 = 0x10;
  long long mpOffset5 = 0x218;
  long long mpOffset6 = 0x0;
  long long mpOffset7 = 0x988;
  long long mpBasePointer = 0x02BDB1A8;

  // offset pointer to dynamic hp
  long long hpOffset1 = 0x58;
  long long hpOffset2 = 0xE0;
  long long hpOffset3 = 0x80;
  long long hpOffset4 = 0x250;
  long long hpOffset5 = 0x10;
  long long hpOffset6 = 0x40;
  long long hpOffset7 = 0xB80;
  long long hpBasePointer = 0x02BDB1A8;

  
  long long hpBaseAddr = 0x1E153040B10; // target first addres
  long long mpBaseAddr = 0x1E153040B10; // target first addres
  long long esBaseAddr = 0x1E153040B10; // target first addres
  

  std::cout << "hpBaseAddr " << hpBaseAddr << "\n";
  std::cout << "mpBaseAddr " << mpBaseAddr << "\n";
  std::cout << "esBaseAddr " << esBaseAddr << "\n";
  std::cout << "baseAddress " << baseAddress << "\n";

  Sleep(5000);

  for (;;){

    unsigned int currentHp = getLastPointer(baseAddress,hpOffset1,hpOffset2,hpOffset3,hpOffset4,hpOffset5,hpOffset6,hpOffset7, handleProcess);
    unsigned int currentMp = getLastPointer(baseAddress,mpOffset1,mpOffset2,mpOffset3,mpOffset4,mpOffset5,mpOffset6,mpOffset7, handleProcess);
    unsigned int currentEs = getLastPointer(baseAddress,esOffset1,esOffset2,esOffset3,esOffset4,esOffset5,esOffset6,esOffset7, handleProcess);

    std::cout << "-----------------" << "\n";
    std::cout << "Dynamic HP Value: " << currentHp << "\n";
    std::cout << "Dynamic MP Value: " << currentMp << "\n";
    std::cout << "Dynamic ES Value: " << currentEs << "\n";
    std::cout << "-----------------" << "\n";
  
    if (currentHp < (150.0F / 100.0F * 50)){
      sendKeys(VK_F1);
      std::cout << "LOW HP" << currentHp << "\n";
    }

    if (currentMp < (129.0F / 100.0F * 50)){
      sendKeys(VK_F2);
      std::cout << "LOW MP" << currentHp << "\n";
    }

    Sleep(100);
    system("cls");
  }

}

int main()
{

  long long baseAddress{ };

  std::cout << "BaseAddress 0x1E1... convert to long int -> 2067272043280" << "\n";
  std::cin >> baseAddress;
  std::cout << "BaseAddress: " << baseAddress << "\n";

  HWND hwnd = getWindowProcess((LPSTR)"Path of Exile");

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
    checkValue(handleProcess, baseAddress, procId);
  }

}