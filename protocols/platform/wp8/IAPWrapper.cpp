#include "IAPWrapper.h"
#include "PluginProtocol.h"
#include "ProtocolIAP.h"
#include "PluginUtils.h"
#include <collection.h>

namespace PhoneDirect3DXamlAppComponent
{
using namespace cocos2d::plugin;

IAPWrapper::IAPWrapper()
{
}

void IAPWrapper::onPayResult(Platform::Object^ obj, int ret, Platform::String^ msg)
{	
	PluginProtocol* pPlugin = PluginUtils::getPluginPtr(obj);
	ProtocolIAP* pIAP = dynamic_cast<ProtocolIAP*>(pPlugin);
	if (pIAP) {
		char chMsg[1024];
		WideCharToMultiByte(CP_UTF8, 0, msg->Data(), -1, chMsg, sizeof(chMsg), 0, 0);
		PayResultCode cRet = (PayResultCode)ret;
		pIAP->onPayResult(cRet, chMsg);
	}
	else {
		PluginUtils::outputLog("Can't find the C++ object of the pay plugin ");
	}
}

}