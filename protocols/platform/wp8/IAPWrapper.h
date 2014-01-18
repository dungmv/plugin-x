#pragma once

namespace PhoneDirect3DXamlAppComponent
{
	
[Windows::Foundation::Metadata::WebHostHidden]
public ref class IAPWrapper sealed
{
public:
	IAPWrapper();
	static void onPayResult(Platform::Object^ obj, int ret, Platform::String^ msg);
};

}