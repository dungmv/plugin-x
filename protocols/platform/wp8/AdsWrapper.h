#pragma once

namespace PhoneDirect3DXamlAppComponent
{

[Windows::Foundation::Metadata::WebHostHidden]
public ref class AdsWrapper sealed
{
public:
	static void onAdsResult(Platform::Object^ obj, int ret, Platform::String^ msg);
	static void onPlayerGetPoints(Platform::Object^ obj, int points);
};

}