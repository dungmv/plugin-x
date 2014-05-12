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

#include "PluginUtils.h"
#include <map>
#include <collection.h>

#define MAX_LOG_LEN         1024

namespace WFC = Windows::Foundation::Collections;

namespace cocos2d { namespace plugin {

	void PluginUtils::initRCPlugin(PluginProtocol* pPlugin, Platform::Object^ ocObj, const char* className)
	{
		PluginRCData* pData = new PluginRCData();
		pData->obj = ocObj;
		pData->className = className;
		PluginUtils::setPluginRCData(pPlugin, pData);
	}

	std::map<PluginProtocol*, PluginRCData*> s_PluginRCObjMap;
	//std::map<std::string, PluginProtocol*> s_RCObjPluginMap;
	std::map<int, PluginProtocol*> s_RCObjPluginMap;

	typedef std::map<PluginProtocol*, PluginRCData*>::iterator RCObjMapIter;
	//typedef std::map<std::string, PluginProtocol*>::iterator RCObjPluginMapIter;
	typedef std::map<int, PluginProtocol*>::iterator RCObjPluginMapIter;

	PluginRCData* PluginUtils::getPluginRCData(PluginProtocol* pKeyObj)
	{
		PluginRCData* ret = NULL;
		RCObjMapIter it = s_PluginRCObjMap.find(pKeyObj);
		if (it != s_PluginRCObjMap.end()) {
			ret = it->second;
		}

		return ret;
	}

	PluginProtocol* PluginUtils::getPluginPtr(Platform::Object^ obj)
	{
		PluginProtocol* ret = NULL;
		RCObjPluginMapIter it = s_RCObjPluginMap.find(obj->GetHashCode());
		if (it != s_RCObjPluginMap.end()) {
			ret = it->second;
		}

		return ret;
	}

		//id PluginUtils::getOCObjFromParam(PluginParam* param)
		//{
		//	if (NULL == param)
		//	{
		//		return nil;
		//	}

		//	id obj = nil;
		//	switch (param->getCurrentType())
		//	{
		//	case PluginParam::kParamTypeInt:
		//		obj = [NSNumber numberWithInt : param->getIntValue()];
		//		break;
		//	case PluginParam::kParamTypeFloat:
		//		obj = [NSNumber numberWithFloat : param->getFloatValue()];
		//		break;
		//	case PluginParam::kParamTypeBool:
		//		obj = [NSNumber numberWithBool : param->getBoolValue()];
		//		break;
		//	case PluginParam::kParamTypeString:
		//		obj = [NSString stringWithUTF8String : param->getStringValue()];
		//		break;
		//	case PluginParam::kParamTypeStringMap:
		//	{
		//											 std::map<std::string, std::string> mapValue = param->getStrMapValue();
		//											 obj = createDictFromMap(&mapValue);
		//	}
		//		break;
		//	case PluginParam::kParamTypeMap:
		//	{
		//									   obj = [NSMutableDictionary dictionary];
		//									   std::map<std::string, PluginParam*> paramMap = param->getMapValue();
		//									   std::map<std::string, PluginParam*>::const_iterator it;
		//									   for (it = paramMap.begin(); it != paramMap.end(); ++it)
		//									   {
		//										   NSString* pKey = [NSString stringWithUTF8String : it->first.c_str()];
		//										   id objValue = PluginUtils::getOCObjFromParam(it->second);
		//										   [obj setValue : objValue forKey : pKey];
		//									   }
		//	}
		//		break;
		//	default:
		//		break;
		//	}

		//	return obj;
		//}

	void PluginUtils::setPluginRCData(PluginProtocol* pKeyObj, PluginRCData* pData)
	{
		erasePluginRCData(pKeyObj);
		s_PluginRCObjMap.insert(std::pair<PluginProtocol*, PluginRCData*>(pKeyObj, pData));
		s_RCObjPluginMap.insert(std::pair<int, PluginProtocol*>(pData->obj->GetHashCode(), pKeyObj));
	}

	void PluginUtils::erasePluginRCData(PluginProtocol* pKeyObj)
	{
		RCObjMapIter it = s_PluginRCObjMap.find(pKeyObj);
		if (it != s_PluginRCObjMap.end()) {
			PluginRCData* pData = it->second;
			if (pData != NULL)
			{
				//Platform::Object^ jobj = pData->obj;

				RCObjPluginMapIter pluginIt = s_RCObjPluginMap.find(pData->obj->GetHashCode());
				if (pluginIt != s_RCObjPluginMap.end())
				{
					s_RCObjPluginMap.erase(pluginIt);
				}

				//delete jobj;
				delete pData;
			}
			s_PluginRCObjMap.erase(it);
		}
	}

