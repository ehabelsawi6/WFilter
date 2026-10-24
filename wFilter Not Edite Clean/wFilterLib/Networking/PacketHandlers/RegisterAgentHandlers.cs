using wkFilter.NetworkStuff.PacketHandler.Agent;
using wFilterLib.Opcodes;
using wFilterLib.Networking.PacketStuff;

namespace wFilterLib.Networking.PacketHandlers;

public static class RegisterAgentHandlers
{
    public static void Setup(PacketManager packetManager)
    {
        //PacketManager packetManager = new(ServerType.Agent);

        #region Server Handlers

        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.CHAR_DATA_START, AgentHandler.CharacterBeginHandler);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.CHAR_DATA, AgentHandler.CharacterDataHandler);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.CHAR_DATA_END, AgentHandler.CharacterEndHandler);

        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.AUTH, AgentHandler.LoginResponse);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.ENVIRONMENT_CELESTIAL_POSITION, AgentHandler.CelestialPositionResponse);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.CHAR_MOVEMENT, AgentHandler.MovementResponse);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.ENTITY_PICKUPITEM_MOVE, AgentHandler.CancelMovementResponse);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.STALL_CREATE, AgentHandler.StallCreateResponse);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.COS_INFO, AgentHandler.CosInfoResponse);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.COS_UPDATE, AgentHandler.CosDismountResponse);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.ENTITY_UPDATE_STATE, AgentHandler.EntityUpdateStateResponse);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.BATTLEARENA_OPERATION, AgentHandler.BArenaOperationResponse);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.PARTY_UPDATE, AgentHandler.PartyDataUpdateResponse);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.PARTY_CREATED_FROM_MATCHING, AgentHandler.PartyInfoResponse);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.GAME_NOTIFY, AgentHandler.GameNotifyResponse);


        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.COMMUNITY_FRIEND_INFO, AgentHandler.FriendInfo);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.CHARACTER_ENTER_WORLD, AgentHandler.EnterWorld);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.CHAT_UPDATE, AgentHandler.ChatResponse);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.CHAR_HANDLE_UPDATE_SLOT, AgentHandler.InventoryResponse);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Agent.Response.ALCHEMY_REINFORCE, AgentHandler.AlchemyReinforceResponse);

        packetManager.RegisterHandler(PacketMode.Server, (ushort)Custom.Framework.DPSMeter, AgentHandler.DPSMeter);

        #endregion


        #region Client Handlers


        #region Custom Packets

        packetManager.RegisterHandler(PacketMode.Client, (ushort)Custom.Request.Hwid, AgentHandler.Hwid2);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Custom.Request.Customs, AgentHandler.HandleCustoms);

        #endregion
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Global.Request.MODULE_KEEP_ALIVE, AgentHandler.PingRequest);

        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.AUTH, AgentHandler.LoginRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.CHARACTER_SELECTION_JOIN, AgentHandler.CharacterSelectRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.GAME_READY, AgentHandler.GameReadyRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.LOGOUT, AgentHandler.LogoutRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.PLAYER_BERSERK, AgentHandler.ZerkRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.SIEGE_ACTION, AgentHandler.SiegeActionRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.EXCHANGE_START, AgentHandler.ExchangeStartRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.STALL_CREATE, AgentHandler.StallCreateRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.TELEPORT_USE, AgentHandler.TeleportUseRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.TIMEJOB_USAGE, AgentHandler.TimeJobUsageRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.INVENTORY_ITEM_USE, AgentHandler.ItemUseRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.CHAR_MAINACTION, AgentHandler.MainActionRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.COS_UPDATE_RIDESTATE, AgentHandler.UpdateRideStateRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.FRPVP_UPDATE, AgentHandler.FrPvpUpdateRequest);

        //Academy
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.ACADEMY_CREATE, AgentHandler.AcademyCreateRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.ACADEMY_INVITE, AgentHandler.AcademyInviteRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.ACCADEMY_MATCHING_JOIN, AgentHandler.AcademyJoinRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.ACADEMY_KICK, AgentHandler.AcademyKickRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.ACADEMY_LEAVE, AgentHandler.AcademyLeaveRequest);

        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.FLAGWAR_REGISTER, AgentHandler.CtfRegisterRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.BATTLEARENA_REQUEST, AgentHandler.BArenaRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.ALCHEMY_REINFORCE, AgentHandler.AlchemyReinforceRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.GUILD_INVITE, AgentHandler.GuildInviteRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.GUILD_UNION_INVITE, AgentHandler.UnionInviteRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.MAGICOPTION_GRANT, AgentHandler.MagicOptionGrantRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.INVENTORY_OPERATION, AgentHandler.InventoryOperationRequest);

        //Party
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.PARTY_CREATE, AgentHandler.PartyRequests);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.PARTY_INVITE, AgentHandler.PartyRequests);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.PARTY_MATCHING_FORM, AgentHandler.PartyRequests);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.PARTY_MATCHING_JOIN, AgentHandler.PartyRequests);


        //chat
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.CHAT, AgentHandler.ChatRequest);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.PLAYER_LINKED_GLOBAL, AgentHandler.LinkedItemInfo);



        //disable alchemy system 
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.ALCHEMY_ENCHANT, AgentHandler.AlchemyReinforceRequest2);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.ALCHEMY_MANUFACTURE, AgentHandler.AlchemyReinforceRequest2);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.ALCHEMY_DISMANTLE, AgentHandler.AlchemyReinforceRequest2);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.ALCHEMY_SOCKET, AgentHandler.AlchemyReinforceRequest2);


        //GM Control
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Agent.Request.OPERATOR_COMMAND, AgentHandler.GMConsoleRequest);

        #endregion
    }
}
