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
#include "ProtocolUtils.h"
#include "PluginUtils.h"
#include "InterfaceUtils.h"
#include <assert.h>

namespace cocos2d { namespace plugin {
	
namespace WFC = Windows::Foundation::Collections;
using namespace PhoneDirect3DXamlAppComponent;

ProtocolUtils::ProtocolUtils()
    : m_rateListener(NULL)
    , m_shareListener(NULL)
    , m_downloadListener(NULL)
{
}

ProtocolUtils::~ProtocolUtils()
{
}

void ProtocolUtils::configDeveloperInfo(TUtilDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtils::outputLog("The developer info is empty for %s!", this->getPluginName());
        return;
    }
    else
    {
        PluginRCData* pData = PluginUtils::getPluginRCData(this);
        assert(pData != NULL);
        
        //id ocObj = pData->obj;
        //if ([ocObj conformsToProtocol:@protocol(InterfaceUtil)]) {
        //    NSObject<InterfaceUtil>* curObj = ocObj;
        //    NSMutableDictionary* pDict = PluginUtils::createDictFromMap(&devInfo);
        //    [curObj configDeveloperInfo:pDict];
        //}
    }
}

void ProtocolUtils::terminate()
{
	PluginRCData* pData = PluginUtils::getPluginRCData(this);
	assert(pData != NULL);
	Platform::Object^ rcObj = pData->obj;
	auto obj = dynamic_cast<InterfaceUtils^>(rcObj);
	if (obj)
	{
		obj->terminate();
	}
}

void ProtocolUtils::terminate(Dict info)
{
	if (info.empty())
	{
		terminate();
	}
	else
	{
		PluginRCData* pData = PluginUtils::getPluginRCData(this);
		assert(pData != NULL);
		Platform::Object^ rcObj = pData->obj;
		auto obj = dynamic_cast<InterfaceUtils^>(rcObj);
		if (obj)
		{
			WFC::IMap<Platform::String^, Platform::String^>^ map = PluginUtils::createDictFromMap(&info);
			obj->terminate(map);
		}
	}

}


void ProtocolUtils::showMessageBox(std::string msg, std::string title)
{
	PluginRCData* pData = PluginUtils::getPluginRCData(this);
	assert(pData != NULL);
	Platform::Object^ rcObj = pData->obj;
	auto obj = dynamic_cast<InterfaceUtils^>(rcObj);
	if (obj)
	{
		obj->showMessageBox(PluginUtils::NativeStringToPlatformString(msg.c_str()), PluginUtils::NativeStringToPlatformString(title.c_str()));
	}
}

void ProtocolUtils::rate()
{
    //if (info.empty())
    //{
    //    if (NULL != m_rateListener)
    //    {
    //        onRateResult(kRateFail, "Rate info error");
    //    }
    //    PluginUtils::outputLog("The Rate info of %s is empty!", this->getPluginName());
    //    return;
    //}
    //else
    {
        PluginRCData* pData = PluginUtils::getPluginRCData(this);
        assert(pData != NULL);
		Platform::Object^ rcObj = pData->obj;
		auto obj = dynamic_cast<InterfaceUtils^>(rcObj);
		if (obj)
		{
			obj->rate();
		}
    }
}

void ProtocolUtils::rate(Dict info)
{
	if (info.empty())
	{
	    if (NULL != m_rateListener)
	    {
	        onRateResult(kRateFail, "Rate info error");
	    }
	    PluginUtils::outputLog("The Rate info of %s is empty!", this->getPluginName());
	    return;
	}
	else
	{
		PluginRCData* pData = PluginUtils::getPluginRCData(this);
		assert(pData != NULL);
		Platform::Object^ rcObj = pData->obj;
		auto obj = dynamic_cast<InterfaceUtils^>(rcObj);
		if (obj)
		{
			WFC::IMap<Platform::String^, Platform::String^>^ map = PluginUtils::createDictFromMap(&info);
			obj->rate(map);
		}
	}
}

void ProtocolUtils::openURL(Dict info)
{
	if (info.empty())
	{
		if (NULL != m_rateListener)
		{
			onRateResult(kRateFail, "url info error");
		}
		PluginUtils::outputLog("The url info of %s is empty!", this->getPluginName());
		return;
	}
	else
	{
		PluginRCData* pData = PluginUtils::getPluginRCData(this);
		assert(pData != NULL);
		Platform::Object^ rcObj = pData->obj;
		auto obj = dynamic_cast<InterfaceUtils^>(rcObj);
		if (obj)
		{
			WFC::IMap<Platform::String^, Platform::String^>^ map = PluginUtils::createDictFromMap(&info);
			obj->openURL(map);
		}
	}
}

void ProtocolUtils::setResultListener(RateResultListener* pRateListener)
{
	m_rateListener = pRateListener;
}
    
void ProtocolUtils::onRateResult(RateResultCode ret, const char* msg)
{
    if (m_rateListener)
    {
    	m_rateListener->onRateResult(ret, msg);
    }
    else
    {
        PluginUtils::outputLog("Rate result listener of %s is null!", this->getPluginName());
    }
    PluginUtils::outputLog("Rate result of %s is : %d(%s)", this->getPluginName(), (int) ret, msg);
}

void ProtocolUtils::share()
{
	PluginRCData* pData = PluginUtils::getPluginRCData(this);
	assert(pData != NULL);
	Platform::Object^ rcObj = pData->obj;
	auto obj = dynamic_cast<InterfaceUtils^>(rcObj);
	if (obj)
	{
		obj->share();
	}
}
    
void ProtocolUtils::setResultListener(UtilShareResultListener* pListener)
{
    m_shareListener = pListener;
}
    
void ProtocolUtils::onUtilShareResult(UtilShareResultCode ret, const char* msg)
{
        if (m_shareListener)
        {
            m_shareListener->onUtilShareResult(ret, msg);
        }
        else
        {
            PluginUtils::outputLog("Share result listener of %s is null!",
                                      this->getPluginName());
        }
        PluginUtils::outputLog("Share result of %s is : %d(%s)",
                                  this->getPluginName(), (int) ret, msg);
}
    
void ProtocolUtils::download(TDownloadInfo info)
{
	if (info.empty())
	{
	    if (NULL != m_rateListener)
	    {
	        onDownloadResult(kDownloadFail, "Download info error");
	    }
	    PluginUtils::outputLog("The download info of %s is empty!", this->getPluginName());
	    return;
	}
	else
    {
        PluginRCData* pData = PluginUtils::getPluginRCData(this);
        assert(pData != NULL);
		Platform::Object^ rcObj = pData->obj;
		auto obj = dynamic_cast<InterfaceUtils^>(rcObj);
		if (obj)
		{
			WFC::IMap<Platform::String^, Platform::String^>^ map = PluginUtils::createDictFromMap(&info);
			obj->download(map);
		}
    }
}
    
void ProtocolUtils::setResultListener(DownloadResultListener* pListener)
{
    m_downloadListener = pListener;
}
    
void ProtocolUtils::onDownloadResult(DownloadResultCode ret, const char* msg)
{
    if (m_downloadListener)
    {
        m_downloadListener->onDownloadResult(ret, msg);
    }
    else
    {
        PluginUtils::outputLog("Rate result listener of %s is null!", this->getPluginName());
    }
    PluginUtils::outputLog("Rate result of %s is : %d(%s)", this->getPluginName(), (int) ret, msg);
}
    
}} // namespace cocos2d { namespace plugin {
