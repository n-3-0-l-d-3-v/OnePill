#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DeviceLockSubsystem.generated.h"

/**
 * Tracks whether this device has already completed the experience. Once locked, the
 * experience cannot be started again on this device — this is the thematic climax, not a
 * technical afterthought, so the lock file lives outside normal save-game slots and is
 * checked before the Pre-Pill sequence is allowed to begin.
 *
 * v1 uses a simple marker file with a hashed device+install identifier. This is intentionally
 * not bulletproof against a determined user wiping app data — see Docs/TECHNICAL_DESIGN.md
 * "Lock reliability" risk note for the open design question on how far to harden this.
 */
UCLASS()
class ONEPILL_API UDeviceLockSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintPure, Category = "OnePill|Lock")
	bool IsDeviceLocked() const { return bIsLocked; }

	/** Permanently marks this device as having completed the experience. Cannot be undone. */
	UFUNCTION(BlueprintCallable, Category = "OnePill|Lock")
	void LockDevicePermanently();

private:
	FString GetLockFilePath() const;

	bool bIsLocked = false;
};
