using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PhoneDirect3DXamlAppComponent;
using System.Windows.Controls;
using System.Threading;
using System.Diagnostics;
using Microsoft.Phone.Controls;
using System.Windows.Threading;
using System.Windows;
using Inneractive.Ad;
using System.Windows.Controls.Primitives;

namespace PluginX
{
    class AdsInneractive : InterfaceAds
    {
        /*AdsInneractive Size*/
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

        /*AdsInneractive Type*/
        private const int kTypeBanner = 0;
        private const int kTypeFullScreen = 1;

        /*AdsInneractive Key*/
        private const string kAdzID = "AdsInneractiveID";
        private const string kAdzUser = "UserID";
        private const string kAdzPass = "PassID";
        private const string kAdzType = "AdType";
        private const string kAdzSize = "AdSize";

        private string appid;
        private InneractiveAd bAds;

        private bool _debug = true;

        public AdsInneractive()
        {
        }

        private void writeLog(string msg)
        {
            if (_debug) Debug.WriteLine("AdsInneractive: " + msg);
        }

        public void configDeveloperInfo(IDictionary<string, string> devInfo)
        {
            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {

                bAds = new InneractiveAd();
                bAds.AppID = devInfo["appid"];
                bAds.AdType = InneractiveAd.IaAdType.IaAdType_Banner;
                bAds.ReloadTime = 60;
                bAds.OptionalAdHeight = 53;
                bAds.OptionalAdWidth = 350;
                appid = devInfo["appid"];

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
                int type = Int32.Parse(info[kAdzType]);
                switch (type)
                {
                    case kTypeBanner:
                        {
                            showBannerAds(Int32.Parse(info[kAdzSize]), pos);
                            break;
                        }
                    case kTypeFullScreen:
                        {
                            InneractiveAd.DisplayAd(appid, InneractiveAd.IaAdType.IaAdType_Interstitial, Plugin.Instance.getRootLayout(), 0);
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
            bAds.AdType = InneractiveAd.IaAdType.IaAdType_Banner;
            Plugin.Instance.addChild(bAds);
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
                        writeLog("not impli" + type.ToString());
                        break;
                    }
                default:
                    writeLog("The value of 'AdType' is wrong (should be 1 or 2)" + type.ToString());
                    break;
            }

        }

        public void spendPoints(int points)
        {
            writeLog("AdsInneractive not support spend points!");
        }

        public void queryPoints()
        {
            writeLog("AdsInneractive not support query points!");
        }
    }
}
