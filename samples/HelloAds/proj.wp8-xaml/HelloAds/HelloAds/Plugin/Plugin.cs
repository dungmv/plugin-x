using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using PhoneDirect3DXamlAppComponent;
using System.Windows.Controls.Primitives;
using System.Windows;
using PhoneDirect3DXamlAppInterop;
using Microsoft.Phone.Controls;

namespace PluginX
{
    class Plugin
    {
        private static Plugin instance = null;
        private Popup m_Popup = null;
        private UIElement m_UIElement = null;
        private Grid m_GridRoot = null;
        private MainPage m_MainPage = null;

        protected Plugin()
        {
        }

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

        public void init(MainPage root)
        {
            m_MainPage = root;
            m_GridRoot = root.LayoutRoot;
        }

        public PageOrientation Orientation
        {
            get
            {
                return m_MainPage.Orientation;
            }
        }

        public Grid getRootLayout()
        {
            return m_GridRoot;
        }

        public bool addChild(Popup element)
        {
            if (!m_GridRoot.Children.Contains(element))
            {
                m_GridRoot.Children.Add(element);
                m_Popup = element;
                return true;
            }
            return false;
        }

        public bool addChild(UIElement element)
        {
            if (!m_GridRoot.Children.Contains(element))
            {
                m_GridRoot.Children.Add(element);
                m_UIElement = element;
                return true;
            }
            return false;
        }

        public bool removeChild(UIElement element)
        {
            if (m_GridRoot.Children.Contains(element))
            {
                m_GridRoot.Children.Remove(element);
                return true;
            }
            return false;
        }

        public bool OnBackKeyPress()
        {
            //if (m_UIElement != null && m_UIElement.Visibility == Visibility.Visible)
            //{
            //    m_UIElement.Visibility = Visibility.Collapsed;
            //    return false;
            //}
            if (m_Popup != null && m_Popup.IsOpen)
            {
                m_Popup.IsOpen = false;
                return false;
            }
            return true;
        }
    }
}
