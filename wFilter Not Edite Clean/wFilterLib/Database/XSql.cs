using Dapper;
using NLog;
using System.Data;
using System.Data.SqlClient;
using System.Globalization;
using wFilterLib.Configs;
using wFilterLib.Database.Models;
using wFilterLib.Helper;
using wFilterLib.Networking.Session;
using wFilterLib.SSA;

namespace wFilterLib.Database;

public class XSql
{
    //--------------------------------------------------------------------------

    #region Private properties & statics

    private static readonly Logger Logger = LogManager.GetLogger("Sql");
    private string _connStr;
    private SqlConnection _connection;

    private string _tempConnStr =
        $"Server={Config.GetSql.SqlServer};Database={Config.GetSql.ShardDatabase};User Id={Config.GetSql.User};Password={Config.GetSql.Password};MultipleActiveResultSets=true;";
    #endregion

    //--------------------------------------------------------------------------

    #region Logic

    private bool IsOpen()
    {
        if (_connection == null)
            return false;

        return _connection.State is ConnectionState.Connecting or ConnectionState.Executing or ConnectionState.Fetching
            or ConnectionState.Open;
    }

    public bool Connect(string connStr )
    {
        
        _connStr = connStr;
        if (IsOpen())
        {
           // Logger.Warn("SQL Connection is already open...");
            return true;
        }

        _connection = new SqlConnection(_connStr);
        try
        {
            _connection.Open();
        }
        catch
        {
            return false;
        }

        return true;
    }

    public void Disconnect()
    {
        if (!IsOpen())
            return;

        try { _connection.Close(); }
        catch { Logger.Error($"Failed to close sql connection."); }
    }

    #endregion

    public bool ExecuteNonQuery(string query)
    {
        try
        {
            /*if (!IsOpen())
                Connect(_tempConnStr);*/

            using (var con = new SqlConnection(_connStr))
            {
                con.Open();
                con.Execute(query);
            }

            return true;
        }
        catch (Exception e)
        {
            Logger.Error($"Failed to execute : {query}");
            Logger.Debug(e);
            return false;
        }
    }

    public T Read<T>(string query)
    {
        try
        {
            /*if (!IsOpen())
                Connect(_tempConnStr);*/

            using (var con = new SqlConnection(_connStr))
            {
                con.Open();
                return con.Query<T>(query).FirstOrDefault();
            }
        }
        catch (Exception e)
        {
            Logger.Error($"Failed to execute : {query}");
            Logger.Debug(e);
            return default;
        }
    }

    public void GetCharacterRegions(PlayerSession session)
    {
        var query = $"use {Config.GetSql.ShardDatabase} Select top 1 TelRegion,DiedRegion from _Char where CharID = {session.State?.CharId}";

        try
        {

            using (var con = new SqlConnection(_connStr))
            {
                con.Open();
                var result = con.Query(query);

                if (session.State != null)
                {
                    session.State.LastReturnRegionId = result.FirstOrDefault().TelRegion;
                    session.State.LastDiedRegionId = result.FirstOrDefault().DiedRegion;
                }
            }
        }
        catch (Exception e)
        {
            Logger.Error($"Failed to execute : {query}");
            Logger.Debug(e);
        }
    }

    public SilkInfo Get_CurSilkPack_By_JID(int JID)
    {
        string query = $"Select silk_own,silk_gift,silk_point from {Config.GetSql.AccountDatabase}.dbo.SK_Silk where JID = {JID}";
        var silkInfo = new SilkInfo();
        try
        {
      
            using (var con = new SqlConnection(_connStr))
            {
                con.Open();
                var result = con.Query(query).FirstOrDefault();

                
                    silkInfo.Own = (uint)result.silk_own;
                    silkInfo.Gift = (uint)result.silk_gift;
                    silkInfo.Point = (uint)result.silk_point;

                

                return silkInfo;
            }
            
        }
        catch (Exception e)
        {
           // Logger.Error($"Failed to execute : {query}");
          //  Logger.Debug(e);
            return silkInfo;
        }
    }

