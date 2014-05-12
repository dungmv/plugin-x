/****************************************************************************
Copyright (c) 2012+2013 cocos2d+x.org

http://www.cocos2d+x.org

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

#ifndef __PLUGIN_UTILS_H__
#define __PLUGIN_UTILS_H__

#include "PluginProtocol.h"
#include <string>
#include <map>
#include "PluginParam.h"
#include "PluginMacros.h"
#include "PluginRCData.h"

namespace cocos2d { namespace plugin {

	class PluginUtils
	{
	public:
		static void initRCPlugin(PluginProtocol* pPlugin, Platform::Object^ rcObj, const char* className);
		static PluginRCData* getPluginRCData(PluginProtocol* pKeyObj);
		static void setPluginRCData(PluginProtocol* pKeyObj, PluginRCData* pData);
		static void erasePluginRCData(PluginProtocol* pKeyObj);

		static PluginProtocol* getPluginPtr(Platform::Object^ obj);

		static Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ createDictFromMap(std::map<std::string, std::string>* paramMap);

		//static Platform::Object^ getRCObjFromParam(PluginParam* param);

		//	/**
		//	@brief method don't have return value
		//	*/
		//	static void callOCFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param);
		//	static void callOCFunctionWithName(PluginProtocol* pPlugin, const char* funcName);

		//	/**
		//	@brief method return int value
		//	*/
		//	static int callOCIntFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param);
		//	static int callOCIntFunctionWithName(PluginProtocol* pPlugin, const char* funcName);

		//	/**
		//	@brief method return float value
		//	*/
		//	static float callOCFloatFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param);
		//	static float callOCFloatFunctionWithName(PluginProtocol* pPlugin, const char* funcName);

		//	/**
		//	@brief method return bool value
		//	*/
		//	static bool callOCBoolFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param);
		//	static bool callOCBoolFunctionWithName(PluginProtocol* pPlugin, const char* funcName);

		//	/**
		//	@brief method return string value
		//	*/
		//	static std::string callOCStringFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param);
		//	static std::string callOCStringFunctionWithName(PluginProtocol* pPlugin, const char* funcName);

		static void outputLog(const char* pFormat, ...);

		static Platform::String^ NativeStringToPlatformString(const char* source);
		//static char* PlatformStringToNativeString(Platform::String^ source);
		//private:
		//	static id callRetFunctionWithParam(PluginProtocol* pPlugin, const char* funcName, id param);
		//	static id callRetFunction(PluginProtocol* pPlugin, const char* funcName);
	};

} } // namespace cocos2d { namespace plugin {

#endif //__PLUGIN_UTILS_IOS_H__
