// Package weather provides tool to forecast the weather.
package weather

// CurrentCondition represents the current weather condiition.
var CurrentCondition string

// CurrentLocation represents the current location (city).
var CurrentLocation string

// Forecast returns a string that represents the forecast of the city.
func Forecast(city, condition string) string {
	CurrentLocation, CurrentCondition = city, condition
	return CurrentLocation + " - current weather condition: " + CurrentCondition
}