    public AlchemyTypeInfo GetAlchemyTypeInfo(int charId, byte slot)
    {
        var query =
            $"use {Config.GetSql.ShardDatabase} SELECT a.TypeID3, b.OptLevel FROM _RefObjCommon a JOIN _Items b ON a.ID = b.RefItemID JOIN _Inventory c ON b.ID64 = c.ItemID WHERE c.CharID = {charId} AND c.Slot = {slot}";

        try
        {
        

            using (var con = new SqlConnection(_connStr))
            {
                con.Open();
                var result = con.Query(query).FirstOrDefault();
                var alchemyTypeInfo = new AlchemyTypeInfo
                {
                    TypeID3 = result.TypeID3,
                    Plus = result.OptLevel
                };

                return alchemyTypeInfo;
            }
        }
        catch (Exception e)
        {
            Logger.Error($"Failed to execute : {query}");
            Logger.Debug(e);
            return null;
        }
    }

    public bool GetTitlesColor()
    {
        const string query = "use wFilter Select * from dbo._TitlesColor";

        try
        {
           
            Globals.TitlesColor.Clear();

            using (var con = new SqlConnection(_connStr))
            {
                con.Open();
                var rows = con.Query(query);

                foreach (var row in rows)
                    Globals.TitlesColor.TryAdd((byte)row.ID, uint.Parse(row.Color.Replace("#", ""), NumberStyles.HexNumber));

            }
        }
        catch (Exception e)
        {
            Logger.Error($"Failed to execute : {query}");
            Logger.Debug(e);
        }

        return true;
    }

    public void UpdateCustomTitle()
    {
        Globals.CustomTitleList.Clear();

        const string query = "use wFilter Select * from dbo._CustomTitle";

        try
        {
         

            Globals.CustomTitleList.Clear();

            using (var con = new SqlConnection(_connStr))
            {
                con.Open();
                var rows = con.Query(query);

                foreach (var row in rows)
                    Globals.CustomTitleList.TryAdd(row.CharName, row.Title);
            }
        }
        catch (Exception e)
        {
            Logger.Error($"Failed to execute : {query}");
            Logger.Debug(e);
        }
    }

    public void LoadCustomIcons()
    {
        Globals.CustomIcons.Clear();

        const string query = "use wFilter Select * from dbo._CustomIcons";

        try
        {
          

            Globals.CustomIcons.Clear();

            using (var con = new SqlConnection(_connStr))
            {
                con.Open();
                var rows = con.Query(query);

                foreach (var row in rows)
                    Globals.CustomIcons.TryAdd((int)row.Id, row.Path);
            }
        }
        catch (Exception e)
        {
            Logger.Error($"Failed to execute : {query}");
            Logger.Debug(e);
        }
    }

    public void GetCharColor()
    {
        Globals.CharNameColor.Clear();

        const string query = "use wFilter Select * from dbo._CharColor";

        try
        {

            Globals.CharNameColor.Clear();

            using (var con = new SqlConnection(_connStr))
            {
                con.Open();
                var rows = con.Query(query);

                foreach (var row in rows)
                    Globals.CharNameColor.TryAdd(row.CharName, uint.Parse(row.Color.Replace("#", ""), NumberStyles.HexNumber));
            }

            if (Globals.CharNameColor.IsEmpty) return;
            var charNameColor = new Packet(0x5111);
            charNameColor.WriteUInt((uint)Globals.CharNameColor.Count);
            foreach (var (key, value) in Globals.CharNameColor)
            {
                charNameColor.WriteAscii(key);
                charNameColor.WriteUInt(value);
            }

            SessionManager.SendPacketToAll(charNameColor);

        }
        catch (Exception e)
        {
            Logger.Error($"Failed to execute : {query}");
            Logger.Debug(e);
        }
    }

