using System.Collections.Generic;
using MazeGame.Rooms.Interfaces;
using MazeGame.Maps.Interfaces;

namespace MazeGame.Engine.Interfaces
{
    public interface IInitializationService
    {
        ICollection<IRoom> InitializeRooms();
        IMap InitializeMap(ICollection<IRoom> roomList);
    }
}
