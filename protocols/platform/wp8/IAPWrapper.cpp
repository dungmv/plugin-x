#include "IAPWrapper.h"
#include "PluginProtocol.h"
#include "ProtocolIAP.h"
#include "PluginUtils.h"
#include <collection.h>
#include <ppltasks.h>

namespace PhoneDirect3DXamlAppComponent
{
using namespace cocos2d::plugin;
using namespace concurrency;

void IAPWrapper::onPayResult(Platform::Object^ obj, int ret, Platform::String^ msg)
{	
	PluginProtocol* pPlugin = PluginUtils::getPluginPtr(obj);
	ProtocolIAP* pIAP = dynamic_cast<ProtocolIAP*>(pPlugin);
	if (pIAP) {
		char *chMsg = new char[2048];
		WideCharToMultiByte(CP_UTF8, 0, msg->Data(), -1, chMsg, sizeof(chMsg), 0, 0);
		PayResultCode cRet = (PayResultCode)ret;
		create_task([pIAP, cRet, chMsg] {
			pIAP->onPayResult(cRet, chMsg);
			delete[] chMsg;
		});
	}
	else 
	{
		PluginUtils::outputLog("Can't find the C++ object of the pay plugin ");
	}
}

}