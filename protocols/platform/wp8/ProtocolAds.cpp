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
#include "ProtocolAds.h"
#include "PluginUtils.h"
#include "PluginRCData.h"
#include "InterfaceAds.h"


namespace cocos2d { namespace plugin {

namespace WFC = Windows::Foundation::Collections;

ProtocolAds::ProtocolAds()
: _listener(NULL)
{
}

ProtocolAds::~ProtocolAds()
{
}

void ProtocolAds::configDeveloperInfo(TAdsDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtils::outputLog("ProtocolAds", "The application info is empty!");
        return;
    }

    PluginRCData* pData = PluginUtils::getPluginRCData(this);
	if (!pData)
	{
		PluginUtils::outputLog("ProtocolAds, can not get RCData!");
		return;
	}

	Platform::Object^ rcObj = pData->obj;
	auto obj = dynamic_cast<PhoneDirect3DXamlAppComponent::InterfaceAds^>(rcObj);
	if (obj)
	{
		WFC::IMap<Platform::String^, Platform::String^>^ map = PluginUtils::createDictFromMap(&devInfo);
		obj->configDeveloperInfo(map);
	}
}

void ProtocolAds::showAds(TAdsInfo info, AdsPos pos)
{
	PluginRCData* pData = PluginUtils::getPluginRCData(this);
	if (!pData)
	{
		PluginUtils::outputLog("ProtocolAds", "can not get RCData!");
		return;
	}
	
	Platform::Object^ rcObj = pData->obj;
	auto obj = dynamic_cast<PhoneDirect3DXamlAppComponent::InterfaceAds^>(rcObj);
	if (obj)
	{
		WFC::IMap<Platform::String^, Platform::String^>^ map = PluginUtils::createDictFromMap(&info);
		obj->showAds(map, pos);
	}
}

void ProtocolAds::hideAds(TAdsInfo info)
{
	PluginRCData* pData = PluginUtils::getPluginRCData(this);
	if (!pData)
	{
		PluginUtils::outputLog("ProtocolAds", "can not get RCData!");
		return;
	}

	Platform::Object^ rcObj = pData->obj;
	auto obj = dynamic_cast<PhoneDirect3DXamlAppComponent::InterfaceAds^>(rcObj);
	if (obj)
	{
		WFC::IMap<Platform::String^, Platform::String^>^ map = PluginUtils::createDictFromMap(&info);
		obj->hideAds(map);
	}
}

void ProtocolAds::queryPoints()
{
    //PluginUtils::callJavaFunctionWithName(this, "queryPoints");
	// TODO: 
}

void ProtocolAds::spendPoints(int points)
{
	PluginRCData* pData = PluginUtils::getPluginRCData(this);
	if (!pData)
	{
		PluginUtils::outputLog("ProtocolAds", "can not get RCData!");
		return;
	}

	Platform::Object^ rcObj = pData->obj;
	auto obj = dynamic_cast<PhoneDirect3DXamlAppComponent::InterfaceAds^>(rcObj);
	if (obj)
	{
		obj->spendPoints(points);
	}
}

}} // namespace cocos2d { namespace plugin {
