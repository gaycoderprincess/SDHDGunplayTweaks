#include <windows.h>
#include "toml++/toml.hpp"
#include "nya_commonhooklib.h"

#include "game.h"

bool IsPlayerWieldingShotgun(UFG::AimingPlayerComponent* pThis) {
	if (!pThis) return false;

	auto pTargetingSystem = pThis->m_pTargetingSystemPedBaseComponent.m_pSimComponent;
	if (!pTargetingSystem) return false;

	auto pWeaponProperties = pTargetingSystem->m_pEquippedSOWPC.m_pPointer;
	if (!pWeaponProperties) return false;

	auto pFireMode = pWeaponProperties->mWeaponTypeInfo->mFireModes[pWeaponProperties->mFireMode];
	if (!pFireMode) return false;

	return pFireMode->mSimObjectWeaponType == 8;
}

auto updateAccuracy_OrigAddress = (void(__fastcall*)(UFG::AimingPlayerComponent*, const float))(NyaHookLib::mEXEBase + 0x56E9B0);
void __fastcall updateAccuracyPatch(UFG::AimingPlayerComponent* pThis, const float fDeltaS) {
	pThis->m_fOverrideReticleSize = IsPlayerWieldingShotgun(pThis) ? -1.0 : 0.0;
	updateAccuracy_OrigAddress(pThis, fDeltaS);
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
	static bool bInitialized = false;
	if (bInitialized) return TRUE;
	bInitialized = true;

	switch( fdwReason ) {
		case DLL_PROCESS_ATTACH: {
			if (NyaHookLib::GetEntryPoint() != 0x12BA5B4) {
				MessageBoxA(nullptr, "Unsupported game version! Make sure you're using the latest Steam release (.exe size of 37490688 bytes)", "nya?!~", MB_ICONERROR);
				return TRUE;
			}

			auto config = toml::parse_file("SDHDGunplayTweaks_gcp.toml");
			bool bNoAutoAim = config["main"]["disable_autoaim"].value_or(true);
			bool bAccurateWeapons = config["main"]["accurate_weapons"].value_or(true);
			bool bNoSteerDeadzone = config["extras"]["no_steering_deadzone"].value_or(false);

			if (bNoAutoAim) {
				NyaHookLib::Patch<uint16_t>(NyaHookLib::mEXEBase + 0x57880C, 0x9090); // UFG::AimingPlayerComponent::updateSoftLockOffset
			}

			if (bAccurateWeapons) {
				// UFG::AimingPlayerComponent::updateAccuracy, unrelated but useful to already have a ptr to AimingPlayerComponent :3
				updateAccuracy_OrigAddress = (void (__fastcall*)(UFG::AimingPlayerComponent *,
													   const float)) NyaHookLib::ReadRelative(NyaHookLib::mEXEBase + 0x5590EC + 1);
				NyaHookLib::PatchRelative(NyaHookLib::JMP, NyaHookLib::mEXEBase + 0x5590EC, &updateAccuracyPatch);
			}

			if (bNoSteerDeadzone) {
				// UFG::VehicleAnalogDriverInput::calcSteeringInput
				NyaHookLib::Patch<uint16_t>(NyaHookLib::mEXEBase + 0x484287, 0x9090);
				NyaHookLib::Patch<uint8_t>(NyaHookLib::mEXEBase + 0x4842A3, 0xEB);
			}
		} break;
		default:
			break;
	}
	return TRUE;
}