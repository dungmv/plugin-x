#include "AdsWrapper.h"
#include "PluginUtils.h"
#include "PluginProtocol.h"
#include "ProtocolAds.h"
#include <collection.h>

namespace PhoneDirect3DXamlAppComponent
{
using namespace cocos2d::plugin;

AdsWrapper::AdsWrapper()
{
}


void AdsWrapper::onAdsResult(Platform::Object^ obj, int ret, Platform::String^ msg)
{
	PluginProtocol* plugin = PluginUtils::getPluginPtr(obj);
	ProtocolAds* adsPlugin = dynamic_cast<ProtocolAds*>(plugin);
	if (adsPlugin) {
		char chMsg[1024];
		WideCharToMultiByte(CP_UTF8, 0, msg->Data(), -1, chMsg, sizeof(chMsg), 0, 0);
		/*std::string chMsg = PluginUtils::PlatformStringToNativeString(msg);*/
		AdsResultCode cRet = (AdsResultCode)ret;
		AdsListener* listener = adsPlugin->getAdsListener();
		if (listener)
		{
			listener->onAdsResult(cRet, chMsg);
		}
	}
	else {
		PluginUtils::outputLog("Can't find the C++ object of the ads plugin");
	}
}

void AdsWrapper::onPlayerGetPoints(Platform::Object^ obj, int points)
{

}

}