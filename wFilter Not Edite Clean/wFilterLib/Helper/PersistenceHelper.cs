using Newtonsoft.Json;

namespace wFilterLib.Helper;

public static class PersistenceHelper
{
    //--------------------------------------------------------------------------

    #region Public methods


    /// <summary>
    /// Converts object of given type to json string.
    /// </summary>
    /// <typeparam name="T">The object type.</typeparam>
    /// <param name="obj">The object.</param>
    /// <returns>The json-serialized, indented string.</returns>
    public static string ToJson<T>(T obj) =>
        JsonConvert.SerializeObject(obj, Formatting.Indented);

    /// <summary>
    /// Converts json string to object of given type.
    /// </summary>
    /// <typeparam name="T">The object type.</typeparam>
    /// <param name="str">The json string to deserialize.</param>
    /// <returns></returns>
    public static T FromJson<T>(string str)
    {
        var jsonSerializerSettings = new JsonSerializerSettings()
        {
            Error = (sender, errorEventArgs) =>
            {
                Console.WriteLine(errorEventArgs.ErrorContext.Error.Message);
                errorEventArgs.ErrorContext.Handled = true;
                Console.ReadLine();
            }
        };

        return JsonConvert.DeserializeObject<T>(str, jsonSerializerSettings);
    }

    /// <summary>
    /// Reads object of given type from file.
    /// </summary>
    /// <typeparam name="T">The object type.</typeparam>
    /// <param name="path">The path.</param>
    /// <returns>
    /// Object instance, or default(T). 
    /// This will obviosly be null for nullable types
    /// </returns>
    public static T ReadFile<T>(string path) where T : IJsonSerializable
    {
        var obj = default(T);
        try
        {
            var str = File.ReadAllText(path);
            return FromJson<T>(str);
        }
        catch { }
        return obj;
    }

    /// <summary>
    /// Writes object of given type to file.
    /// </summary>
    /// <typeparam name="T">The object type.</typeparam>
    /// <param name="obj">The object.</param>
    /// <param name="path">The path.</param>
    /// <returns>true / false</returns>
    public static bool WriteFile<T>(T obj, string path) where T : IJsonSerializable
    {
        try
        {
            var str = ToJson(obj);
            File.WriteAllText(path, str);
            return true;
        }
        catch { }
        return false;
    }

    #endregion

    //--------------------------------------------------------------------------
}

/// <summary>
/// Used to ensure if type is json serializable/deserializable.
/// </summary>
public interface IJsonSerializable
{
    /// <summary>
    /// Creates default configuration.
    /// </summary>
    bool GenerateDefaults();

    /// <summary>
    /// Dump the object as string representation.
    /// </summary>
    /// <returns>The string.</returns>
    string Dump();
}