    public void ReadQuery(PlayerSession session)
    {

        //var customsQuery =
        //    @$"use wFilter declare @NameColor varchar(50) declare @TitleColor varchar(50) declare @CustomIcon int declare @CustomTitle varchar(255) declare @CustomTitleCredits int declare @IsLocked bit declare @PINCode int declare @SavedPC varchar(255)
        //       SELECT TOP(1) @NameColor = [NameColor], @TitleColor = [TitleColor],@CustomIcon = [CustomIconId],@CustomTitle = [CustomTitleName],@CustomTitleCredits = [CustomTitleCredits],@IsLocked = IsLocked,@PINCode = PINCode,@SavedPC = SavedPC
        //       FROM wFilter.[dbo].[_CharacterCustoms] where CharName like '{session.State.SqlCharName}'
        //       SELECT ISNULL(@NameColor, 0), ISNULL(@TitleColor, 0), ISNULL(@CustomTitle, ''), ISNULL(@CustomIcon, 0), ISNULL(@CustomTitleCredits, 0), ISNULL(@IsLocked, 0), ISNULL(@PINCode, 0), ISNULL(@SavedPC, '')";

        var customsQuery =
            @$"use wFilter declare @NameColor varchar(50) declare @TitleColor varchar(50) declare @CustomIcon int declare @CustomTitle varchar(255) declare @DSPoints int declare @IsLocked bit declare @PINCode int declare @SavedPC varchar(255)
               SELECT TOP(1) @NameColor = [NameColor], @TitleColor = [TitleColor],@CustomIcon = [CustomIconId],@CustomTitle = [CustomTitleName],@DSPoints =DSPoints ,@IsLocked = IsLocked,@PINCode = PINCode,@SavedPC = SavedPC
               FROM wFilter.[dbo].[_CharacterCustoms] where CharName like '{session.State.SqlCharName}'
               SELECT ISNULL(@NameColor, 0), ISNULL(@TitleColor, 0), ISNULL(@CustomTitle, ''), ISNULL(@CustomIcon, 0),ISNULL(@DSPoints, 0), ISNULL(@IsLocked, 0), ISNULL(@PINCode, 0), ISNULL(@SavedPC, '')";

        try
        {

            using var con = new SqlConnection(_connStr);
            con.Open();
            using var cmd = new SqlCommand(customsQuery, con);
            using var reader = cmd.ExecuteReader();
            if (reader.HasRows)
            {
                while (reader.Read())
                {
                    session.State.NameColor = int.Parse(reader[0].ToString(), NumberStyles.HexNumber);
                    session.State.TitleColor = int.Parse(reader[1].ToString(), NumberStyles.HexNumber);
                    session.State.CustomTitleName = reader[2].ToString();
                    session.State.CustomIconId = int.Parse(reader[3].ToString());
                   // session.State.CustomTitleCredits = byte.Parse(reader[4].ToString());
                    session.State.DSPoints = int.Parse(reader[4].ToString());
                    session.State.IsLocked = bool.Parse(reader[5].ToString());
                    session.State.PinCode = reader[6].ToString();
                    session.State.SavedPC = reader[7].ToString();
                }
            }
            reader.Close();
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
        }
    }

    public void KillCounter()
    {

        try
        {
            foreach (var item in Config.GetGUISettings.KillCounters)
            {
                List<KillCounterData> listData = new();
                var regionId = item.RegionID;

                if (regionId > 0)
                {
                    var query =
                  $"use wFilter Select top 5 * from dbo.{item.TableName} order by Kills desc";


                    using (var con = new SqlConnection(_connStr))
                    {
                        con.Open();
                        listData = con.Query<KillCounterData>(query).ToList();
                    }

                }


                if (listData.Count > 0)
                {

                    foreach (var session in SessionManager.playerSessions)
                    {
                        if (string.IsNullOrEmpty(session.State.CharName)) continue;
                        if (session.State.TempPosition.RegionID != regionId) continue;

                        var killPacket = new Packet(0x1338);
                        killPacket.WriteByte(0x77);
                        killPacket.WriteByte((byte)listData.Count);
                        foreach (var data in listData)
                        {
                            killPacket.WriteAscii(data.CharName16);
                            killPacket.WriteInt32(data.Kills);
                        }

                       // var haveToBeReplaced = item.CurrentKillCount;
                       // haveToBeReplaced = haveToBeReplaced.Replace("@p1", session.State.CharName);

                        var killCount = Read<int>($"SELECT TOP 1 Kills FROM wFilter..{item.TableName} WITH (NOLOCK) WHERE CharName16 like '{session.State.SqlCharName}'");

                        killPacket.WriteInt8(killCount);
                        session.SendPacketToClient(killPacket);
                    }
                }
            }
        }

        catch (Exception e)
        {
            Logger.Error($"Failed to execute : KillCounter");
            Logger.Debug(e);
        }
    }

