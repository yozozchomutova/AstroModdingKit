/* 
* Script for experimenting and manipulating with voxel functions (Biome weight, Height). Currently configured for Terran Forests and Terran Mountains. 
* Made for: UE4SS
*/

#include <stdio.h>
#include <Mod/CppUserModBase.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Windows.h>
#include <cinttypes>
#include <UE4SSProgram.hpp>

using namespace RC;
using namespace RC::Unreal;

class HorizontalTerranBiomes : public RC::CppUserModBase
{

public:
    uintptr_t entry_mountains_height;
    uintptr_t entry_mountains_biome_weight;

    HorizontalTerranBiomes() : CppUserModBase()
    {
        ModName = STR("HorizontalTerranBiomes");
        ModVersion = STR("1.0");
        ModDescription = STR("ABC");
        ModAuthors = STR("Yzch");
    }

    ~HorizontalTerranBiomes() override
    {

    }

    void DumpBytes(uintptr_t addr, size_t count)
    {
        wchar_t buffer[256] = { 0 };
        wchar_t* p = buffer;

        for (size_t i = 0; i < count; i++)
        {
            unsigned char byte = *(unsigned char*)(addr + i);
            p += swprintf(p, 256 - (p - buffer), L"%02X ", byte);
        }

        Output::send<LogLevel::Verbose>(STR("{}\n"), buffer);
    }

    static void MyFunction()
    {
        Output::send<LogLevel::Verbose>(STR("Hooked!"));
        return;
    }

    void PatchXMM0(uintptr_t src, uintptr_t dst, bool is64bit, BYTE byt)
    {
        const int patchSize = 6;
        DWORD oldProtect;
        VirtualProtect((void*)src, patchSize, PAGE_EXECUTE_READWRITE, &oldProtect);

        BYTE patch[patchSize];

        // FF 25 00 00 00 00  -> JMP [RIP+0]
        patch[0] = is64bit ? 0x41 : 0x90;
        patch[1] = 0x0F;
        patch[2] = 0x28;
        patch[3] = byt;
        patch[4] = 0xC3;
        patch[5] = 0x90;

        // absolute address follows
        //*(void**)(patch + 6) = (void*) dst;

        memcpy((void*)src, patch, patchSize);
        VirtualProtect((void*)src, patchSize, oldProtect, &oldProtect);
        FlushInstructionCache(GetCurrentProcess(), (void*)src, patchSize);
    }

    void PatchJMP(uintptr_t src, BYTE registry, bool x8_16, float vector4[])
    {
        const int patchSize = 47;
        DWORD oldProtect;
        BYTE INSTR1 = x8_16 ? 0x66 : 0x90;
        BYTE INSTR2 = x8_16 ? 0x44 : 0x66;

        VirtualProtect((void*)src, patchSize, PAGE_EXECUTE_READWRITE, &oldProtect);

        // Initialize your patch array with the constant opcodes and placeholder slots
        BYTE patch[patchSize] = {
            // --- LANE 0 ---
            0xB8, 0x00, 0x00, 0x00, 0x00,       // mov eax, [Float 1 Placeholder]
            INSTR1, INSTR2, 0x0F, 0x6E, registry,             // movd xmm0, eax

            // --- LANE 1 ---
            0xB8, 0x00, 0x00, 0x00, 0x00,       // mov eax, [Float 2 Placeholder]
            INSTR1, INSTR2, 0x0F, 0x3A, 0x22, registry, 0x01, // pinsrd xmm0, eax, 1

            // --- LANE 2 ---
            0xB8, 0x00, 0x00, 0x00, 0x00,       // mov eax, [Float 3 Placeholder]
            INSTR1, INSTR2, 0x0F, 0x3A, 0x22, registry, 0x02, // pinsrd xmm0, eax, 2

            // --- LANE 3 ---
            0xB8, 0x00, 0x00, 0x00, 0x00,       // mov eax, [Float 4 Placeholder]
            INSTR1, INSTR2, 0x0F, 0x3A, 0x22, registry, 0x03,  // pinsrd xmm0, eax, 3
            0xC3
        };

        // Copy each float directly into its exact destination slot inside the patch array
        std::memcpy(&patch[1], &vector4[0], 4);
        std::memcpy(&patch[11], &vector4[1], 4);
        std::memcpy(&patch[23], &vector4[2], 4);
        std::memcpy(&patch[35], &vector4[3], 4);

        memcpy((void*)src, patch, patchSize);
        VirtualProtect((void*)src, patchSize, oldProtect, &oldProtect);
        FlushInstructionCache(GetCurrentProcess(), (void*)src, patchSize);
    }

