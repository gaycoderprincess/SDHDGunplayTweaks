namespace UFG {
	template<typename T>
	class RebindingComponentHandle {
	public:
		uint8_t _0[0x14];
		T* m_pSimComponent;
		uint8_t _20[0x10];
	};

	template<typename T>
	class qSafePointer {
	public:
		uint8_t _0[0x10];
		T* m_pPointer;
	};

	class FireModeInfo {
	public:
		int mSimObjectWeaponType;
	};

	class WeaponTypeInfo {
	public:
		uint8_t _0[0x8];
		FireModeInfo* mFireModes[2];
	};

	class SimObjectWeaponPropertiesComponent {
	public:
		uint8_t _0[0xAC];
		int mFireMode;
		WeaponTypeInfo* mWeaponTypeInfo;
	};

	class TargetingSystemPedBaseComponent {
	public:
		uint8_t _0[0x208];
		UFG::qSafePointer<UFG::SimObjectWeaponPropertiesComponent> m_pEquippedSOWPC;
	};

	class AimingPlayerComponent {
	public:
		uint8_t _0[0x110];
		RebindingComponentHandle<TargetingSystemPedBaseComponent> m_pTargetingSystemPedBaseComponent;
		uint8_t _140[0xB0];
		float m_fOverrideReticleSize;
	};
	static_assert(offsetof(AimingPlayerComponent, m_fOverrideReticleSize) == 0x1F0);
}