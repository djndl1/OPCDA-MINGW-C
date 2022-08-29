#include "opccomn.h"
#include "OpcEnum.h"

#include <windows.h>
#include <objbase.h>

#include <iostream>

using std::cout;
using std::endl;

extern "C"
int wmain(int argc, wchar_t* argv[])
{
    ::CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    CLSID server_id = { 0 };
    ::CLSIDFromProgID(L"Kepserver", &server_id);

    std::cout << server_id.Data1 << std::endl;

    IOPCCommon *server;
    HRESULT result = ::CoCreateInstance(
        server_id, 
        nullptr, 
        CLSCTX_ALL, 
        IID_IOPCCommon, 
        (LPVOID*)&server);

    if (!SUCCEEDED(result))
    {
        std::cout << "Failed to create Kepserver: " << std::hex << result << std::dec << '\n';


        return 1;
    }
    LCID locale_id = { 0 };
    HRESULT locale_result = server->GetLocaleID(&locale_id);

    if (!SUCCEEDED(locale_result))
    {
        std::cout << "Failed to get Locale" << '\n';
        return 2;
    }

    std::cout << locale_id << std::endl;

    DWORD count = 0;
    LCID *lcids;
    HRESULT queryLocaleResult = server->QueryAvailableLocaleIDs(
        &count, &lcids);

    std::cout << "List all LCIDs" << '\n';
    for (int i = 0; i < count ; i++) {

        std::cout << std::hex <<  LANGIDFROMLCID(lcids[i]) << std::endl;
    }

    

    return 0;
}