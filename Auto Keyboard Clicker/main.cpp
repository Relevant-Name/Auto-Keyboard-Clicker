#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <string>
#include "timer.h"
#include <random>
using namespace std;

float lowTimeNum;
float highTimeNum;
char inputkey;

int main() {

	cout << "Enter key you want to type: ";
	cin >> inputkey;
	cout << "Enter time range interval (Low to High)\n" <<
		"Low: ";
	cin >> lowTimeNum;
	cout << "High: ";
	cin >> highTimeNum;
	cout << "'" << inputkey << "' will cast every " << lowTimeNum << " to " << highTimeNum << " seconds\n";
	lowTimeNum *= 1000; highTimeNum *= 1000;
	std::random_device                  rng;
	std::default_random_engine          prng{ rng() };
	std::uniform_int_distribution<int>  probability(lowTimeNum, highTimeNum);

	float between = probability(prng);
	HKL kbl = GetKeyboardLayout(0);
	int vk = VkKeyScanExA(inputkey, kbl);
	Timer<std::chrono::steady_clock> t;

	t.start();
	bool isgoing = false;
	cout << "Toggle with up arrow key to get started\n";

	while (true) {

		if (GetKeyState(VK_UP) & 0x8000) {
			cout << "Started \n";
			Sleep(300);
			while (true) {
				if (t.get_elapsed_ms().count() >= between) {
					INPUT ip;
					ip.type = INPUT_KEYBOARD;
					ip.ki.wVk = vk; //virtual key
					ip.ki.dwFlags = 0; // 0 for key press
					SendInput(1, &ip, sizeof(INPUT));
					ip.ki.dwFlags = KEYEVENTF_KEYUP;
					SendInput(1, &ip, sizeof(INPUT));
					cout << "Casted at " << between / 1000 << "\n";
					between = probability(prng);
					t.stop();
					t.start();
				}
				if (GetKeyState(VK_UP) & 0x8000) {
					cout << "Stopped \n";
					Sleep(300);
					break;
				}
				Sleep(1);
				double run_time = t.get_run_time_ms().count();
			}
			double run_time = t.get_run_time_ms().count();
			Sleep(1);
		}
		Sleep(1);
	}
	system("pause");
	return 0;
}