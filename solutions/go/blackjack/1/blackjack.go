package blackjack

// ParseCard returns the integer value of a card following blackjack ruleset.
func ParseCard(card string) int {
    switch card {
		case "ace":   return 11
    	case "two":   return 2
    	case "three": return 3
    	case "four":  return 4
    	case "five":  return 5
    	case "six":   return 6
    	case "seven": return 7
        case "eight": return 8
        case "nine":  return 9
        case "ten":   return 10
        case "jack":  return 10
        case "queen": return 10
        case "king":  return 10
        default:      return 0
    }
}

// FirstTurn returns the decision for the first turn, given two cards of the
// player and one card of the dealer.
func FirstTurn(card1, card2, dealerCard string) string {
    value1 := ParseCard(card1)
    value2 := ParseCard(card2)
    value3 := ParseCard(dealerCard)
    valueSum := value1 + value2

    if value1 == 11 && value2 == 11 {
        return "P"
    }
    if valueSum == 21 {
        if value3 < 10 {
            return "W"
        } else {
        	return "S"
        }
    }
    if valueSum >= 17 && valueSum <= 20 {
        return "S"
    }
    if valueSum >= 12 && valueSum <= 16 {
        if value3 >= 7 {
        	return "H"
        } else {
        	return "S"
        }
    }
    return "H"
}