    auto on_unreal_init() -> void override
    {
        static float BWXMM0[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        static float BWXMM1[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        static float BWXMM2[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        static float BWXMM3[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        static float BWXMM4[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        static float BWXMM5[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        static float BWXMM6[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        static float BWXMM7[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        static float BWXMM8[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        static float BWXMM9[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        static float BWXMM10[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        static float BWXMM11[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        static float BWXMM12[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        static float BWXMM13[4] = { 0.5f, 0.4f, 0.3f, 0.2f };
        static float BWXMM14[4] = { 0.51f, 0.41f, 0.31f, 0.19f };
        static float BWXMM15[4] = { 0.5f, 0.4f, 0.3f, 0.2f };
        static float HXMM0[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

        UE4SS_ENABLE_IMGUI()
        Output::send<LogLevel::Verbose>(STR("HorizontalTerranBiomes says hello\n"));

        uintptr_t base = (uintptr_t)GetModuleHandleW(nullptr);
        uintptr_t entry_forests_biome_weight = base + 0x96B480;
        entry_mountains_height = base + 0x967AD0;
        entry_mountains_biome_weight = base + 0x9673A0;

        wchar_t formatted[256];
        swprintf(formatted, 256, L"Target Address: 0x%" PRIxPTR "\n", entry_forests_biome_weight);
        Output::send<LogLevel::Verbose>(STR("{}\n"), formatted);
        //DumpBytes(target, 10);
        
        // GUI Tab
        register_tab(STR("MountainBiomesTest"), [](CppUserModBase* instance) {
            auto mod = dynamic_cast<HorizontalTerranBiomes*>(instance);
            if (!mod)
            {
                return;
            }

            ImGui::InputFloat4("BW: XMM0", BWXMM0, "%.3f");
            ImGui::InputFloat4("BW: XMM1", BWXMM1, "%.3f");
            ImGui::InputFloat4("BW: XMM2", BWXMM2, "%.3f");
            ImGui::InputFloat4("BW: XMM3", BWXMM3, "%.3f");
            ImGui::InputFloat4("BW: XMM4", BWXMM4, "%.3f");
            ImGui::InputFloat4("BW: XMM5", BWXMM5, "%.3f");
            ImGui::InputFloat4("BW: XMM6", BWXMM6, "%.3f");
            ImGui::InputFloat4("BW: XMM7", BWXMM7, "%.3f");
            ImGui::InputFloat4("BW: XMM8", BWXMM8, "%.3f");
            ImGui::InputFloat4("BW: XMM9", BWXMM9, "%.3f");
            ImGui::InputFloat4("BW: XMM10", BWXMM10, "%.3f");
            ImGui::InputFloat4("BW: XMM11", BWXMM11, "%.3f");
            ImGui::InputFloat4("BW: XMM12", BWXMM12, "%.3f");
            ImGui::InputFloat4("BW: XMM13", BWXMM13, "%.3f");
            ImGui::InputFloat4("BW: XMM14", BWXMM14, "%.3f");
            ImGui::InputFloat4("BW: XMM15", BWXMM15, "%.3f");
            ImGui::InputFloat4("H: XMM0", HXMM0, "%.3f");
            if (ImGui::Button("Patch")) {
                mod->PatchJMP(mod->entry_mountains_biome_weight + 46 * 0, 0xC0, false, BWXMM0); // Weight?
                mod->PatchJMP(mod->entry_mountains_biome_weight + 46 * 1, 0xC8, false, BWXMM1); // Full sphere
                mod->PatchJMP(mod->entry_mountains_biome_weight + 46 * 2, 0xD0, false, BWXMM2); // Full sphere
                mod->PatchJMP(mod->entry_mountains_biome_weight + 46 * 3, 0xD8, false, BWXMM3); // Full sphere
                mod->PatchJMP(mod->entry_mountains_biome_weight + 46 * 4, 0xE0, false, BWXMM4); // Pozitive Z - Smooth
                mod->PatchJMP(mod->entry_mountains_biome_weight + 46 * 5, 0xE8, false, BWXMM5); // Pozitive Y - Smooth
                mod->PatchJMP(mod->entry_mountains_biome_weight + 46 * 6, 0xF0, false, BWXMM6); // Pozitive X - Smooth
                mod->PatchJMP(mod->entry_mountains_biome_weight + 46 * 7, 0xF8, false, BWXMM7);
                mod->PatchJMP(mod->entry_mountains_biome_weight + 46 * 8, 0xC0, true, BWXMM8); // POZITIVE Y (SMOOTH but HARD EDGES)
                mod->PatchJMP(mod->entry_mountains_biome_weight + 46 * 9, 0xC8, true, BWXMM9);
                mod->PatchJMP(mod->entry_mountains_biome_weight + 46 * 10, 0xD0, true, BWXMM10); // Biome priority over other biomes?
                mod->PatchJMP(mod->entry_mountains_biome_weight + 46 * 11, 0xD8, true, BWXMM11); // Pozitive Z - Cutted/Zebra
                mod->PatchJMP(mod->entry_mountains_biome_weight + 46 * 12, 0xE0, true, BWXMM12); // Pozitive X - Cutted/Zebra
                mod->PatchJMP(mod->entry_mountains_biome_weight + 46 * 13, 0xE8, true, BWXMM13); // Full sphere
                mod->PatchJMP(mod->entry_mountains_biome_weight + 46 * 14, 0xF0, true, BWXMM14); // Pozitive Z - Cutted/Zebra
                //mod->PatchJMP(mod->entry_mountains_biome_weight + 46 * 15, 0xF8, true, BWXMM15); // Pozitive Z smooth
                mod->PatchJMP(mod->entry_mountains_height, 0xC0, false, HXMM0);
                //mod->PatchJMP(mod->entry_mountains_height, 0xC8, HXMM1);
                Output::send<LogLevel::Verbose>(STR("HorizontalTerranBiomes Patched!\n"));
            }
            });
    }

    bool keyPressed_U = false;
    bool keyPressed_I = false;
    int index = 0;
    BYTE options[16] = {0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7};
    auto on_update() -> void override
    {
        // U pressed
        if (GetKeyState('U') & 0x8000)
        {
            if (!keyPressed_U) {
                index = min(index+1, 15);
                wchar_t formatted[256];
                swprintf(formatted, 256, L"U Pressed, index: %d\n", index);
                Output::send<LogLevel::Verbose>(STR("U pressed, index: {}\n"), formatted);
                PatchXMM0(entry_mountains_biome_weight, reinterpret_cast<std::uintptr_t>(MyFunction), index >= 7, options[index]);
            }
            keyPressed_U = true;
        }
        else {
            keyPressed_U = false;
        }

        // I pressed
        if (GetKeyState('I') & 0x8000)
        {
            if (!keyPressed_I) {
                index = max(index - 1, 0);
                wchar_t formatted[256];
                swprintf(formatted, 256, L"I Pressed, index: %d\n", index);
                Output::send<LogLevel::Verbose>(STR("I pressed, index: {}\n"), formatted);
                PatchXMM0(entry_mountains_biome_weight, reinterpret_cast<std::uintptr_t>(MyFunction), index >= 7, options[index]);
            }
            keyPressed_I = true;
        }
        else {
            keyPressed_I = false;
        }
    }

    void PatchMemory(void* address, const void* data, size_t size)
    {
        DWORD oldProtect;
        VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect);
        memcpy(address, data, size);
        VirtualProtect(address, size, oldProtect, &oldProtect);
        FlushInstructionCache(GetCurrentProcess(), address, size);
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
