using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.Networking.Session.Struct;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult UpdateRideStateRequest(Packet packet, PlayerSession session)
    {
        if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            return new PacketResult(PacketResultType.Nothing);
        var status = packet.ReadByte();
        var TEMP_PET_DISMOUNT_ID = packet.ReadUInt();

        if (status == 0x01 && TEMP_PET_DISMOUNT_ID == session.State.FellowPetId) //attempting to ride a pet
        {
            if (session.State.InSurvival)
                return new PacketResult(PacketResultType.Block);


            if (Config.GetFortress.DisablePetRide &&
                session.State.Location == PlayerLocation.Fortress)
            {
                 session.SendNotice("You cannot ride fellow pets here");
                return new PacketResult(PacketResultType.Block);
            }

            if (Config.GetJob.DisablePetRide && session.State.IsJob)
            {
                 session.SendNotice("You cannot ride fellow pets while in Job mode");
                return new PacketResult(PacketResultType.Block);
            }

            if (Config.GetExtra.DisableZerkPetRide && session.State.IsZerking)
            {
                 session.SendNotice("You cannot ride fellow pets while in Zerk mode");
                return new PacketResult(PacketResultType.Block);
            }
        }


        return new PacketResult(PacketResultType.Nothing);

    }
}