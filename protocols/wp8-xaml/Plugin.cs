using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using PhoneDirect3DXamlAppComponent;

namespace PluginX
{
    class Plugin
    {
        private static Plugin instance = null;
        private Grid m_pGrid;

        public static Plugin Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new Plugin();
                    PluginHelper m_pHelper = new PluginHelper();
                    PluginWrapper wrapper = new PluginWrapper();
                    m_pHelper.initPlugin(wrapper);
                }
                return instance;
            }
        }

        private Plugin()
        {
        }

        public void init(Grid root)
        {
            m_pGrid = root;
        }

        public Grid getRootLayout()
        {
            return m_pGrid;
        }
    }
}
