namespace wFilterLib.Configs.Structures
{
    public class SilkPerHour : Helper.IJsonSerializable
    {
        public bool Enable { get; set; } = false;
        public byte MinLevel { get; set; } = 100;
        public int RewardEvery { get; set; } = 10;
        public string SilkType { get; set; } = "Own";
        public int RewardAmount { get; set; } = 1;
        public bool RewardAfk { get; set; } = true;
        public int PCLimit { get; set; } = 0;

        public string Dump()
        {
            throw new NotImplementedException();
        }

        public bool GenerateDefaults()
        {
            throw new NotImplementedException();
        }
    }
}
