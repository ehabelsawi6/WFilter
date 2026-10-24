using System.Text;
using wFilterLib;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult Hwid2(Packet packet, PlayerSession session)
    {
        const int baseValue = 147483647;
        
        var total1 = baseValue;
        var total2 = baseValue;
        var total3 = baseValue;
        var totalDynamic = baseValue;
        
        for (var i = 0; i < 5; i++)
        {
            var val = packet.ReadUInt8();
            total1 += (val * 3);
        }
        
        var check1 = packet.ReadUInt32(); // compare with total1
        var size = packet.ReadInt16();
        var actualHwid = new StringBuilder();
        
        for (var i = 0; i < size - 30241; i++)//actual hwid
        {
            var val = packet.ReadUInt8();
            actualHwid.Append((char)val);
            total2 += (val * 2);
        }
        
        var check2 = packet.ReadUInt32(); // compare with total2

        for (var i = 0; i < 10; i++)
        {
            var val = packet.ReadUInt8();
            if (val > 150)
                total3 += (val * 2);
            else
                total3 += (val * 3);
        }

        var check3 = packet.ReadUInt32(); // compare with total3

        var dynHwidInfo = new StringBuilder(); // dynamic amq
        dynHwidInfo.Append(session.State.RefObjId);
        dynHwidInfo.Append(session.State.CurLevel);
        dynHwidInfo.Append(session.State.ServerTime);
        dynHwidInfo.Append(session.State.ExpOffset);
        dynHwidInfo.Append(session.State.SExpOffset);
        dynHwidInfo.Append(session.State.RemainGold);
        dynHwidInfo.Append(session.State.RemainSkillPoint);
        
        var encryptedHwid = wFilterLib.Helper.Utility.CreateMD5(dynHwidInfo.ToString());

        var fromClient = new StringBuilder();
        
        for (var i = 0; i < encryptedHwid.Length; i++)
        {
            var val = packet.ReadUInt8();
            totalDynamic += ((val - 1) * 2);
            fromClient.Append((char)(val - 1));
        }
        
        var check4 = packet.ReadUInt32(); // compare with total_dynamic

        #region Verify

        if (check1 != total1)
            Globals.Logger.Warn("HWIDParser::Method1 is not equals.");
        if (check2 != total2)
            Globals.Logger.Warn("HWIDParser::Method2 is not equals.");
        if (check3 != total3)
            Globals.Logger.Warn("HWIDParser::Method3 is not equals.");
        if (check4 != totalDynamic)
            Globals.Logger.Warn("HWIDParser::Method4 is not equals.");
        if (encryptedHwid != fromClient.ToString())
            Globals.Logger.Warn("HWIDParser::Method5 is not equals.");

        if (check1 != total1 || check2 != total2 || check3 != total3 || check4 != totalDynamic || encryptedHwid != fromClient.ToString())
        {
            Globals.Logger.Warn("HWIDParser::Parsing error? {0} - {1}", session.State.CharName, session.State.Ip);
            return new PacketResult(PacketResultType.Disconnect);

        }

        #endregion


        session.State.Hwid = actualHwid.ToString();

        //todo comment this line -_-
        //Console.WriteLine("ActualHWID = "+ actualHwid.ToString());

        
        return new PacketResult(PacketResultType.Block);
    }
}