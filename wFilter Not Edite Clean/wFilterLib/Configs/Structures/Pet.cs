namespace wFilterLib.Configs.Structures;

public class Pet : Helper.IJsonSerializable
{
    public bool DisableFwPetRide { get; set; } = false;
    public bool DisableJobPetRide { get; set; } = false;
    public bool DisableZerkPetRide { get; set; } = false;

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}
