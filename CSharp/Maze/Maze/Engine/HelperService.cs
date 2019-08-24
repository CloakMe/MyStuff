using System;
using MazeGame.Common;
using MazeGame.Engine.Interfaces;
using MazeGame.Renderer.Interfaces;

namespace MazeGame.Engine
{
    public class HelperService : IHelperService
    {
        private readonly IRenderer renderer;

        public HelperService(IRenderer renderer)
        {
            this.renderer = renderer;
        }

        public void PrintMessage(string message)
        {
            this.renderer.RenderMessageOnNewLine(message);
        }

        public void PrintMainMenu()
        {
            this.renderer.RenderMessageOnNewLine("Commands you can use:");

            foreach (var option in Enum.GetNames(typeof(MenuOptions)))
            {
                this.renderer.RenderMessageOnNewLine("   - " + option);
            }
        }

        public void ClearScreen()
        {
            this.renderer.ClearScreen();
        }
    }
}
