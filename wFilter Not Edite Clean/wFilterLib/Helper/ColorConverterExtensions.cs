using System.Drawing;
using System.Globalization;

namespace wFilterLib.Helper;

public static class ColorConverterExtensions
{
    public static uint ToHexUInt(this Color c) =>
        uint.Parse(c.ToHexString(), NumberStyles.HexNumber);

    public static string ToHexString(this Color c) => $"{c.R:X2}{c.G:X2}{c.B:X2}";

    public static string ToRgbString(this Color c) => $"RGB({c.R}, {c.G}, {c.B})";
}
