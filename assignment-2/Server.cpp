// Server.cpp
//#include <windows.h>
#include <iostream>

int main()
{
    HANDLE hPipe;
    char buffer[1024];
    DWORD dwRead;

    // Create named pipe
    hPipe = CreateNamedPipe("\\\\.\\pipe\\MyPipe", PIPE_ACCESS_INBOUND, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 1, 0, 0, NMPWAIT_USE_DEFAULT_WAIT, NULL);

    // Wait for client to connect
    ConnectNamedPipe(hPipe, NULL);

    // Read data from client
    ReadFile(hPipe, buffer, sizeof(buffer), &dwRead, NULL);
    buffer[dwRead] = '\0';

    std::cout << "Received from client: " << buffer << std::endl;

    // Process data (you can add your logic here)

    // Send response back to client
    const char *response = "Message received successfully";
    WriteFile(hPipe, response, strlen(response), NULL, NULL);

    // Close the pipe handle
    CloseHandle(hPipe);

    return 0;
}
