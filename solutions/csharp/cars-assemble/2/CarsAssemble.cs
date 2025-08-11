static class AssemblyLine
{
    private const double CARS_PER_HOUR_AT_1 = 221.0;
        
    public static double SuccessRate(int speed)
    {
        if (speed == 0) {
            return 0.0;
        }
        if (1 <= speed && speed <= 4) {
            return 1.0;
        }
        if (5 <= speed && speed <= 8) {
            return 0.9;
        }
        if (speed == 9) {
            return 0.8;
        }
        return 0.77;
    }
    
    public static double ProductionRatePerHour(int speed) => speed * SuccessRate(speed) * CARS_PER_HOUR_AT_1;

    public static int WorkingItemsPerMinute(int speed) =>  (int)ProductionRatePerHour(speed) / 60;
}
