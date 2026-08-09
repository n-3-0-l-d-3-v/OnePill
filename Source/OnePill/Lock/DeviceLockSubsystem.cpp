#include "Lock/DeviceLockSubsystem.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/SecureHash.h"

FString UDeviceLockSubsystem::GetLockFilePath() const
{
	// Stored outside the standard SaveGame slots so a normal "delete save" action does not
	// undo the lock.
	return FPaths::Combine(FPaths::ProjectPersistentDownloadDir(), TEXT("OnePill.lock"));
}

void UDeviceLockSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	bIsLocked = FPaths::FileExists(GetLockFilePath());
}

void UDeviceLockSubsystem::LockDevicePermanently()
{
	if (bIsLocked)
	{
		return;
	}

	const FString LockPath = GetLockFilePath();
	const FString Timestamp = FDateTime::UtcNow().ToIso8601();
	const FString Marker = FMD5::HashAnsiString(*(FPlatformMisc::GetDeviceId() + Timestamp));

	if (FFileHelper::SaveStringToFile(Marker, *LockPath))
	{
		bIsLocked = true;
	}
}
