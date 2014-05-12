/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "ProtocolIAP.h"
#include "PluginUtils.h"
#include "PluginRCData.h"
#include "InterfaceIAP.h"
#include <assert.h>

namespace cocos2d { namespace plugin {

bool ProtocolIAP::_paying = false;
namespace WFC = Windows::Foundation::Collections;
using namespace PhoneDirect3DXamlAppComponent;

ProtocolIAP::ProtocolIAP()
: _listener(NULL)
{
}

ProtocolIAP::~ProtocolIAP()
{
}

void ProtocolIAP::configDeveloperInfo(TIAPDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtils::outputLog("ProtocolIAP, The developer info is empty!");
        return;
    }
    else
    {
		PluginRCData* pData = PluginUtils::getPluginRCData(this);
		assert(pData != nullptr);
		Platform::Object^ rcObj = pData->obj;
		auto obj = dynamic_cast<InterfaceIAP^>(rcObj);
		if (obj)
		{
			WFC::IMap<Platform::String^, Platform::String^>^ map = PluginUtils::createDictFromMap(&devInfo);
			obj->configDeveloperInfo(map);
		}
    }
}

void ProtocolIAP::payForProduct(TProductInfo info)
{
    if (_paying)
    {
        PluginUtils::outputLog("ProtocolIAP now is paying");
        return;
    }

    if (info.empty())
    {
        if (NULL != _listener)
        {
            onPayResult(kPayFail, "Product info error");
        }
        PluginUtils::outputLog("The product info is empty!");
        return;
    }
    else
    {
        _paying = true;
        _curInfo = info;
		
		PluginRCData* pData = PluginUtils::getPluginRCData(this);

		assert(pData != NULL);

		Platform::Object^ rcObj = pData->obj;
		auto obj = dynamic_cast<InterfaceIAP^>(rcObj);
		if (obj)
		{
			WFC::IMap<Platform::String^, Platform::String^>^ map = PluginUtils::createDictFromMap(&info);
			obj->payForProduct(map);
		}
    }
}

void ProtocolIAP::setResultListener(PayResultListener* pListener)
{
	PluginUtils::outputLog("ProtocolIAP set listener");
	_listener = pListener;
}

void ProtocolIAP::onPayResult(PayResultCode ret, const char* msg)
{
    _paying = false;
    if (_listener)
    {
    	_listener->onPayResult(ret, msg, _curInfo);
    }
    else
    {
        PluginUtils::outputLog("Pay result listener is null!");
    }
    _curInfo.clear();
    //PluginUtils::outputLog("Pay result is: %d (%s)", (int) ret, msg);
}

}} // namespace cocos2d { namespace plugin {
