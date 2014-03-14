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
#include "ProtocolShare.h"
#include "PluginUtils.h"

namespace cocos2d { namespace plugin {

ProtocolShare::ProtocolShare()
: _listener(NULL)
{
}

ProtocolShare::~ProtocolShare()
{
}

void ProtocolShare::configDeveloperInfo(TShareDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtils::outputLog("ProtocolShare", "The developer info is empty!");
        return;
    }
    else
    {
     //   PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    	//PluginJniMethodInfo t;
     //   if (PluginJniHelper::getMethodInfo(t
    	//	, pData->jclassName.c_str()
    	//	, "configDeveloperInfo"
    	//	, "(Ljava/util/Hashtable;)V"))
    	//{
     //   	// generate the hashtable from map
     //   	jobject obj_Map = PluginUtils::createJavaMapObject(&devInfo);

     //       // invoke java method
     //       t.env->CallVoidMethod(pData->jobj, t.methodID, obj_Map);
     //       t.env->DeleteLocalRef(obj_Map);
     //       t.env->DeleteLocalRef(t.classID);
     //   }
    }
}

void ProtocolShare::share(TShareInfo info)
{
    if (info.empty())
    {
        if (NULL != _listener)
        {
            onShareResult(kShareFail, "Share info error");
        }
        PluginUtils::outputLog("ProtocolShare", "The Share info is empty!");
        return;
    }
    else
    {
  //      PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
		//PluginJniMethodInfo t;
		//if (PluginJniHelper::getMethodInfo(t
		//	, pData->jclassName.c_str()
		//	, "share"
		//	, "(Ljava/util/Hashtable;)V"))
		//{
		//	// generate the hashtable from map
		//	jobject obj_Map = PluginUtils::createJavaMapObject(&info);

		//	// invoke java method
		//	t.env->CallVoidMethod(pData->jobj, t.methodID, obj_Map);
		//	t.env->DeleteLocalRef(obj_Map);
		//	t.env->DeleteLocalRef(t.classID);
		//}
    }
}

void ProtocolShare::setResultListener(ShareResultListener* pListener)
{
	_listener = pListener;
}

void ProtocolShare::onShareResult(ShareResultCode ret, const char* msg)
{
    if (_listener)
    {
    	_listener->onShareResult(ret, msg);
    }
    else
    {
        PluginUtils::outputLog("ProtocolShare", "Result listener is null!");
    }
    PluginUtils::outputLog("ProtocolShare", "Share result is : %d(%s)", (int) ret, msg);
}

}} // namespace cocos2d { namespace plugin {