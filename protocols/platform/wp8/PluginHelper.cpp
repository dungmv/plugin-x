#include "PluginHelper.h"
#include "PluginUtils.h"

namespace PhoneDirect3DXamlAppComponent {

	static PluginHelper^ s_pHelper = nullptr;

	PluginHelper^ PluginHelper::getInstance()
	{
		if (!s_pHelper)
		{
			s_pHelper = ref new PluginHelper();
		}
		return s_pHelper;
	}

	PluginHelper::PluginHelper()
	{
		s_pHelper = this;
	}

	PluginHelper::~PluginHelper()
	{
		if (s_pHelper == this)
		{
			s_pHelper = nullptr;
		}
	}

	void PluginHelper::initPlugin(IPluginWrapper^ wrapper)
	{
		m_wPluginWrapper = wrapper;
	}

	Platform::Object^ PluginHelper::createPlugin(Platform::String^ className)
	{
		return m_wPluginWrapper->initPlugin(className);
	}

	PluginType PluginHelper::getPluginType(Platform::Object^ obj)
	{
		return m_wPluginWrapper->getPluginType(obj);
	}
	
} // namespace cocos2d { namespace plugin {