    public GlobalLinking GetItemForGlobalLinking(int charId, byte slot)
    {
        var customsQuery =
            @$"use {Config.GetSql.ShardDatabase} SELECT IT.ID64, IT.RefItemID, ISNULL(IT.OptLevel, 0), ISNULL(IT.Variance, 0), ISNULL(IT.[Data], 0), ISNULL(IT.MagParamNum, 0), ISNULL(IT.MagParam1, 0), ISNULL(IT.MagParam2, 0), ISNULL(IT.MagParam3, 0), ISNULL(IT.MagParam4, 0), ISNULL(IT.MagParam5, 0), ISNULL(IT.MagParam6, 0), ISNULL(IT.MagParam7, 0), ISNULL(IT.MagParam8, 0), ISNULL(IT.MagParam9, 0), ISNULL(IT.MagParam10, 0), ISNULL(IT.MagParam11, 0), ISNULL(IT.MagParam12, 0) FROM _Items IT JOIN _Inventory I ON IT.ID64 = I.ItemID WHERE I.CharID = {charId} and I.Slot = {slot}";
        var g = new GlobalLinking();

        try
        {
            using var con = new SqlConnection(_connStr);
            con.Open();
            using var cmd = new SqlCommand(customsQuery, con);
            using var reader = cmd.ExecuteReader();

            if (reader.HasRows)
            {
                while (reader.Read())
                {

                    g.ID64 = ulong.Parse(reader[0].ToString());
                    g.RefItemID = uint.Parse(reader[1].ToString());
                    g.OptLevel = uint.Parse(reader[2].ToString());
                    g.Variance = ulong.Parse(reader[3].ToString());
                    g.Data = int.Parse(reader[4].ToString());
                    g.MagParamNum = uint.Parse(reader[5].ToString());

                    if (g.MagParamNum > 0)
                    {
                        for (int i = 0; i < g.MagParamNum; i++)
                            g.MagParamList.Add(ulong.Parse(reader[6 + i].ToString()));
                    }
                }
            }
            reader.Close();

        }
        catch (Exception e)
        {
            Console.WriteLine(e);
        }

        return g;

    }

    public PetInfo GetGrabPetInfo(int petId)
    {
        var customsQuery =
            @$"use {Config.GetSql.ShardDatabase} SELECT TOP 1 State, RefCharID, CONVERT(int, DATEDIFF(SECOND,GETDATE(), RentEndTime)) AS RentEndTime, ISNULL(CharName, '') AS CharName FROM _CharCOS WITH (NOLOCK) WHERE ID = {petId}";
        var gPet = new PetInfo();

        try
        {
            using var con = new SqlConnection(_connStr);
            con.Open();
            using var cmd = new SqlCommand(customsQuery, con);
            using var reader = cmd.ExecuteReader();

            if (reader.HasRows)
            {
                while (reader.Read())
                {

                    gPet.State = uint.Parse(reader[0].ToString());
                    gPet.RefCharID = uint.Parse(reader[1].ToString());
                    gPet.RentTime = uint.Parse(reader[2].ToString());
                    gPet.PetName = reader[3].ToString();

                }
            }
            reader.Close();

        }
        catch (Exception e)
        {
            Console.WriteLine(e);
        }

        return gPet;

    }

