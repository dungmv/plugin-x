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
#include "PluginProtocol.h"
#include "PluginUtils.h"
#include <ppltasks.h>
//#include "PluginWrapper.h"

#define LOG_TAG     "PluginProtocol"

namespace cocos2d { namespace plugin {

PluginProtocol::~PluginProtocol()
{
    //PluginUtils::erasePluginRCData(this);
}

std::string PluginProtocol::getPluginVersion()
{
	std::string verName;

	//PluginOCData* pData = PluginUtils::getPluginOCData(this);
	//if (pData) {
	//	id pOCObj = pData->obj;
	//	SEL selector = NSSelectorFromString(@"getPluginVersion");

	//	if ([pOCObj respondsToSelector : selector]) {
	//		NSString* strRet = (NSString*)[pOCObj performSelector : selector];
	//		verName = [strRet UTF8String];
	//	}
	//	else {
	//		PluginUtilsIOS::outputLog("Can't find function 'getPluginVersion' in class '%s'", pData->className.c_str());
	//	}
	//}
	//else {
	//	PluginUtilsIOS::outputLog("Plugin %p not right initilized", this);
	//}
	verName = "1.1.1";
	return verName;
}

std::string PluginProtocol::getSDKVersion()
{
	std::string verName;

	//PluginOCData* pData = PluginUtils::getPluginOCData(this);
	//if (pData) {
	//	id pOCObj = pData->obj;
	//	SEL selector = NSSelectorFromString(@"getPluginVersion");

	//	if ([pOCObj respondsToSelector : selector]) {
	//		NSString* strRet = (NSString*)[pOCObj performSelector : selector];
	//		verName = [strRet UTF8String];
	//	}
	//	else {
	//		PluginUtilsIOS::outputLog("Can't find function 'getPluginVersion' in class '%s'", pData->className.c_str());
	//	}
	//}
	//else {
	//	PluginUtilsIOS::outputLog("Plugin %p not right initilized", this);
	//}
	verName = "1.1.1";
	return verName;
}

void PluginProtocol::setDebugMode(bool isDebugMode)
{
    //PluginUtils::callJavaFunctionWithName_oneParam(this, "setDebugMode", "(Z)V", isDebugMode);
}

/*
 * khong hieu cai dong nay dung de lam j nua
*/
void PluginProtocol::callFuncWithParam(const char* funcName, PluginParam* param, ...)
{
    std::vector<PluginParam*> allParams;
    if (NULL != param)
    {
        allParams.push_back(param);

        va_list argp;
        PluginParam* pArg = NULL;
        va_start( argp, param );
        while (1)
        {
            pArg = va_arg(argp, PluginParam*);
            if (pArg == NULL)
                break;

            allParams.push_back(pArg);
        }
        va_end(argp);
    }

    callFuncWithParam(funcName, allParams);
}

void PluginProtocol::callFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
}

std::string PluginProtocol::callStringFuncWithParam(const char* funcName, PluginParam* param, ...)
{
	std::string pRet = "wtf";
	return pRet;
}

std::string PluginProtocol::callStringFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
	std::string pRet = "wtf";
	return pRet;
}

int PluginProtocol::callIntFuncWithParam(const char* funcName, PluginParam* param, ...)
{
	int pRet = -1;
	return pRet;
}

int PluginProtocol::callIntFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
	int pRet = -1;
	return pRet;
}

bool PluginProtocol::callBoolFuncWithParam(const char* funcName, PluginParam* param, ...)
{
	bool pRet = false;
	return pRet;
}

bool PluginProtocol::callBoolFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
	bool pRet = true;
	return pRet;
}

float PluginProtocol::callFloatFuncWithParam(const char* funcName, PluginParam* param, ...)
{
	float pRet = 0.0f;
	return pRet;
}

float PluginProtocol::callFloatFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
	float pRet = 0.0f;
	return pRet;
}

}} //namespace cocos2d { namespace plugin {
