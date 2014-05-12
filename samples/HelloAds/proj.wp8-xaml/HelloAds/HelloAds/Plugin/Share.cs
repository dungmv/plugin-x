using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PhoneDirect3DXamlAppComponent;
using System.Net.NetworkInformation;
using System.Windows;
using Facebooklib;
using Microsoft.Phone.Controls;

namespace PluginX
{
    class Share : InterfaceShare
    {
        private bool _debug = true;
        private Facebook fb = new Facebook();
        private string fbid = null;

        private void writeLog(string mes)
        {
            if(_debug)
            {
                System.Diagnostics.Debug.WriteLine(mes);
            }
        }

        public void configDeveloperInfo(IDictionary<string, string> cpInfo)
        {
            fbid = cpInfo["fbAppID"];
        }

        public void share(IDictionary<string, string> info)
        {
            if (NetworkInterface.GetIsNetworkAvailable())
            {
                Deployment.Current.Dispatcher.BeginInvoke(() =>
                {
                    Plugin.Instance.addChild(fb.getPopup(info["id"], info["Orientation"]));
                    fb.PostPhotoFB(info["msg"], info["dir"]);
                    //Plugin.Instance.CurrentPopup = fb.getPopup(info["id"], info["Orientation"]);
                });
            }
            else
            {
                Deployment.Current.Dispatcher.BeginInvoke(() =>
                {
                    MessageBox.Show("Network error, check setting network!", "Network error!", MessageBoxButton.OK);
                });
            }
        }

        public PluginType getPluginType()
        {
            return PluginType.PluginShare;
        }

        public string getPluginVersion()
        {
            return "1.0.0";
        }

        public string getSDKVersion()
        {
            return "1.0.0";
        }

        public void setDebugMode(bool debug)
        {
            _debug = debug;
        }


        public void getLeaderboard()
        {

        }

        public void submitScore(int score)
        {

        }
    }
}