    public PetInfo GetAttackPetInfo(int petId)
    {
        var customsQuery =
            @$"use {Config.GetSql.ShardDatabase} SELECT TOP 1 State, RefCharID, ISNULL(CharName, '') AS CharName FROM _CharCOS WITH (NOLOCK) WHERE ID = {petId}";
        var aPet = new PetInfo();

        try
        {
            using var con = new SqlConnection(_connStr);
            con.Open();
            using var cmd = new SqlCommand(customsQuery, con);
            using var reader = cmd.ExecuteReader();

            if (reader.HasRows)
            {
                while (reader.Read())
                {

                    aPet.State = uint.Parse(reader[0].ToString());
                    aPet.RefCharID = uint.Parse(reader[1].ToString());
                    aPet.PetName = reader[2].ToString();

                }
            }
            reader.Close();

        }
        catch (Exception e)
        {
            Console.WriteLine(e);
        }

        return aPet;

    }

    public Tuple<List<SocketData>, List<AdvData>> GetSocketAndAdv(ulong id64)
    {
        var customsQuery =
            @$"use {Config.GetSql.ShardDatabase} SELECT ISNULL(bOptType, 0), ISNULL(nSlot, 0), ISNULL(nOptID, 0), ISNULL(nOptLvl, 0), ISNULL(nOptValue, 0), ISNULL(nParam1, 0), ISNULL(nParam2, 0) FROM _BindingOptionWithItem WITH (NOLOCK) WHERE (nOptID <> 0) AND (nItemDBID = {id64}) ORDER BY bOptType, nSlot";
        var sock = new List<SocketData>();
        var adv = new List<AdvData>();

        try
        {
            using var con = new SqlConnection(_connStr);
            con.Open();
            using var cmd = new SqlCommand(customsQuery, con);
            using var reader = cmd.ExecuteReader();

            if (reader.HasRows)
            {
                while (reader.Read())
                {

                    var bOptType = byte.Parse(reader[0].ToString());
                    var nSlot = byte.Parse(reader[1].ToString());
                    var nOptID = int.Parse(reader[2].ToString());
                    var nOptLvl = byte.Parse(reader[3].ToString());
                    var nOptValue = int.Parse(reader[4].ToString());
                    var nParam1 = int.Parse(reader[5].ToString());
                    var nParam2 = int.Parse(reader[6].ToString());

                    if (bOptType == 1)
                    {
                        SocketData s;
                        s.nSlot = nSlot;
                        s.nOptID = nOptID;
                        s.nOptLvl = nOptLvl;
                        s.nParam1 = nParam1;
                        s.nParam2 = nParam2;

                        sock.Add(s);
                    }
                    else if (bOptType == 2)
                    {
                        AdvData a;
                        a.nOptID = nOptID;
                        a.nOptValue = nOptValue;
                        a.nSlot = nSlot;

                        adv.Add(a);
                    }


                }
            }
            reader.Close();

        }
        catch (Exception e)
        {
            Console.WriteLine(e);
        }

        return Tuple.Create(sock, adv);

    }

    public bool UpdateHwanList(PlayerSession session)
    {

        try
        {
            session.State.CharTitles.Clear();

            var query =
                $"use wFilter Select TitleID from dbo._Title_Storage WITH (NOLOCK) where CharName like '{session.State.SqlCharName}' order by TitleID ASC;";


            using (var con = new SqlConnection(_connStr))
            {
                con.Open();
                session.State.CharTitles = con.Query<byte>(query).ToList();

                //foreach (var row in rows)
                //    session.State.CharTitles.Add(row.TitleID);
            }

            return true;
        }
        catch (Exception e)
        {
            Logger.Error($"Failed to execute : UpdateHwanList");
            Logger.Debug(e);
            return false;
        }
    }

    public bool LoadIntoList(List<int> list, string query)
    {
        list.Clear();

        try
        {

            using (var con = new SqlConnection(_connStr))
            {
                con.Open();
                var result = con.Query<int>(query);

                foreach (var item in result)
                    list.Add(item);
            }
        }
        catch (Exception e)
        {
            Logger.Error($"Failed to execute : {query}");
            Logger.Debug(e);
        }


        return true;
    }

