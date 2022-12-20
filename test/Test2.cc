#include <gtest/gtest.h>

#include <windows.h>
#include "opccomn.h"
#include "OpcEnum.h"
#include <stdio.h>

void test_func()
{
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    CLSID server_id = { 0 };
    CLSIDFromProgID(L"Kepserver", &server_id);

    printf("%d\n", server_id.Data1);

    IOPCCommon *server;
    HRESULT result = CoCreateInstance(
        server_id,
        nullptr,
        CLSCTX_ALL,
        IID_IOPCCommon,
        (LPVOID*)&server);

    if (!SUCCEEDED(result))
    {
        printf("Failed to create Kepserver: %x\n",  result);
        return;
    }
    LCID locale_id = { 0 };
    HRESULT locale_result = IOPCCommon_GetLocaleID(server, &locale_id);

    if (!SUCCEEDED(locale_result))
    {
        printf("Failed to get Locale");
        return;
    }

    printf("%d\n", locale_id);

    DWORD count = 0;
    LCID *lcids;
    HRESULT queryLocaleResult = IOPCCommon_QueryAvailableLocaleIDs(server, &count, &lcids);

    printf("List all LCIDs");
    for (int i = 0; i < count ; i++) {

        printf("%x", LANGIDFROMLCID(lcids[i]));
    }
}

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  test_func();
}
