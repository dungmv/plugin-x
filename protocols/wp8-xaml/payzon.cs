using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PhoneDirect3DXamlAppComponent;
using System.Diagnostics;
using libzon;
using System.Windows;
using Microsoft.Phone.Tasks;
using System.Windows.Threading;

namespace PluginX
{
    class Payzon : InterfaceIAP
    {
        /*result code*/
        private const int kPaySuccess = 0;
        private const int kPayFail = 1;
        private const int kPayCancel = 2;
        private const int kPayTimeOut = 3;

        private const int SMS_PAYMENT = 0; // payment via sms
        private const int CARD_PAYMENT = 1; // payment via credit card
        private const int VALID_CODE = 2; // payment via valid code sms
        private const int SMS_PERMISSION = 3; // payment via sms with permission


        private const string KEY_GAMEID = "GameID";
        private const string KEY_KEYCARD = "KeyCard";
        private const string KEY_VALUE = "Value";
        private const string KEY_TYPE_PAY = "TypePay";
        
        private bool _debug;
        private string gameId;
        private string keyCard;

        private ThanhtoanSMS pSMS;
        private Thanhtoanthe pCard;
        
        private void writeLog(string msg)
        {
            if (_debug) Console.WriteLine("Payzon: " + msg);
        }

        private void writeLog(string format, params object[] arg)
        {
            if (_debug)
            {
                Console.Write("Payzon: ");
                Console.WriteLine(format, arg);
            }
        }

        public void configDeveloperInfo(IDictionary<string, string> cpInfo)
        {
            if (!cpInfo.TryGetValue(KEY_GAMEID, out gameId))
            {
                gameId = "GAMESV";
            }
            if (!cpInfo.TryGetValue(KEY_KEYCARD, out keyCard))
            {
                keyCard = "0985bfd1ed1bd5b3e5ca2401b5952231";
            }
            writeLog(gameId + "|" + keyCard);
            // Khai bao cac thanh phan thanh toan cua Libzon iOs
            pSMS = new ThanhtoanSMS();
            pCard = new Thanhtoanthe();
            pCard.onResult = mobiCardResult;
            pCard.setCard_key(keyCard);
        }

        public void payForProduct(IDictionary<string, string> profuctInfo)
        {
            if (profuctInfo == null) 
            {
                payResult(kPayFail, "info null");
                return;
            }
            int value;
            if (!Int32.TryParse(profuctInfo[KEY_VALUE], out value))
            {
                value = 0;
                //payResult(kPayFail, "can not get value");
            }
            int type;
            if (!Int32.TryParse(profuctInfo[KEY_TYPE_PAY], out type))
            {
                type = 0;
                //payResult(kPayFail, "can not get type");
            }
            string cardNumber;
            if (!profuctInfo.TryGetValue("cardNumber", out cardNumber)) 
            {
                cardNumber = "";
                //payResult(kPayFail, "can not get cardNumber");
            }
            string cardSerial;
            if (!profuctInfo.TryGetValue("cardSerial", out cardSerial))
            {
                cardNumber = "";
                //payResult(kPayFail, "can not get cardSerial");
            }
            string telcom;
            if (!profuctInfo.TryGetValue("telcom", out telcom))
            {
                telcom = "";
                //payResult(kPayFail, "can not get telcom");
            }
            string codeSms;
            if (!profuctInfo.TryGetValue("smscode", out codeSms))
            {
                codeSms = "";
                //payResult(kPayFail, "can not get codeSms");
            }
            doPayment(type, value, cardNumber, cardSerial, telcom, codeSms);
        }

        private void doPayment(int type, int value, string cardNumber, string cardSerial, string telcom, string code)
        {
            if (type == SMS_PAYMENT) 
            {
                if (value == 5000)
                {
                    pSMS.sms5(gameId);
                }
                else if (value == 10000)
                {
                    pSMS.sms10(gameId);
                } 
                else
                {
                    pSMS.sms15(gameId);
                }
                payResult(kPaySuccess, "thanh cong " + type.ToString());
            }
            else if (type == CARD_PAYMENT)
            {
                pCard.sendCard(cardNumber, cardSerial, telcom);
            }
            else if (type == VALID_CODE) 
            {
                int pRet = pSMS.xacNhan(code);
                if (pRet == 0)
                {
                    payResult(kPayFail, "vali faild");
                }
                else
                {
                    payResult(kPaySuccess, pRet.ToString());
                }
            }
            else if (type == SMS_PERMISSION) 
            {
                // Payment is stop when onPaymentSmsSuccess fuction is called by smsAllInOne
                payResult(kPayCancel, "not support");
            } else {
                payResult(kPayCancel, "Type faild. Type is: " + type.ToString());
            }
        }

        private void mobiCardResult(string statuts, string message, string demon)
        {
            if(statuts == "404")
                payResult(kPayCancel, /*statuts + message +*/ demon);
            else
                payResult(kPaySuccess, /*statuts + message +*/ demon);
        }

        public string getPluginVersion()
        {
            return "0.0.1";
        }

        public string getSDKVersion()
        {
            return "0.0.1";
        }

        public PluginType getPluginType()
        {
            return PluginType.PluginIAP;
        }

        public void setDebugMode(bool debug)
        {
            _debug = debug;
        }

        private void payResult(int ret, string msg)
        {
            IAPWrapper.onPayResult(this, ret, msg);
        }
    }
}
