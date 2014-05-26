using PhoneDirect3DXamlAppComponent;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.ApplicationModel.Store;
using Store = Windows.ApplicationModel.Store;
using System.Windows;
using System.Diagnostics;
using System.Net.NetworkInformation;

namespace PluginX
{
    class IAPStore : InterfaceIAP
    {
        private bool bDebug = true;

        private const int successes = 0;
        private const int canceled = 1;
        private const int error = 2;

        public void configDeveloperInfo(IDictionary<string, string> cpInfo)
        {
            //Storeload();
        }

        private async void Storeload()
        {
            Debug.WriteLine("start debug:");
            ListingInformation li = await Store.CurrentApp.LoadListingInformationAsync();
            foreach (string key in li.ProductListings.Keys)
            {
                ProductListing pListing = li.ProductListings[key];
                System.Diagnostics.Debug.WriteLine(key);
                //bool actived = Store.CurrentApp.LicenseInformation.ProductLicenses[key].IsActive;
            }
            Debug.WriteLine("done");
        }

        public void payForProduct(IDictionary<string, string> profuctInfo)
        {
            string key = profuctInfo["productID"];

            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                payment(key);
            });
        }

        private async void payment(string key)
        {
            if (!NetworkInterface.GetIsNetworkAvailable())
            {
                MessageBox.Show("Network error, please check your network setting and try again!");
                onComplated(error, "khong co mang");
                return;
            }
            //if (!Store.CurrentApp.LicenseInformation.ProductLicenses[key].IsActive)
            //{
            try
            {
                await CurrentApp.RequestProductPurchaseAsync(key, false);
                CurrentApp.ReportProductFulfillment(key);
                onComplated(successes, "thanh toan thanh cong");
            }
            catch (SystemException ex)
            {
                onComplated(canceled, "thanh toan that bai");
                //MessageBox.Show("Product not purchased: " + ex);
            }

                //RenderStoreItems();
            //}
            //else
            //{
            //    Debug.WriteLine("da mua roi");
            //}
        }

        public PluginType getPluginType()
        {
            return PluginType.PluginIAP;
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
            bDebug = debug;
        }

        private void onComplated(int ret, string msg)
        {
            IAPWrapper.onPayResult(this, ret, msg);
        }
    }
}
