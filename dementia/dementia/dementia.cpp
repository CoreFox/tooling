#include "stdafx.h"
#include "iostream"
#include <sstream>
#include <windows.h>

using namespace std;

int main()
{
	HWND hwnd = FindWindowA(NULL, "AssaultCube");

	if (hwnd == NULL)
	{
		cout << "Cannot find window." << endl;
		Sleep(3000);
		exit(-1);
	}
	else
	{
		DWORD procID;
		GetWindowThreadProcessId(hwnd, &procID);
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

		if (procID == NULL)
		{
			cout << "Cannot obtain process." << endl;
			Sleep(3000);
			exit(-1);
		}
		else
		{		
			const DWORD sptr_player = 0x00509b74;			
			const DWORD ofs_armor = 0x0FC;
			const DWORD ofs_health = 0xF8;
			const DWORD ofs_ammo_rifle = 0x150;
			const DWORD ofs_ammo_granades = 0x158;
			const DWORD ofs_ammo_pistol = 0x13C;
			const DWORD ofs_ammo_dual_pistol = 0x15C;
			const DWORD ofs_rate_of_gun_fire = 0x178;
			const DWORD ofs_flag_shoot_gun = 0x224;

			DWORD adr_player;
			DWORD adr_armor;
			DWORD adr_health;
			DWORD adr_ammo_rifle;
			DWORD adr_ammo_granades;
			DWORD adr_ammo_pistol;
			DWORD adr_ammo_dual_dual;					
			DWORD adr_rate_of_gun_fire; 

			// rifle shot raises gun by 0.935111 
			// y = 0x044  (per shot do value at this offset - 0.935111)
			// x = 0x040			
			
				
			const int val_999 = 999;
			const int val_0 = 0;
			cout << "Dementia Enabled..." << endl;

			for (;;)
			{
				// read static pointer for player memory base address
				ReadProcessMemory(handle, (PBYTE*)sptr_player, &adr_player, sizeof(adr_player), 0);

				//get other player value addresses, by adding an offset to value from player static ptr (player address)
				adr_armor			= adr_player + ofs_armor;
				adr_health			= adr_player + ofs_health;
				adr_ammo_rifle		= adr_player + ofs_ammo_rifle;
				adr_ammo_granades	= adr_player + ofs_ammo_granades;
				adr_ammo_pistol		= adr_player + ofs_ammo_pistol;
				adr_ammo_dual_dual	= adr_player + ofs_ammo_dual_pistol;					
				
				//set address from above with certain values
				WriteProcessMemory(handle, (LPVOID)adr_ammo_rifle, &val_999, sizeof(val_999), 0);//.........ammo rifle 				
				WriteProcessMemory(handle, (LPVOID)adr_ammo_granades, &val_999, sizeof(val_999), 0);//......ammo granades 				
				WriteProcessMemory(handle, (LPVOID)adr_ammo_pistol, &val_999, sizeof(val_999), 0);//........ammo pistol				
				WriteProcessMemory(handle, (LPVOID)adr_ammo_dual_dual, &val_999, sizeof(val_999), 0);//.....ammo pistol dual
				WriteProcessMemory(handle, (LPVOID)adr_armor, &val_999, sizeof(val_999), 0);//..............armor
				WriteProcessMemory(handle, (LPVOID)adr_health, &val_999, sizeof(val_999), 0);//.............health								
				
				//Sleep(750);
			}
		}
	}

	return 0;
}
