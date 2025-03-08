// Client.cpp
//#include <windows.h>
#include <iostream>

int main()
{
    HANDLE hPipe;
    char buffer[1024];
    DWORD dwWritten, dwRead;

    // Connect to named pipe
    hPipe = CreateFile("\\\\.\\pipe\\MyPipe", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    // Write data to server
    const char *message = "Hello from client";
    WriteFile(hPipe, message, strlen(message), &dwWritten, NULL);

    // Read response from server
    ReadFile(hPipe, buffer, sizeof(buffer), &dwRead, NULL);
    buffer[dwRead] = '\0';

    std::cout << "Server response: " << buffer << std::endl;

    // Close the pipe handle
    CloseHandle(hPipe);

    return 0;
}
