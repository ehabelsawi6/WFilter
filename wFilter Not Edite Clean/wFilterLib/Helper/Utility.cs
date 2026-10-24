using System.Security.Cryptography;
using System.Text;
using wFilterLib.Libs.Firewall;

namespace wFilterLib.Helper;

public static class Utility
{
    public static string CleanString(string test)
    {
        var cleanText = test;
        cleanText = cleanText.Replace("'", "");
        cleanText = cleanText.Replace("-", "");
        cleanText = cleanText.Replace("\"", "");

        return cleanText;
    }

    public static string Base64Decode(string base64EncodedData) =>
        Encoding.UTF8.GetString(Convert.FromBase64String(base64EncodedData));

    #region Protection
    public static double GET_PER_SEC_RATE(ulong totalTraffic, DateTime startTime) =>
        Math.Round(totalTraffic / (DateTime.Now - startTime).TotalSeconds, 2);

    public static void BlockIp(string? ip, string? reason)
    {
        const string guidFwPolicy2 = "{E2B3C97F-6AE1-41AC-817A-F6F92166D7DD}";
        const string guidRwRule = "{2C5BC43E-3369-4C33-AB0C-BE9469677AF4}";
        var typeFwPolicy2 = Type.GetTypeFromCLSID(new Guid(guidFwPolicy2));
        var typeFwRule = Type.GetTypeFromCLSID(new Guid(guidRwRule));
        _ = (INetFwPolicy2)Activator.CreateInstance(typeFwPolicy2);
        var netFwRule = (INetFwRule)Activator.CreateInstance(typeFwRule);
        netFwRule.Name = $"{ip} Blocked by wkFilter";
        netFwRule.Description = reason;
        netFwRule.Action = NetFwAction.NetFwActionBlock;
        netFwRule.Direction = NetFwRuleDirection.NetFwRuleDirIn;
        netFwRule.Enabled = true;
        netFwRule.InterfaceTypes = "All";
        netFwRule.RemoteAddresses = ip;
        var netFwPolicy =
            (INetFwPolicy2)Activator.CreateInstance(Type.GetTypeFromProgID("HNetCfg.FwPolicy2"));
        netFwPolicy.Rules.Add(netFwRule);
        Globals.Logger.Info($"IP:{ip} has been blocked via firewall due to rules Reason:{reason}");

    }

    #endregion


    public static string CreateMD5(string input)
    {
        // Use input string to calculate MD5 hash
        using (var md5 = MD5.Create())
        {
            var inputBytes = Encoding.ASCII.GetBytes(input);
            var hashBytes = md5.ComputeHash(inputBytes);

            // Convert the byte array to hexadecimal string
            var sb = new StringBuilder();
            for (var i = 0; i < hashBytes.Length; i++)
                sb.Append(hashBytes[i].ToString("X2"));
            return sb.ToString().ToLower();
        }
    }
    //public static string XOR(string data, char[] key)
    //{
    //    try
    //    {
    //        var xorstring = new StringBuilder(data);
    //        for (var i = 0; i < xorstring.Length; i++)
    //            xorstring[i] = (char)(data[i] ^ key[i]);

    //        return xorstring.ToString();
    //    }
    //    catch (Exception EX) { Logger.Error($"XOR() failed and returned string.Empty. {EX}"); return string.Empty; }
    //}
}
