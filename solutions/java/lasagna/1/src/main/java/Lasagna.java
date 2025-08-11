public class Lasagna {
    public int expectedMinutesInOven() {
        return 40;
    }

    public int remainingMinutesInOven(int elapsedMinutes) {
        return expectedMinutesInOven() - elapsedMinutes;
    }

    public int preparationTimeInMinutes(int numberOfLayers) {
        return numberOfLayers * 2;
    }

    public int totalTimeInMinutes(int numberOfLayers, int elapsedMinutes) {
        return preparationTimeInMinutes(numberOfLayers) + elapsedMinutes;
    }
}
