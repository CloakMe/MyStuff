using MazeGame.Items.Interfaces;
using MazeGame.Rooms.Interfaces;
using MazeGame.Maps.Interfaces;

namespace MazeGame.Engine.Interfaces
{
    public interface ILocationService
    {
        IRoom ChangeLocation(string destination, IRoom currentRoom, IItem key);

        void PrintCurrentLocation(IRoom currentRoom);

        void PrintMap(IRoomProperties[,] roomPropertiesMatrix);
    }
}
