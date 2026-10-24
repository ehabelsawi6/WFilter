using NLog;

namespace wFilterLib
{
    public static class NLogConfig
    {
        public static void Setup()
        {
            var config = new NLog.Config.LoggingConfiguration();

            // Targets where to log to: File and Console
            var logfileDebug = new NLog.Targets.FileTarget("logfile") { FileName = "logs/debug/debug.log", };
            var logfileError = new NLog.Targets.FileTarget("logfile") { FileName = "logs/error/error.log" };
            var logfileFatal = new NLog.Targets.FileTarget("logfile") { FileName = "logs/fatal/fatal.log" };
            var logfileWarn = new NLog.Targets.FileTarget("logfile") { FileName = "logs/warn/warn.log" };

            logfileDebug.ArchiveEvery = NLog.Targets.FileArchivePeriod.Day;
            logfileDebug.ArchiveNumbering = NLog.Targets.ArchiveNumberingMode.Date;
            logfileDebug.ArchiveFileName = "logs/debug/debug.{#}.log";
            logfileDebug.ArchiveDateFormat = "yyyyMMdd";

            logfileError.ArchiveEvery = NLog.Targets.FileArchivePeriod.Day;
            logfileError.ArchiveNumbering = NLog.Targets.ArchiveNumberingMode.Date;
            logfileError.ArchiveFileName = "logs/error/error.{#}.log";
            logfileError.ArchiveDateFormat = "yyyyMMdd";

            logfileFatal.ArchiveEvery = NLog.Targets.FileArchivePeriod.Day;
            logfileFatal.ArchiveNumbering = NLog.Targets.ArchiveNumberingMode.Date;
            logfileFatal.ArchiveFileName = "logs/fatal/fatal.{#}.log";
            logfileFatal.ArchiveDateFormat = "yyyyMMdd";

            logfileWarn.ArchiveEvery = NLog.Targets.FileArchivePeriod.Day;
            logfileWarn.ArchiveNumbering = NLog.Targets.ArchiveNumberingMode.Date;
            logfileWarn.ArchiveFileName = "logs/warn/warn.{#}.log";
            logfileWarn.ArchiveDateFormat = "yyyyMMdd";

            var logconsole = new NLog.Targets.ColoredConsoleTarget()
            {
                Layout = "${date}|${level}|${logger}|${message} ${exception:format=tostring}"
            };

            // Rules for mapping loggers to targets            
            config.AddRule(LogLevel.Info, LogLevel.Fatal, logconsole);
            // config.AddRule(LogLevel.Debug, LogLevel.Fatal, logfile);
            config.AddRuleForOneLevel(LogLevel.Debug, logfileDebug);
            config.AddRuleForOneLevel(LogLevel.Fatal, logfileFatal);
            config.AddRuleForOneLevel(LogLevel.Error, logfileError);
            config.AddRuleForOneLevel(LogLevel.Warn, logfileWarn);

            // Apply config           
            LogManager.Configuration = config;
        }
    }
}
