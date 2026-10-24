using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.Networking.Session.Struct;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult MainActionRequest(Packet packet, PlayerSession session)
    {
        try
        {
            if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
                return new PacketResult(PacketResultType.Nothing);

            if (session.State.CharName.Length < 1)
                return new PacketResult(PacketResultType.Disconnect);
            
            if (session.State.SurvivalBlock)
                return new PacketResult(PacketResultType.Block);
            
            var action = packet.ReadByte();
            if (action == 1)
            {
                var type = packet.ReadByte();
                switch (type)
                {
                    case 3:
                        if (Config.GetJob.DisableTrace && session.State.IsJob)
                        {
                             session.SendNotice("You are not allowed to use Trace under job mode !");
                            return new PacketResult(PacketResultType.Block);
                        }

                        if (Config.GetFortress.DisableTrace &&
                            session.State.Location == PlayerLocation.Fortress)
                        {
                             session.SendNotice("You are not allowed to use Trace during Fortress War !");
                            return new PacketResult(PacketResultType.Block);
                        }

                        break;
                    case 4:

                        

                        var skillId = packet.ReadInt32();

                        if (Config.GetBlockedSkill.EveryWhere.Contains(skillId))
                        {
                             session.SendNotice("You may not cast this spell!");
                            return new PacketResult(PacketResultType.Block);
                        }

                        if (Config.GetBlockedSkill.Job.Contains(skillId) && session.State.IsJob)
                        {
                             session.SendNotice("You may not cast this spell under job mode !");
                            return new PacketResult(PacketResultType.Block);
                        }

                        if (Config.GetBlockedSkill.Fortress.Contains(skillId) &&
                            session.State.Location == PlayerLocation.Fortress)
                        {
                             session.SendNotice("You may not cast this spell here !");
                            return new PacketResult(PacketResultType.Block);
                        }

                        if (Config.GetBlockedSkill.Arena.Contains(skillId) &&
                            session.State.Location == PlayerLocation.Arena)
                        {
                             session.SendNotice("You may not cast this spell here !");
                            return new PacketResult(PacketResultType.Block);
                        }

                        if (Config.GetBlockedSkill.Ctf.Contains(skillId) &&
                            session.State.Location == PlayerLocation.Ctf)
                        {
                             session.SendNotice("You may not cast this spell here !");
                            return new PacketResult(PacketResultType.Block);
                        }

                        if (Config.GetBlockedSkill.Fgw.Contains(skillId) &&
                            session.State.Location == PlayerLocation.Fgw)
                        {
                             session.SendNotice("You may not cast this spell here !");
                            return new PacketResult(PacketResultType.Block);
                        }

                        if (Config.GetBlockByRegion.Skills.Count > 0)
                        {
                            if (Config.GetBlockByRegion.Skills.ContainsKey(
                                    session.State.TempPosition.RegionID))
                            {
                                if (Config.GetBlockByRegion.Skills[session.State.TempPosition.RegionID]
                                    .Contains(skillId))
                                {
                                     session.SendNotice("You may not cast this spell here !");
                                    return new PacketResult(PacketResultType.Block);
                                }
                            }
                        }


                        break;
                }
            }

        }
        catch (Exception e)
        {

            Console.WriteLine(e.ToString());
        }
        return new PacketResult(PacketResultType.Nothing);
    }
}