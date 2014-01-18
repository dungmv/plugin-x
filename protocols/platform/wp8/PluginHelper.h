#pragma once

#include "InterfaceProtocol.h"

namespace PhoneDirect3DXamlAppComponent {
	
	[Windows::Foundation::Metadata::WebHostHidden]
	public interface class IPluginWrapper
	{
	public:
		virtual Platform::Object^ initPlugin(Platform::String^ className);
		virtual PluginType getPluginType(Platform::Object^ obj);
	};

	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class PluginHelper sealed
	{
	public:
		PluginHelper();
		virtual ~PluginHelper();
		static PluginHelper^ getInstance();
		void initPlugin(IPluginWrapper^ wrapper);
		Platform::Object^ createPlugin(Platform::String^ className);
		PluginType getPluginType(Platform::Object^ obj);
	private:
		IPluginWrapper^ m_wPluginWrapper;
		//static PluginHelper^ s_pHelper;
	};

} // namespace cocos2d { namespace plugin {
