using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PhoneDirect3DXamlAppComponent;
using System.Windows;
using System.Diagnostics;
using PhoneDirect3DXamlAppInterop.Resources;
using Microsoft.Phone.Tasks;
using System.IO.IsolatedStorage;
using System.Windows.Media.Imaging;
using System.IO;
using System.Net.NetworkInformation;

namespace PluginX
{
    class Utils : InterfaceUtils
    {
        private bool _debug = true;
        private const string kPublisherID = "IdDevWP";
        private const string kOpen = "open";
        private IsolatedStorageSettings setting = IsolatedStorageSettings.ApplicationSettings;
        public void configDeveloperInfo(IDictionary<string, string> cpInfo)
        {
            throw new NotImplementedException();
        }
        public void rate()
        {
            //throw new NotImplementedException();
            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                //MessageBoxResult result = MessageBox.Show("Chúng tôi rất mong được bạn đánh giá 5 sao. Việc thể hiện sự yêu thích của bạn sẽ giúp chúng tôi tiếp tục phát triển ứng dụng và ngày càng hoàn thiện hơn!", "Yêu thích!", MessageBoxButton.OKCancel);
                //if (result == MessageBoxResult.OK)
                //{
                //    if (!setting.Contains(kOpen))
                //    {
                //        setting.Add(kOpen, -1);
                //    }
                //    else
                //    {
                //        setting[kOpen] = -1;
                //    }
                //    setting.Save();
                    MarketplaceReviewTask marketplaceReviewTask = new MarketplaceReviewTask();
                    marketplaceReviewTask.Show();
                //}
            });
        }
        public void rate(IDictionary<string, string> info)
        {
            //throw new NotImplementedException();
            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                int count;
                if (!setting.Contains(kOpen))
                {
                    setting.Add(kOpen, 1);
                    count = 1;
                }
                else
                {
                    count = Convert.ToInt32(setting[kOpen]);
                    setting[kOpen] = count + 1;
                    if (count > 20) count = -1;
                }
                setting.Save();
                if (count == -1) return;
                string x;
                info.TryGetValue("x1", out x);
                if (count.ToString() != x)
                {
                    info.TryGetValue("x2", out x);
                    if (count.ToString() != x) return;
                }
                {
                    MessageBoxResult result = MessageBox.Show("We'd love you to rate our app 5 stars Showing us some love on the store helps us to continue to work on the app and make things even better!", "We'd love you to rate our app 5 stars!", MessageBoxButton.OKCancel);
                    if (result == MessageBoxResult.OK)
                    {
                        setting[kOpen] = -1;
                        setting.Save();
                        MarketplaceReviewTask marketplaceReviewTask = new MarketplaceReviewTask();
                        marketplaceReviewTask.Show();
                    }
                }
                //if ((count != 5) == (count != 10)) return;
            });
        }

        public void share()
        {
            MarketplaceReviewTask marketplaceReviewTask = new MarketplaceReviewTask();
            marketplaceReviewTask.Show();
            //throw new NotImplementedException();
        }
        public async void download(IDictionary<string, string> info)
        {
            string publisher = info[kPublisherID];
            await Windows.System.Launcher.LaunchUriAsync(new Uri("zune:search?publisher=" + publisher));
            //throw new NotImplementedException();
        }

        public PluginType getPluginType()
        {
            return PluginType.PluginUtils;
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

        public void showMessageBox(string msg, string title)
        {
            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                MessageBox.Show(msg, title, MessageBoxButton.OK);
            });
        }

        public BitmapImage LoadImageFromIsolatedStorage(string path)
        {
            var isf = IsolatedStorageFile.GetUserStoreForApplication();
            using (var fs = isf.OpenFile(path, System.IO.FileMode.Open))
            {
                var image = new BitmapImage();
                image.SetSource(fs);
                return image;
            }
        }


        public void openURL(IDictionary<string, string> info)
        {
            WebBrowserTask webBrowserTask = new WebBrowserTask();

            webBrowserTask.Uri = new Uri(info["url"], UriKind.Absolute);

            webBrowserTask.Show();
        }

        public void terminate()
        {
            System.Windows.Application.Current.Terminate();
        }

        public void terminate(IDictionary<string, string> info)
        {
            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                MessageBoxResult result = MessageBox.Show(info["message"], info["title"], MessageBoxButton.OKCancel);
                if (result == MessageBoxResult.OK)
                {
                    System.Windows.Application.Current.Terminate();
                }
            });
        }
    }
}
