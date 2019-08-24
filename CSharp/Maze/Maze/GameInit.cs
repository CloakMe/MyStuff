using MazeGame.Engine;
using MazeGame.Engine.Interfaces;
using MazeGame.Renderer.Interfaces;
using MazeGame.Renderer;
using MazeGame.Common;

namespace MazeGame
{
    public static class GameInit
    {
        public static void StartGame()
        {
            IRenderer iRenderer = new ConsoleRenderer();
            RandomGenerator random = new RandomGenerator();
            IItemService itemService = new ItemService(random, iRenderer);
            IHelperService helperService = new HelperService(iRenderer);
            ILocationService locationService = new LocationService(iRenderer);
            Reader reader = new Reader();
            IInputProviderService inputProviderService = new InputProviderService(iRenderer, reader);
            IGameEndService gameEndService = new GameEndService(iRenderer);
            IHealthService healthService = new HealthService(iRenderer);
            IInitializationService initializationService = new InitializationService();

            MazeEngine engine = new MazeEngine(itemService, 
                                                helperService, 
                                                locationService,
                                                inputProviderService,
                                                gameEndService,
                                                healthService,
                                                initializationService);

            engine.Initialize();

            while (true)
            {
                bool result = engine.ProcessCommand();
                if (!result)
                {
                    return;
                }
            }
        }
    }
}
