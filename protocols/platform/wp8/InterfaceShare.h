#pragma once

#include "InterfaceProtocol.h"

namespace PhoneDirect3DXamlAppComponent
{

	[Windows::Foundation::Metadata::WebHostHidden]
	public interface class InterfaceShare : InterfaceProtocol
	{
	public:
		virtual void configDeveloperInfo(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ cpInfo);
		virtual void share(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ shareInfo);
		virtual void submitScore(int score);
		virtual void getLeaderboard();
	};

}