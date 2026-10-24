namespace wFilterLib.Networking.Session.Struct;

public enum PlayerLocation : ushort
{
    None = 0,
    // Town = 1,
    Fgw = 2,
    Arena = 3,
    Ctf = 4,
    Fortress = 5,
    ThiefVillage = 6
}

public enum JobType : byte
{
    NoneDb = 0,
    None = 4,
    Trader = 1,
    Robber = 2,
    Hunter = 3
}

public enum CharacterRace : byte
{
    Chinese = 0,
    Europe = 1
}
