#include "kernel.h"
#include "kernelStuff/memory/memory.h"
#include "kernelStuff/stuff/kernelInit.h"
#include "osData/MStack/MStackM.h"
#include "interrupts/panic.h"
#include "elf/elf.h"
#include "devices/serial/serial.h"
#include "devices/pit/pit.h"

#include <libm/list/list.h>
#include "memory/heap.h"
#include "scheduler/scheduler.h"


void boot(void* _bootInfo)
{
    BootInfo* bootInfo = (BootInfo*)_bootInfo;

    osData.NO_INTERRUPTS = false;
    osData.booting = false;
    osData.maxNonFatalCrashCount = 5;
    MStackData::stackPointer = 0;
    for (int i = 0; i < 1000; i++)
        MStackData::stackArr[i] = MStack();

    osData.enableStackTrace = RECORD_STACK_TRACE;
    MStackData::BenchmarkEnabled = true;
    AddToStack();
    osData.crashCount = 0;
    //
    //while(true);
    osData.booting = true;
    osData.verboseBoot = true;

    PrintAll = true;
    
    InitKernel(bootInfo);

    //GlobalRenderer->Clear(Colors.black);
    
    Scheduler::SchedulerEnabled = false;

    {
        uint8_t* data = (uint8_t*)bootInfo->nothingDoer->fileData;
        Serial::Writelnf("data: %x", data);

        Elf::LoadedElfFile file = Elf::LoadElf(data);
        if (!file.works)
            Panic("FILE NO WORK :(", true);

        Scheduler::AddElf(file, 0, NULL, false);
        Serial::Writelnf("> ADDED NOTHING DOER");
    }

    // {
    //     uint8_t* data = (uint8_t*)bootInfo->testModule->fileData;
    //     Serial::Writelnf("data: %x", data);

    //     Elf::LoadedElfFile file = Elf::LoadElf(data);
    //     if (!file.works)
    //         Panic("FILE NO WORK :(", true);

    //     Scheduler::AddElf(file, 1234, NULL, false);
    //     Serial::Writelnf("> ADDED MODULE 1");
    // }

    {
        uint8_t* data = (uint8_t*)bootInfo->testModule->fileData;
        Serial::Writelnf("data: %x", data);

        Elf::LoadedElfFile file = Elf::LoadElf(data);
        if (!file.works)
            Panic("FILE NO WORK :(", true);

        Scheduler::AddElf(file, 12345678, NULL, true);
        Serial::Writelnf("> ADDED MODULE 2");
    }

    //bootInfo->smpData->cpus[1]->goto_address;

    // GlobalRenderer->Clear(Colors.bred);

    // PIT::Sleep(1000);
    
    // GlobalRenderer->Clear(Colors.black);


    Scheduler::SchedulerEnabled = true;

    while (true);
}


 
void bootTest(Framebuffer fb, ACPI::RSDP2* rsdp, PSF1_FONT* psf1_font, MaslOsAssetStruct* assets, void* freeMemStart, void* extraMemStart, uint64_t freeMemSize, void* kernelStart, uint64_t kernelSize, void* kernelStartV, limineSmpResponse* smpData)
{
    //MStackData::BenchmarkEnabled = false;
    BootInfo tempBootInfo;
    tempBootInfo.framebuffer = &fb;
    tempBootInfo.rsdp = rsdp;

    tempBootInfo.psf1_font = psf1_font;

    tempBootInfo.testImage = assets->testImage;
    tempBootInfo.bootImage = assets->bootImage;
    tempBootInfo.MButton = assets->MButton;
    tempBootInfo.MButtonS = assets->MButtonS;
    tempBootInfo.bgImage = assets->bgImage;
    tempBootInfo.maabZIP = assets->maabZIP;
    tempBootInfo.otherZIP = assets->otherZIP;

    tempBootInfo.mouseZIP = assets->mouseZIP;
    tempBootInfo.windowButtonZIP = assets->windowButtonZIP;
    tempBootInfo.windowIconsZIP = assets->windowIconsZIP;

    tempBootInfo.testModule = assets->testModule;
    tempBootInfo.nothingDoer = assets->nothingDoer;

    tempBootInfo.mMapStart = freeMemStart;
    tempBootInfo.m2MapStart = extraMemStart;
    tempBootInfo.mMapSize = freeMemSize;
    
    tempBootInfo.kernelStart = kernelStart;
    tempBootInfo.kernelSize = kernelSize;
    tempBootInfo.kernelStartV = kernelStartV;

    tempBootInfo.smpData = smpData;

    for (int y = 0; y < 100; y++)
        for (int x = 500; x < 600; x++)
            *(uint32_t*)((uint64_t)fb.BaseAddress + 4 * (x + y * fb.PixelsPerScanLine)) = (Colors.yellow * ((x + y + 1) % 2)) + (Colors.green * ((x + y) % 2));

    //while (true);

    
    boot(&tempBootInfo);
    return;
}
