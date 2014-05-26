using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PhoneDirect3DXamlAppComponent;
using System.Diagnostics;
using Microsoft.Phone.Controls;

namespace PluginX
{
    class PluginWrapper : IPluginWrapper
    {
        private const string namespaceName = "PluginX";
        public PluginType getPluginType(object obj)
        {
            PluginType pRet = PluginType.PluginNone;

            InterfaceProtocol protocol = obj as InterfaceProtocol;
            if (protocol != null)
            {
                pRet = protocol.getPluginType();
            }
            return pRet;
        }

        public object initPlugin(string className)
        {
            if (className == "LibzonPayment") className = "Payzon";
            Type type = Type.GetType(namespaceName + "." + className);
            return Activator.CreateInstance(type);
        }
    }
}
