namespace wFilterLib.Configs.Structures;

public class Academy : Helper.IJsonSerializable
{
    public bool DisableAcademyCreate { get; set; } = false;
    public bool DisableAcademyInvite { get; set; } = false;
    public bool DisableAcademyJoin { get; set; } = false;
    public bool DisableAcademyBan { get; set; } = false;
    public bool DisableAcademyLeave { get; set; } = false;

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}
