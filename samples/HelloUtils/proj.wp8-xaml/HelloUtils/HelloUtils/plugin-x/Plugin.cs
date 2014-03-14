using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using PhoneDirect3DXamlAppComponent;
using System.Windows.Controls.Primitives;
using System.Windows;

namespace PluginX
{
    class Plugin
    {
        private static Plugin instance = null;
        private Grid m_pGrid = null;
        private Popup mPopup = null;

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

        public bool addChild(UIElement element)
        {
            if (!m_pGrid.Children.Contains(element))
            {
                m_pGrid.Children.Add(element);
                return true;
            }
            return false;
        }

        public bool removeChild(UIElement element)
        {
            if (!m_pGrid.Children.Contains(element))
            {
                m_pGrid.Children.Remove(element);
                return true;
            }
            return false;
        }

        public Popup CurrentPopup
        {
            set
            {
                mPopup = value;
            }
            get
            {
                return mPopup;
            }
        }
    }
}