	WFC::IMap<Platform::String^, Platform::String^>^ PluginUtils::createDictFromMap(std::map<std::string, std::string>* paramMap)
	{
		if (NULL == paramMap)
		{
			return nullptr;
		}

		WFC::IMap<Platform::String^, Platform::String^>^ dict = ref new Platform::Collections::Map<Platform::String^, Platform::String^>();
			//WFC::IMap<Platform::String^, Platform::String^>(nullptr);
		std::map<std::string, std::string>::const_iterator it;
		for (it = paramMap->begin(); it != paramMap->end(); ++it)
		{
			Platform::String^ pKey = PluginUtils::NativeStringToPlatformString(it->first.c_str());
			Platform::String^ pValue = PluginUtils::NativeStringToPlatformString(it->second.c_str());
			dict->Insert(pKey, pValue);
		}
		return dict;
	}

	//void PluginUtils::callOCFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param)
	//{
	//	return_if_fails(funcName != NULL && strlen(funcName) > 0);

	//	PluginOCData* pData = PluginUtils::getPluginOCData(pPlugin);
	//	if (pData) {
	//		id pOCObj = pData->obj;

	//		NSString* strFuncName = [NSString stringWithUTF8String : funcName];
	//		strFuncName = [strFuncName stringByAppendingString : @":"];

	//		SEL selector = NSSelectorFromString(strFuncName);
	//		if ([pOCObj respondsToSelector : selector]) {
	//			[pOCObj performSelector : selector withObject : param];
	//		}
	//		else {
	//			outputLog("Can't find function '%s' in class '%s'", [strFuncName UTF8String], pData->className.c_str());
	//		}
	//	}
	//	else {
	//		PluginUtils::outputLog("Plugin %s not right initilized", pPlugin->getPluginName());
	//	}
	//}

	//void PluginUtils::callOCFunctionWithName(PluginProtocol* pPlugin, const char* funcName)
	//{
	//	return_if_fails(funcName != NULL && strlen(funcName) > 0);

	//	PluginOCData* pData = PluginUtils::getPluginOCData(pPlugin);
	//	if (pData) {
	//		id pOCObj = pData->obj;

	//		NSString* strFuncName = [NSString stringWithUTF8String : funcName];
	//		SEL selector = NSSelectorFromString(strFuncName);
	//		if ([pOCObj respondsToSelector : selector]) {
	//			[pOCObj performSelector : selector];
	//		}
	//		else {
	//			outputLog("Can't find function '%s' in class '%s'", [strFuncName UTF8String], pData->className.c_str());
	//		}
	//	}
	//	else {
	//		PluginUtils::outputLog("Plugin %s not right initilized", pPlugin->getPluginName());
	//	}
	//}

	//int PluginUtils::callOCIntFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param)
	//{
	//	NSNumber* num = (NSNumber*)callRetFunctionWithParam(pPlugin, funcName, param);
	//	int ret = [num integerValue];
	//	return ret;
	//}

	//int PluginUtils::callOCIntFunctionWithName(PluginProtocol* pPlugin, const char* funcName)
	//{
	//	NSNumber* num = (NSNumber*)callRetFunction(pPlugin, funcName);
	//	int ret = [num integerValue];
	//	return ret;
	//}

	//float PluginUtils::callOCFloatFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param)
	//{
	//	float ret = 0.0f;
	//	NSNumber* pRet = (NSNumber*)callRetFunctionWithParam(pPlugin, funcName, param);
	//	if (nil != pRet) {
	//		ret = [pRet floatValue];
	//	}

	//	return ret;
	//}

	//float PluginUtils::callOCFloatFunctionWithName(PluginProtocol* pPlugin, const char* funcName)
	//{
	//	float ret = 0.0f;
	//	NSNumber* pRet = (NSNumber*)callRetFunction(pPlugin, funcName);
	//	if (nil != pRet) {
	//		ret = [pRet floatValue];
	//	}

	//	return ret;
	//}

	//bool PluginUtils::callOCBoolFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param)
	//{
	//	bool ret = false;
	//	NSNumber* pRet = (NSNumber*)callRetFunctionWithParam(pPlugin, funcName, param);
	//	if (nil != pRet) {
	//		ret = [pRet boolValue];
	//	}

	//	return ret;
	//}

