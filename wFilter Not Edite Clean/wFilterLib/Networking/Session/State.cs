using Timer = System.Timers.Timer;
using wFilterLib.SSA;
using wFilterLib.Networking.Session.Classes;
using wFilterLib.Networking.Session.Struct;

namespace wFilterLib.Networking.Session
{
    public class State : IDisposable
    {
        public Packet CharacterDataPacket;
        public int CurLevel;
        public byte HwanLevel = 0;
        public string? Ip;
        public uint ServerTime;
        public uint RefObjId;
        public ulong RemainGold { get; set; }
        public uint RemainSkillPoint { get; set; }
        public ushort RemainStatPoint { get; set; }
        public byte Scale { get; set; }
        public ulong ExpOffset { get; set; }
        public uint SExpOffset { get; set; }
        public uint UniqueId;
        public GamePosition Position;
        public GamePosition TempPosition = new();
        public PlayerLocation Location;

        public bool InTown;
        public string CharName = "";
        public string SqlCharName = "";
        public int CharId = 0;
        public string UserName = "";
        public int UserJid = 0;
        public string JobName = "";
        public JobType JobType = JobType.None;
        public bool IsJob;
        public bool IsZerking;
        public bool InsideParty;
        public bool OnTransport;
        public DateTime GlobalDelay = DateTime.Now.Subtract(TimeSpan.FromMinutes(10));
        public DateTime ReverseDelay = DateTime.Now.Subtract(TimeSpan.FromMinutes(10));
        public DateTime ResurrectionDelay = DateTime.Now.Subtract(TimeSpan.FromMinutes(10));
        public DateTime StallDelay = DateTime.Now.Subtract(TimeSpan.FromMinutes(10));
        public DateTime ExchangeDelay = DateTime.Now.Subtract(TimeSpan.FromMinutes(10));
        public DateTime ZerkDelay = DateTime.Now.Subtract(TimeSpan.FromMinutes(10));
        public DateTime LogoutDelay = DateTime.Now.Subtract(TimeSpan.FromMinutes(10));
        public string Hwid = "";

        public bool FirstTime = false;
        public bool CharScreen = false;
        public bool IsOnline;
        public uint TokenId;
        public CharacterRace Race;
        public uint FellowPetId;

        public int LastDiedRegionId;
        public int LastReturnRegionId;

        public bool CtfRegistered;
        public bool ArenaRegistered;

        public Timer SilkTimer;
        //GUI 
        public List<byte> CharTitles = new();

        public int NameColor = 0;
        public int TitleColor = 0;
        public int CustomIconId = 0;
        public string CustomTitleName = string.Empty;
        //public byte CustomTitleCredits = 0;
        public bool IsLocked = false;
        public string PinCode = "";
        public byte PinFailedTimes = 0;
        public string SavedPC = "";

        //dynamic shop
        public int DSPoints = 0;

        public Packet GameReadyPacket = null;

        //GLOBAL ITEM LINKING

        public byte m_GlobalLinkedItemBegin = 0;
        public byte m_GlobalLinkedItemEnd = 0;
        public byte m_GlobalLinkedItemSlot = 0;
        public string m_CustomLinkedItemName = string.Empty;
        public uint CurrentGlobalColor = 0;

        public bool IsAfk = false;
        public int PingCounter = 0;

        public uint phbotOpcode = 0;
        public byte PendingAlchemySlot = 255;
        public int PendingAlchemyPlus = -1;

        public bool PatchSent;
        public bool ServerListSent;

        public bool IsClientLess;


        #region Events

        public bool InSurvival = false;
        public bool SurvivalBlock = false;

        #endregion

        public void Dispose()
        {
            if (CharTitles != null)
            {
                CharTitles.Clear();
                CharTitles = null;
            }

            if (SilkTimer != null)
            {
                SilkTimer.Stop();
                SilkTimer.Dispose();
                SilkTimer = null;
            }


            if (Position != null)
                Position = null;

            if (TempPosition != null)
                TempPosition = null;
        }
    }
}
