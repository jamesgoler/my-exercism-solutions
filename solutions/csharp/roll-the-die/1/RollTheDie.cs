public class Player
{
    private System.Random rnd = new System.Random();
    
    public int RollDie() => rnd.Next(1, 18);

    public double GenerateSpellStrength() => rnd.NextDouble() * 100.0;
}
