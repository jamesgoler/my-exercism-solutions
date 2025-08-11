class Lasagna
{
    public int ExpectedMinutesInOven() => 40;
    public int RemainingMinutesInOven(int actualMinutes) => ExpectedMinutesInOven() - actualMinutes;
    public int PreparationTimeInMinutes(int numberOfLayers) => numberOfLayers * 2;
    public int ElapsedTimeInMinutes(int numberOfLayers, int actualMinutes) => PreparationTimeInMinutes(numberOfLayers) + actualMinutes;
}
