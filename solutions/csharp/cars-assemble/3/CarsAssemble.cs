static class AssemblyLine
{
    private const double CARS_PER_HOUR_AT_1 = 221.0;
        
    public static double SuccessRate(int speed) => speed switch {
            0 => 0.0,
            <= 4 => 1.0,
            <= 8 => 0.9,
            9 => 0.8,
            _ => 0.77,
        };
    
    public static double ProductionRatePerHour(int speed) => speed * SuccessRate(speed) * CARS_PER_HOUR_AT_1;

    public static int WorkingItemsPerMinute(int speed) =>  (int)ProductionRatePerHour(speed) / 60;
}
