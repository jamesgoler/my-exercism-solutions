static class LogLine
{
    public static string Message(string logLine)
    {
        int idx = logLine.IndexOf("]: ");
        if (idx >= 0) {
            return logLine.Substring(idx+3).Trim();
        }
        return logLine.Trim();
    }

    public static string LogLevel(string logLine)
    {
        int endIdx = logLine.IndexOf("]: ");
        if (endIdx >= 0) { 
            int startIdx = logLine.IndexOf("[");
            if (startIdx >= 0 && startIdx < endIdx) {
                startIdx += 1;
                int len = endIdx - startIdx;
                return logLine.Substring(startIdx, len).ToLower();
            }
        }
        return logLine;
    }

    public static string Reformat(string logLine) => $"{Message(logLine)} ({LogLevel(logLine)})";
}
