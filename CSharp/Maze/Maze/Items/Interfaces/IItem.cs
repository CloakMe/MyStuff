namespace MazeGame.Items.Interfaces
{
    public interface IItem
    {
        string Name { get; }

        int Weight { get; }

        bool IsUsed { get; set; }
    }
}
