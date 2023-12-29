#include <windows.h>
#include <stdio.h>

void PressKey(char ch) {
    SHORT vk = VkKeyScan(ch);
    WORD key = LOBYTE(vk);

    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;

    // Check if shift key needs to be pressed
    if (HIBYTE(vk) & 1) {
        keybd_event(VK_SHIFT, 0, 0, 0); // Press shift down
    }

    SendInput(1, &input, sizeof(INPUT)); // Key down

    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT)); // Key up

    if (HIBYTE(vk) & 1) {
        keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0); // Release shift
    }
}

int main() {
    // Simulate CTRL+R
    keybd_event(VK_LWIN, 0, 0, 0);
    keybd_event('R', 0, 0, 0);
    keybd_event('R', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);

    // Small delay to ensure the run dialog is open
    Sleep(500);

    // Type the command and press Enter
    const char* command = "cmd.exe /C whoami&pause";
    for (int i = 0; command[i] != '\0'; i++) {
        PressKey(command[i]);
    }

    PressKey(VK_RETURN);

    return 0;
}
