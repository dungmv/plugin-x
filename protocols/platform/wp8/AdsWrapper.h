#pragma once

namespace PhoneDirect3DXamlAppComponent
{

typedef enum {
	kAdsReceived = 0,

	kAdsShown,
	kAdsDismissed,

	kPointsSpendSucceed,
	kPointsSpendFailed,

	kNetworkError,
	kUnknownError,
} AdsResult;

typedef enum {
	kPosCenter = 0,
	kPosTop,
	kPosTopLeft,
	kPosTopRight,
	kPosBottom,
	kPosBottomLeft,
	kPosBottomRight,
} AdsPosEnum;

[Windows::Foundation::Metadata::WebHostHidden]
public ref class AdsWrapper sealed
{
public:
	AdsWrapper();
	static void onAdsResult(Platform::Object^ obj, int ret, Platform::String^ msg);
	static void onPlayerGetPoints(Platform::Object^ obj, int points);
};

}