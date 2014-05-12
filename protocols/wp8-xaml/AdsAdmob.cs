using GoogleAds;
using PhoneDirect3DXamlAppComponent;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace PluginX
{
    class AdsAdmob : InterfaceAds
    {
        /*Adz Size*/
        private readonly int kSizeBanner = 0;
        private readonly int kSizeIABMRect = 1;
        private readonly int kSizeIABBanner = 2;
        private readonly int kSizeIABLeaderboard = 3;
        private readonly int kSizeSkyscraper = 4;

        /*Adz Position*/
        private readonly int kPosCenter = 0;
        private readonly int kPosTop = 1;
        private readonly int kPosTopLeft = 2;
        private readonly int kPosTopRight = 3;
        private readonly int kPosBottom = 4;
        private readonly int kPosBottomLeft = 5;
        private readonly int kPosBottomRight = 6;

        /*Adz Type*/
        private readonly int kTypeBanner = 0;
        private readonly int kTypeFullScreen = 1;

        /*Adz Key*/
        private readonly string kAdzID = "AdmobID";
        private readonly string kAdzUser = "UserID";
        private readonly string kAdzPass = "PassID";
        private readonly string kAdzType = "AdType";
        private readonly string kAdzSize = "AdSize";

        // 
        private InterstitialAd interstitialAd;
        private AdView bannerAd = null;
        private AdRequest adRequest;
        private string mAdsUnitID;
        private bool _debug = true;
        //private DispatcherTimer tmr;

        public AdsAdmob()
        {

        }

        public void configDeveloperInfo(IDictionary<string, string> devInfo)
        {
            mAdsUnitID = devInfo["AdmobID"];
        }

        public void hideAds(IDictionary<string, string> info)
        {
            String strType = info[kAdzType];
            int adsType = Int32.Parse(strType);
            if (adsType == kTypeBanner)
            {
                Deployment.Current.Dispatcher.BeginInvoke(() =>
                {
                    Plugin.Instance.removeChild(bannerAd);
                    bannerAd = null;
                });
            }
            else if (adsType == kTypeFullScreen)
            {
                Debug.WriteLine("not support!");
            }
            else
            {
                Debug.WriteLine("unknow!");
            }
        }

        public void queryPoints()
        {
            Debug.WriteLine("not support!");
        }

        public void showAds(IDictionary<string, string> info, int pos)
        {
            int adsType = Int32.Parse(info[kAdzType]);
            if (adsType == kTypeBanner)
            {
                Deployment.Current.Dispatcher.BeginInvoke(() =>
                {
                    showBannerAds(Int32.Parse(info[kAdzSize]), pos);
                });
            }
            else if (adsType == kTypeFullScreen)
            {
                Deployment.Current.Dispatcher.BeginInvoke(() =>
                {
                    showInterstitialAds();
                });
            }
            else
            {
                Debug.WriteLine("unknow!");
            }
        }

        private void showInterstitialAds()
        {
            interstitialAd = new InterstitialAd(mAdsUnitID);
            interstitialAd.ReceivedAd += (object sender, AdEventArgs e) =>
            {
                Debug.WriteLine("Received interstitial successfully. Click 'Show Interstitial'.");
                interstitialAd.ShowAd();
            };
            interstitialAd.DismissingOverlay += (object sender, AdEventArgs e) =>
            {
                Debug.WriteLine("Dismissing interstitial.");
            };
            interstitialAd.FailedToReceiveAd += (object sender, AdErrorEventArgs e) =>
            {
                Debug.WriteLine("Failed to receive interstitial with error " + e.ErrorCode);
            };

            AdRequest adRequest = new AdRequest();
            adRequest.ForceTesting = false;
            interstitialAd.LoadAd(adRequest);
            
        }

        private void showBannerAds(int size, int pos)
        {
            bannerAd = new AdView
            {
                Format = AdFormats.Banner,
                AdUnitID = mAdsUnitID
            };
            if (pos == kPosCenter)
            {
                bannerAd.HorizontalAlignment = System.Windows.HorizontalAlignment.Center;
                bannerAd.VerticalAlignment = System.Windows.VerticalAlignment.Center;
            }
            else if (pos == kPosTop)
            {
                bannerAd.HorizontalAlignment = System.Windows.HorizontalAlignment.Center;
                bannerAd.VerticalAlignment = System.Windows.VerticalAlignment.Top;
            }
            else if (pos == kPosTopLeft)
            {
                bannerAd.HorizontalAlignment = System.Windows.HorizontalAlignment.Left;
                bannerAd.VerticalAlignment = System.Windows.VerticalAlignment.Top;
            }
            else if (pos == kPosTopRight)
            {
                bannerAd.HorizontalAlignment = System.Windows.HorizontalAlignment.Right;
                bannerAd.VerticalAlignment = System.Windows.VerticalAlignment.Top;
            }
            else if (pos == kPosBottom)
            {
                bannerAd.HorizontalAlignment = System.Windows.HorizontalAlignment.Center;
                bannerAd.VerticalAlignment = System.Windows.VerticalAlignment.Bottom;
            }
            else if (pos == kPosBottomLeft)
            {
                bannerAd.HorizontalAlignment = System.Windows.HorizontalAlignment.Left;
                bannerAd.VerticalAlignment = System.Windows.VerticalAlignment.Bottom;
            }
            else if (pos == kPosBottomRight)
            {
                bannerAd.HorizontalAlignment = System.Windows.HorizontalAlignment.Right;
                bannerAd.VerticalAlignment = System.Windows.VerticalAlignment.Bottom;
            }
            else
            {
                Debug.WriteLine("unknow!");
            }

            Plugin.Instance.addChild(bannerAd);
        }

        public void spendPoints(int points)
        {
            Debug.WriteLine("not support!");
        }

        public PluginType getPluginType()
        {
            return PluginType.PluginAds;
        }

        public string getPluginVersion()
        {
            return "0.0.1";
        }

        public string getSDKVersion()
        {
            return "6.5.11";
        }

        public void setDebugMode(bool debug)
        {
            _debug = debug;
        }
    }
}
