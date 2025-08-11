let expectedMinutesInOven = 40

func remainingMinutesInOven(elapsedMinutes: Int) -> Int {
  return expectedMinutesInOven - elapsedMinutes
}

func preparationTimeInMinutes(layers numberOfLayers: Int) -> Int {
  return numberOfLayers * 2
}

func totalTimeInMinutes(layers numberOfLayers: Int, elapsedMinutes: Int) -> Int {
  return preparationTimeInMinutes(layers: numberOfLayers) + elapsedMinutes
}
