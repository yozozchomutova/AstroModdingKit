#include <stdio.h>
#include <Mod/CppUserModBase.hpp>
#include <Windows.h>
#include <cinttypes>

using namespace RC;
using namespace RC::Unreal;

class HorizontalTerranBiomes : public RC::CppUserModBase
{

public:
    HorizontalTerranBiomes() : CppUserModBase()
    {
        ModName = STR("HorizontalTerranBiomes");
        ModVersion = STR("1.0.0");
        ModDescription = STR("ABC");
        ModAuthors = STR("Yzch");
    }

    ~HorizontalTerranBiomes() override
    {

    }

    // Launches once on UE4SS start
    auto on_unreal_init() -> void override
    {
        Output::send<LogLevel::Verbose>(STR("HorizontalTerranBiomes init.\n"));

        // Get addresses of functions (___ModuleEntryPoint_...)
        uintptr_t base = (uintptr_t)GetModuleHandleW(nullptr);
        uintptr_t entry_forests_biome_weight = base + 0x96B480;
        uintptr_t entry_mountains_biome_weight = base + 0x9673A0;

        // Print addresses in console
        wchar_t formatted[256];
        swprintf(formatted, 256, L"Forests: 0x%" PRIxPTR " | Mountains: 0x%" PRIXPTR "\n", entry_forests_biome_weight, entry_mountains_biome_weight);
        Output::send<LogLevel::Verbose>(STR("{}\n"), formatted);

        // Patch Mountains biome weight function
        const int patchSize = 256;
        BYTE patchBytes_mountains[patchSize] = {
            0x0F, 0x28, 0xC6,               // movasp xmm0, xmm6 (writes xmm6 (planet X vector) to the xmm0 (final weight value))

            0x66, 0x0f, 0x76, 0xc9,         // pcmpeqd xmm1,xmm1 (fill Xmm1 with 1's)
            0x66, 0x0f, 0x72, 0xd1, 0x01,   // psrld  xmm1,0x1 (bit shift right)
            0x0f, 0x54, 0xc1,               // andps  xmm0,xmm1 (something like ABS())

            0xC3                            // return
        };
        PatchASM(entry_mountains_biome_weight, patchBytes_mountains, patchSize);

        // Patch Forests biome weight function
        BYTE patchBytes_forests[patchSize] = {
            0x0F, 0x28, 0xC6,               // movasp xmm0, xmm6 (writes xmm6 (planet X vector) to the xmm0 (final weight value))

            0x66, 0x0f, 0x76, 0xc9,         // pcmpeqd xmm1,xmm1 (fill Xmm1 with 1's)
            0x66, 0x0f, 0x72, 0xd1, 0x01,   // psrld  xmm1,0x1 (byte shift)
            0x0f, 0x54, 0xc1,               // andps  xmm0,xmm1 (something like ABS())

            0xb8, 0x00, 0x00, 0x00, 0x40,   // mov    eax,0x40000000
            0x66, 0x0f, 0x6e, 0xc8,         // movd   xmm1,eax
            0x0f, 0xc6, 0xc9, 0x00,         // shufps xmm1,xmm1,0x0
            0x0f, 0x59, 0xc1,               // divps  xmm0,xmm1 (multiply by 2)

            0xC3                            // return
        };
        PatchASM(entry_forests_biome_weight, patchBytes_forests, patchSize);

        // Finish notice
        Output::send<LogLevel::Verbose>(STR("Patching finished\n"));
    }
    auto on_update() -> void override
    {

    }

    void PatchASM(uintptr_t address, BYTE patchBytes[], int patchSize) {
        DWORD oldProtect;
        VirtualProtect((void*)address, patchSize, PAGE_EXECUTE_READWRITE, &oldProtect);

        memcpy((void*)address, patchBytes, patchSize);
        VirtualProtect((void*)address, patchSize, oldProtect, &oldProtect);
        FlushInstructionCache(GetCurrentProcess(), (void*)address, patchSize);
    }
};

#define HORIZONTAL_TERRAN_BIOMES_API __declspec(dllexport)
extern "C"
{
    HORIZONTAL_TERRAN_BIOMES_API RC::CppUserModBase* start_mod()
    {
        return new HorizontalTerranBiomes();
    }

    HORIZONTAL_TERRAN_BIOMES_API void uninstall_mod(RC::CppUserModBase* mod)
    {
        delete mod;
    }
}
