namespace MazeGame.Renderer.Interfaces
{
    public interface IRenderer
    {
        void RenderWithoutNewLine(string message);

        void RenderMessageOnNewLine(string message);

        void ClearScreen();
    }
}
