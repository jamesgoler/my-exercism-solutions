public class Lasagna {
    private static final int EXPECTED_MINUTES_IN_OVEN = 40;
    private static final int PREPARATION_TIME_FOR_EACH_LAYER = 2;
    
    public int expectedMinutesInOven() {
        return EXPECTED_MINUTES_IN_OVEN;
    }

    public int remainingMinutesInOven(int elapsedMinutes) {
        return expectedMinutesInOven() - elapsedMinutes;
    }

    public int preparationTimeInMinutes(int numberOfLayers) {
        return numberOfLayers * PREPARATION_TIME_FOR_EACH_LAYER;
    }

    public int totalTimeInMinutes(int numberOfLayers, int elapsedMinutes) {
        return preparationTimeInMinutes(numberOfLayers) + elapsedMinutes;
    }
}
