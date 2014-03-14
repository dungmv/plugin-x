using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using System.Windows.Threading;
using Microsoft.Phone.Info;

namespace PhoneDirect3DXamlAppInterop.Utils
{
    public partial class Usage : UserControl
    {
        private readonly DispatcherTimer timer;
        private const float ByteToMega = 1024 * 1024;
        public Usage()
        {
            InitializeComponent();
            this.VerticalAlignment = System.Windows.VerticalAlignment.Top;
            this.HorizontalAlignment = System.Windows.HorizontalAlignment.Left;

            this.timer = new DispatcherTimer();
            this.timer.Interval = TimeSpan.FromMilliseconds(500);
            this.timer.Tick += OnTimerTick;
            this.timer.Start();
        }
        private void OnTimerTick(object sender, EventArgs e)
        {
            try
            {
                string currentMemory = (DeviceStatus.ApplicationCurrentMemoryUsage / ByteToMega).ToString("#.00");
                string peakMemory = (DeviceStatus.ApplicationPeakMemoryUsage / ByteToMega).ToString("#.00");
                usage.Text = string.Format("{0}MB {1}MB", currentMemory, peakMemory);
            }
            catch (Exception ex)
            {
                usage.Text = (ex.StackTrace);
                this.timer.Stop();
            }
        }
    }
}
