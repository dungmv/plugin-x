#pragma once

namespace PhoneDirect3DXamlAppComponent 
{

	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class ShareWrapper sealed
	{
	public:
		static void onShareResult(Platform::Object^ obj, int ret, Platform::String^ msg);
		static void onLeaderboardResult(Platform::Object^ obj, int ret, Platform::String^ msg);
	};

}