	//bool PluginUtils::callOCBoolFunctionWithName(PluginProtocol* pPlugin, const char* funcName)
	//{
	//	bool ret = false;
	//	NSNumber* pRet = (NSNumber*)callRetFunction(pPlugin, funcName);
	//	if (nil != pRet) {
	//		ret = [pRet boolValue];
	//	}

	//	return ret;
	//}

	//std::string PluginUtils::callOCStringFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param)
	//{
	//	std::string ret = "";
	//	NSString* pRet = (NSString*)callRetFunctionWithParam(pPlugin, funcName, param);
	//	if (nil != pRet) {
	//		ret = [pRet UTF8String];
	//	}

	//	return ret;
	//}

	//std::string PluginUtils::callOCStringFunctionWithName(PluginProtocol* pPlugin, const char* funcName)
	//{
	//	std::string ret = "";
	//	NSString* pRet = (NSString*)callRetFunction(pPlugin, funcName);
	//	if (nil != pRet) {
	//		ret = [pRet UTF8String];
	//	}

	//	return ret;
	//}

	//id PluginUtils::callRetFunction(PluginProtocol* pPlugin, const char* funcName)
	//{
	//	id ret = nil;
	//	return_val_if_fails(funcName != NULL && strlen(funcName) > 0, ret);

	//	PluginOCData* pData = PluginUtils::getPluginOCData(pPlugin);
	//	if (pData) {
	//		id pOCObj = pData->obj;

	//		NSString* strFuncName = [NSString stringWithUTF8String : funcName];
	//		SEL selector = NSSelectorFromString(strFuncName);
	//		if ([pOCObj respondsToSelector : selector]) {
	//			ret = [pOCObj performSelector : selector];
	//		}
	//		else {
	//			outputLog("Can't find function '%s' in class '%s'", [strFuncName UTF8String], pData->className.c_str());
	//		}
	//	}
	//	else {
	//		PluginUtils::outputLog("Plugin %s not right initilized", pPlugin->getPluginName());
	//	}

	//	return ret;
	//}

	//id PluginUtils::callRetFunctionWithParam(PluginProtocol* pPlugin, const char* funcName, id param)
	//{
	//	id ret = nil;
	//	return_val_if_fails(funcName != NULL && strlen(funcName) > 0, ret);

	//	PluginOCData* pData = PluginUtils::getPluginOCData(pPlugin);
	//	if (pData) {
	//		id pOCObj = pData->obj;

	//		NSString* strFuncName = [NSString stringWithUTF8String : funcName];
	//		strFuncName = [strFuncName stringByAppendingString : @":"];
	//		SEL selector = NSSelectorFromString(strFuncName);
	//		if ([pOCObj respondsToSelector : selector]) {
	//			ret = [pOCObj performSelector : selector withObject : param];
	//		}
	//		else {
	//			outputLog("Can't find function '%s' in class '%s'", [strFuncName UTF8String], pData->className.c_str());
	//		}
	//	}
	//	else {
	//		PluginUtils::outputLog("Plugin %s not right initilized", pPlugin->getPluginName());
	//	}

	//	return ret;
	//}

	void PluginUtils::outputLog(const char* pFormat, ...)
	{
		char szBuf[MAX_LOG_LEN + 1] = { 0 };
		va_list ap;
		va_start(ap, pFormat);
		vsnprintf_s(szBuf, MAX_LOG_LEN, pFormat, ap);
		va_end(ap);
		WCHAR wszBuf[MAX_LOG_LEN] = { 0 };
		MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
		OutputDebugStringW(L"Plugin-x: ");
		OutputDebugStringW(wszBuf);
		OutputDebugStringW(L"\n");
		//WideCharToMultiByte(CP_ACP, 0, wszBuf, sizeof(wszBuf), szBuf, sizeof(szBuf), NULL, FALSE);
	}

	Platform::String^ PluginUtils::NativeStringToPlatformString(const char* className)
	{
		WCHAR wszBuf[MAX_LOG_LEN] = { 0 };
		MultiByteToWideChar(CP_UTF8, 0, className, -1, wszBuf, sizeof(wszBuf));
		return ref new Platform::String(wszBuf);
	}
	
	//char* PluginUtils::PlatformStringToNativeString(Platform::String^ source)
	//{
	//	char szUTF8String[MAX_LOG_LEN];
	//	WideCharToMultiByte(CP_UTF8, WC_COMPOSITECHECK, source->Data(), -1, szUTF8String, sizeof(szUTF8String), nullptr, nullptr);
	//	return szUTF8String;
	//}
} }// namespace cocos2d { namespace plugin {