    public void LoadObjects()
    {      
        var bak = Globals.RefObjCommon;
        // ChangeDatabase(Globals.Settings.Sql.ShardDatabase);
        Globals.RefObjCommon.Clear();
        try
        {
            _connection.Query<RefObjCommon>(
                    $"use {Config.GetSql.ShardDatabase} SELECT ID,TypeID1,TypeID2,TypeID3,TypeID4,CashItem FROM dbo._RefObjCommon where service =1")
                .ToList().ForEach(
                    obj => { Globals.RefObjCommon.TryAdd(obj.ID, obj); });

        }
        catch (Exception e)
        {
            Logger.Error($"Failed to execute : Load Objects");
            Logger.Debug(e);
            Globals.RefObjCommon = bak;
        }

    }

    public void LoadHwans()
    {
        Globals.RefHwan.Clear();
        try
        {
            _connection.Query<RefHWANLevel>(
                    $"use {Config.GetSql.ShardDatabase} SELECT HwanLevel,Title_CH70,Title_EU70 FROM dbo._RefHWANLevel")
                .ToList().ForEach(
                    hwan => { Globals.RefHwan.TryAdd(hwan.HwanLevel, hwan); });

        }
        catch (Exception e)
        {
            Logger.Error($"Failed to execute : Load Hwans");
            Logger.Debug(e);
        }
    }

    public void LoadBlocked()
    {
        Globals.BlockData.Clear();
        try
        {
            _connection.Query<Blocked>(
                $"use wFilter SELECT * FROM dbo._Blocked WHERE EndDate > '{DateTime.Now}'").ToList().ForEach(
                block => { Globals.BlockData.TryAdd(block.IpOrHwid, block); });

        }
        catch (Exception e)
        {
            Logger.Error($"Failed to execute : Load Blocked");
            Logger.Debug(e);
        }
    }

    public void LoadEventList()
    {
        Globals.EventTimeList.Clear();
        try
        {
            _connection.Query<EventTime>(
                $"use wFilter SELECT * FROM dbo._EventSchedule").ToList().ForEach(
                eventList => { Globals.EventTimeList.TryAdd(eventList.Id, eventList); });

        }
        catch (Exception e)
        {
            Logger.Error($"Failed to execute : Load Events");
            Logger.Debug(e);
        }
    }

    public void LoadGMLoginSecurity()
    {
        Globals.GMSecurityList.Clear();
        try
        {
            _connection.Query(
                $"use wFilter SELECT * FROM dbo._GMLoginSecurity").ToList().ForEach(
                gmSec => { Globals.GMSecurityList.TryAdd(gmSec.UserName, gmSec.Ip); });

        }
        catch (Exception e)
        {
            Logger.Error($"Failed to execute : Load GMSecurity");
            Logger.Debug(e);
        }
    }

    public void LoadGMControl()
    {
        Globals.GMControlList.Clear();
        try
        {
            _connection.Query<GMControl>(
                $"use wFilter SELECT * FROM dbo._GMControl").ToList().ForEach(
                gm => { Globals.GMControlList.TryAdd(gm.UserName, gm); });

        }
        catch (Exception e)
        {
            Logger.Error($"Failed to execute : Load GMControl");
            Logger.Debug(e);
        }
    }

    public void LoadDShopTitlesList()
    {
        Globals.DShopTitlesList.Clear();
        try
        {
            _connection.Query<Models.DynamicShop.M_Titles>(
                $"use wFilter SELECT * FROM dbo._DynamicShop_Titles order by TitleId asc").ToList().ForEach(
                dshopTitle => { Globals.DShopTitlesList.TryAdd(dshopTitle.TitleId, dshopTitle); });


            _connection.Query<Models.DynamicShop.M_Colors>(
                $"use wFilter SELECT top 1 * FROM dbo._DynamicShop_Colors_AND_CustomTitle").ToList().ForEach(
                dshopColors =>
                {
                    Globals.DShopNameColorPrice = dshopColors.NameColorPrice; Globals.DShopTitleColorPrice = dshopColors.TitleColorPrice;
                    Globals.DShopCustomTitlePrice = dshopColors.CustomTitlePrice;
                });
        }
        catch (Exception e)
        {
            Logger.Error($"Failed to execute : Load _DynamicShop_xxx");
            Logger.Debug(e);
        }
    }
}
