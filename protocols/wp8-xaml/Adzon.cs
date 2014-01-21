using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PhoneDirect3DXamlAppComponent;
using System.Windows.Controls;
using System.Threading;
using System.Diagnostics;
using adzon;
using Microsoft.Phone.Controls;
using System.Windows.Threading;
using System.Windows;

namespace PluginX
{
    class Adzon : InterfaceAds
    {
        /*Adzon Size*/
        private const int kSizeBanner = 0;
        private const int kSizeIABMRect = 1;
        private const int kSizeIABBanner = 2;
        private const int kSizeIABLeaderboard = 3;
        private const int kSizeSkyscraper = 4;

        /*Adz Position*/
        private const int kPosCenter = 0;
        private const int kPosTop = 1;
        private const int kPosTopLeft = 2;
        private const int kPosTopRight = 3;
        private const int kPosBottom = 4;
        private const int kPosBottomLeft = 5;
        private const int kPosBottomRight = 6;

        /*Adzon Type*/
        private const int kTypeBanner = 0;
        private const int kTypeFullScreen = 1;

        /*Adzon Key*/
        private const string kAdzID = "AdzonID";
        private const string kAdzUser = "UserID";
        private const string kAdzPass = "PassID";
        private const string kAdzType = "AdType";
        private const string kAdzSize = "AdSize";

        private adzonBanner bAds;
        private adzonFullscreen fcAds;

        private bool _debug = true;

        public Adzon()
        {
        }

        private void writeLog(string msg)
        {
            if (_debug) Debug.WriteLine("Adzon: " + msg);
        }

        public void configDeveloperInfo(IDictionary<string, string> devInfo)
        {
            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                string publishID = devInfo[kAdzID];
                string userID = devInfo[kAdzUser];
                string passID = devInfo[kAdzPass];

                writeLog("key: " + publishID + " user " + userID + " pass " + passID);

                bAds = new adzonBanner();
                bAds.setAdzonKey(publishID);
                bAds.setUser(userID);
                bAds.setPassword(passID);
                bAds.OnFail = (int n) => { writeLog("onfil " + n); };
                bAds.OnLoaded = () => { writeLog("thanh cong"); };

                fcAds = new adzonFullscreen();
                fcAds.setAdzonKey(publishID);
                fcAds.setUser(userID);
                fcAds.setPassword(passID);
                fcAds.OnLoaded = () => { writeLog("thanh cong"); };
                fcAds.OnFail = () => { writeLog("loi nhe"); };
                fcAds.OnClose = () => 
                { 
                    writeLog("clode");
                    Plugin.Instance.getRootLayout().Children.Remove(fcAds);
                };

                fcAds.OrientationChanged(PageOrientation.Landscape);
            });
        }

        public string getPluginVersion()
        {
            return "0.0.1";
        }

        public string getSDKVersion()
        {
            return "0.0.1";
        }

        public void setDebugMode(bool debug)
        {
            _debug = debug;
        }

        public PluginType getPluginType()
        {
            return PluginType.PluginAds;
        }

        public void showAds(IDictionary<string, string> info, int pos)
        {
            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                writeLog("day la debug");
                int type = Int32.Parse(info[kAdzType]);
                switch (type)
                {
                    case kTypeBanner:
                        {
                            writeLog("show ads banner");
                            showBannerAds(Int32.Parse(info[kAdzSize]), pos);
                            break;
                        }
                    case kTypeFullScreen:
                        {
                            writeLog("show ads full screen");
                            fcAds.showAds();
                            Grid root = Plugin.Instance.getRootLayout();
                            root.Children.Add(fcAds);
                            break;
                        }
                    default:
                        writeLog("The value of 'AdType' is wrong (should be 1 or 2) " + type.ToString());
                        break;
                }
            });
        }

        private void showBannerAds(int size, int pos)
        {
            bAds.showAds();
            switch (pos)
            {
                case kPosCenter:
                    bAds.HorizontalAlignment = System.Windows.HorizontalAlignment.Center;
                    bAds.VerticalAlignment = System.Windows.VerticalAlignment.Center;
                    break;
                case kPosTop:
                    bAds.HorizontalAlignment = System.Windows.HorizontalAlignment.Center;
                    bAds.VerticalAlignment = System.Windows.VerticalAlignment.Top;
                    break;
                case kPosTopLeft:
                    bAds.HorizontalAlignment = System.Windows.HorizontalAlignment.Left;
                    bAds.VerticalAlignment = System.Windows.VerticalAlignment.Top;
                    break;
                case kPosTopRight:
                    bAds.HorizontalAlignment = System.Windows.HorizontalAlignment.Right;
                    bAds.VerticalAlignment = System.Windows.VerticalAlignment.Top;
                    break;
                case kPosBottom:
                    bAds.HorizontalAlignment = System.Windows.HorizontalAlignment.Center;
                    bAds.VerticalAlignment = System.Windows.VerticalAlignment.Bottom;
                    break;
                case kPosBottomLeft:
                    bAds.HorizontalAlignment = System.Windows.HorizontalAlignment.Left;
                    bAds.VerticalAlignment = System.Windows.VerticalAlignment.Bottom;
                    break;
                case kPosBottomRight:
                    bAds.HorizontalAlignment = System.Windows.HorizontalAlignment.Right;
                    bAds.VerticalAlignment = System.Windows.VerticalAlignment.Bottom;
                    break;
                default:
                    writeLog("pos not avali " + pos.ToString());
                    break;
            }
            Grid root = Plugin.Instance.getRootLayout();
            if(!root.Children.Contains(bAds))
                root.Children.Add(bAds);
        }

        public void hideAds(IDictionary<string, string> info)
        {
            int type = Int32.Parse(info[kAdzType]);
            switch (type)
            {
                case kTypeBanner:
                    {
                        if (bAds != null)
                        {
                            Deployment.Current.Dispatcher.BeginInvoke(() =>
                              {
                                  Grid root = Plugin.Instance.getRootLayout();
                                  root.Children.Remove(bAds);
                              });
                        }
                        break;
                    }
                case kTypeFullScreen:
                    {
                        if (null != fcAds)
                        {
                            Deployment.Current.Dispatcher.BeginInvoke(() =>
                            {
                                Grid root = Plugin.Instance.getRootLayout();
                                root.Children.Remove(fcAds);
                            });
                        }
                        break;
                    }
                default:
                    writeLog("The value of 'AdType' is wrong (should be 1 or 2)" + type.ToString());
                    break;
            }

        }

        public void spendPoints(int points)
        {
            writeLog("Adzon not support spend points!");
        }

        public void queryPoints()
        {
            writeLog("Adzon not support query points!");
        }
    }
}
