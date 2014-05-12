#include "ShareWrapper.h"
#include "PluginProtocol.h"
#include "PluginUtils.h"
#include "ProtocolShare.h"
#include <collection.h>

#define MAXBUFFER 2048

namespace PhoneDirect3DXamlAppComponent
{
	using namespace cocos2d::plugin;

	void ShareWrapper::onShareResult(Platform::Object^ obj, int ret, Platform::String^ msg)
	{
		PluginProtocol* plugin = PluginUtils::getPluginPtr(obj);
		ProtocolShare* sharePlugin = dynamic_cast<ProtocolShare*>(plugin);
		if (sharePlugin) {
			char chMsg[MAXBUFFER];
			WideCharToMultiByte(CP_UTF8, 0, msg->Data(), -1, chMsg, MAXBUFFER, 0, 0);
			ShareResultCode cRet = (ShareResultCode)ret;
			sharePlugin->onShareResult(cRet, chMsg);
		}
		else 
		{
			PluginUtils::outputLog("Can't find the C++ object of the ads plugin");
		}
	}

	void ShareWrapper::onLeaderboardResult(Platform::Object^ obj, int ret, Platform::String^ msg)
	{
		PluginProtocol* plugin = PluginUtils::getPluginPtr(obj);
		ProtocolShare* sharePlugin = dynamic_cast<ProtocolShare*>(plugin);
		if (sharePlugin) {
			char chMsg[MAXBUFFER];
			WideCharToMultiByte(CP_UTF8, 0, msg->Data(), -1, chMsg, MAXBUFFER, 0, 0);
			ShareResultCode cRet = (ShareResultCode)ret;
			sharePlugin->onLeaderboardResult(cRet, chMsg);
		}
		else
		{
			PluginUtils::outputLog("Can't find the C++ object of the ads plugin");
		}
	}
}
