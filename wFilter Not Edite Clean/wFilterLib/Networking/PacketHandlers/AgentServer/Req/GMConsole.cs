using wFilterLib;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult GMConsoleRequest(Packet packet, PlayerSession session)
    {

        if (Globals.GMControlList.ContainsKey(session.State.UserName.ToLower()))
        {
            var GM = Globals.GMControlList[session.State.UserName.ToLower()];


            if (GM != null)
            {
                var command = packet.ReadByte();

                switch (command)
                {
                    case 1:
                        {
                            if (!GM.FindUser)
                            {
                                session.SendNotice($"You are not allowed to use FindUser command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    case 2:
                        {
                            if (!GM.Gotown)
                            {
                                session.SendNotice($"You are not allowed to use Gotown command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    case 3:
                        {
                            if (!GM.Totown)
                            {
                                session.SendNotice($"You are not allowed to use Totown command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    case 4:
                        {
                            if (!GM.WorldStatus)
                            {
                                session.SendNotice($"You are not allowed to use WorldStatus command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    case 6:
                        {
                            if (!GM.LoadMonster)
                            {
                                session.SendNotice($"You are not allowed to use LoadMonster command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    case 7:
                        {
                            if (!GM.MakeItem)
                            {
                                session.SendNotice($"You are not allowed to use MakeItem command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    case 8:
                        {
                            if (!GM.MoveToUser)
                            {
                                session.SendNotice($"You are not allowed to use MoveToUser command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    case 10:
                        {
                            if (!GM.WP)
                            {
                                session.SendNotice($"You are not allowed to use WP command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    case 12:
                        {
                            if (!GM.Zoe)
                            {
                                session.SendNotice($"You are not allowed to use Zoe command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    case 13:
                        {
                            if (!GM.Ban)
                            {
                                session.SendNotice($"You are not allowed to use Ban command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    case 14:
                        {
                            if (!GM.Invisible)
                            {
                                session.SendNotice($"You are not allowed to use Invisible command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    case 15:
                        {
                            if (!GM.Invincible)
                            {
                                session.SendNotice($"You are not allowed to use Invincible command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    case 17:
                        {
                            if (!GM.RecallUser)
                            {
                                session.SendNotice($"You are not allowed to use RecallUser command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    case 18:
                        {
                            if (!GM.RecallGuild)
                            {
                                session.SendNotice($"You are not allowed to use RecallGuild command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    case 20:
                        {
                            if (!GM.MobKill)
                            {
                                session.SendNotice($"You are not allowed to use MobKill command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    case 31:
                        {
                            if (!GM.MoveToNpc)
                            {
                                session.SendNotice($"You are not allowed to use MoveToNpc command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    case 38:
                        {
                            if (!GM.MakeRentItem)
                            {
                                session.SendNotice($"You are not allowed to use MakeRentItem command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    case 42:
                        {
                            if (!GM.Spawnunique_loc)
                            {
                                session.SendNotice($"You are not allowed to use Spawnunique_loc command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;

                    default:
                        {
                            if (!GM.Unkown)
                            {
                                session.SendNotice($"You are not allowed to use this command");
                                return new PacketResult(PacketResultType.Block);
                            }
                        }
                        break;
                }
            }
            else
            {
                session.SendNotice($"Call GM Owner to add you as one of our team");
                return new PacketResult(PacketResultType.Block);
            }
        }


        return new PacketResult(PacketResultType.Nothing);
    }
}