namespace wFilterLib.Configs.Structures;

public class SurvivalHonorSystem : Helper.IJsonSerializable
{
    public string SurvivalStartTime = "00:00 PM";
    public string SurvivalEndTime = "00:30 PM";

    public string HonorStartTime = "00:00 PM";
    public string HonorEndTime = "00:30 PM";

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }

}
