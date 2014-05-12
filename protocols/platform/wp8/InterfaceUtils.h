#pragma once

#include "InterfaceProtocol.h"

namespace PhoneDirect3DXamlAppComponent
{

	[Windows::Foundation::Metadata::WebHostHidden]
	public interface class InterfaceUtils : InterfaceProtocol
	{
	public:
		virtual void configDeveloperInfo(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ cpInfo);
		virtual void share();
		virtual void download(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ info);
		virtual void rate(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ info);
		virtual void rate();
		virtual void openURL(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ info);
		virtual void terminate();
		virtual void terminate(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ info);
		virtual void showMessageBox(Platform::String^ msg, Platform::String^ title);
	};

}