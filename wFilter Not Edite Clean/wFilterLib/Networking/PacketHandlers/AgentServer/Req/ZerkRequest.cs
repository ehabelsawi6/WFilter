using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.Networking.Session.Struct;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult ZerkRequest(Packet packet, PlayerSession session)
    {
        if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            return new PacketResult(PacketResultType.Nothing);

        if (session.State.CharName.Length < 1)
            return new PacketResult(PacketResultType.Disconnect);

        if (packet.ReadByte() != 1)
            return new PacketResult(PacketResultType.Block);


        if (session.State.InSurvival && Config.GetSurvivalEvent.BlockZerk)
        {
            session.SendBlueNotice("You are not allowed to use Zerk during Survival Event !");
            return new PacketResult(PacketResultType.Block);
        }


        #region Zerk Delay

        if (Config.GetDelays.ZerkDelay > 0)
        {
            var lastZerkSec = Convert.ToInt32(DateTime.Now.Subtract(session.State.ZerkDelay).TotalSeconds);
            if (lastZerkSec < Config.GetDelays.ZerkDelay)
            {
                var zerkMsg =
                    $"Zerk delay: You must wait [{Config.GetDelays.ZerkDelay - lastZerkSec}] sec to Zerk again";

                 session.SendNotice(zerkMsg);
                return new PacketResult(PacketResultType.Block);
            }

            session.State.ZerkDelay = DateTime.Now;
        }

        #endregion

        if (Config.GetJob.DisableZerk && session.State.IsJob)
        {
             session.SendNotice("You are not allowed to use Zerk under job mode !");
            return new PacketResult(PacketResultType.Block);
        }

        if (Config.GetFortress.DisableZerk && session.State.Location == PlayerLocation.Fortress)
        {
             session.SendNotice("You are not allowed to use Zerk during Fortress War !");
            return new PacketResult(PacketResultType.Block);
        }

        //if (Configs.Config.GetPet.DisableZerkPet )
        //{
        //    session.SendNotice("You are not allowed to use Zerk with pet !");
        //    return new PacketResult(PacketResultType.Block);
        //}

        if (Config.GetBlockByRegion.ZerkRegions.Count > 0)
        {
            if (Config.GetBlockByRegion.ZerkRegions.Contains(session.State.TempPosition.RegionID))
            {
                 session.SendNotice("You are not allowed to use Zerk here !");
                return new PacketResult(PacketResultType.Block);
            }
        }

        return new PacketResult(PacketResultType.Nothing);
    }
}