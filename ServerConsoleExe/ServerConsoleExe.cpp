#include "PrecompileHeader.h"

int main()
{
	std::cout << "Create Server...\n";
	ServerCore MainCore;
	
	std::cout << "Init Server...\n";
	std::cout << "Write PortNumber : ";
	
	int PortNumber = 0;
	
	while (49152 > PortNumber || 65536 < PortNumber)
	{
		std::cin >> PortNumber;
	
		if (49152 <= PortNumber && 65536 >= PortNumber)
		{
			break;
		}
	
		std::cout << "Is Not Valid Port Number... Please Retry...\n";
	}
	
	MainCore.Initialize(static_cast<USHORT>(PortNumber));
	
	Sleep(100);
	system("cls");
	
	while (false == MainCore.IsCloseServer())
	{
		MainCore.Update();
	}

	return 0;
}