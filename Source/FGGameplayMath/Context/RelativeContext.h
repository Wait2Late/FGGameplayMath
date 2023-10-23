#pragma once

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ERelativeContext : uint8
{
	None		= 0 UMETA(Hidden),
	Behind		= 1 << 1,
	InFront		= 1 << 2,
	ToTheRight	= 1 << 3,
	ToTheLeft	= 1 << 4,
	Above		= 1 << 5,
	Below		= 1 << 6,
	Seen		= 1 << 7
};
ENUM_CLASS_FLAGS(ERelativeContext)