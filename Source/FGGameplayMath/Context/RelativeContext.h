#pragma once

UENUM(meta = (Bitflags))
enum class ERelativeContext
{
	Behind,
	InFront,
	ToTheRight,
	ToTheLeft,
	Above,
	Below,
	Close,
	Far,
	Seen,
	Unseen,
	FacingSame,
	FacingOpposite
};