#include <vector>
#include <set>
class Cube
{
	public:
	Cube(const std::vector<std::vector<int>> &matrix)
	{
		mZ = 100;
		mH = matrix.size();
		mCube.resize(mH);
		for (int i = 0; i < mH; i++)
		{
			if(i==0)
				mW = matrix[i].size();

			mCube[i].resize(mW);

			for (int j = 0; j < mW; j++) 
			{
				int zHeight = matrix[i][j];
				mCube[i][j].resize(mZ);

				for (int k = 0; k < zHeight; k++) 
				{
					mCube[i][j][k] = Cell(true);
				}

				for (int k = zHeight; k < mZ; k++) 
				{
					mCube[i][j][k] = Cell(false);
				}
			}
        }
    
	}

private:
	enum Neighbour
	{
		Left,
		Right,
		Up,
		Down,
		Top,
		Bottom	
	};


	struct Cell
	{
		Cell(bool present = false)
		{
			Present = present;
		}
		bool Present;
		short OutsideWalls;
		std::set<Neighbour> Neighbours;
	};


	std::vector<std::vector<std::vector<Cell> > > mCube;
	short mW,mH,mZ;

	void FillCellNeighbours()
	{
		for (int i = 0; i < mH; i++)
		{
			for (int j = 0; j < mW; j++) 
			{
				for (int k = 0; k < mZ; k++) 
				{
					if(!mCube[i][j][k].Present)
						break;

					if(k > 0)
						mCube[i][j][k].Neighbours.insert(Bottom);

					if(k < mZ - 1)
					{
						if(mCube[i][j][k+1].Present)
							mCube[i][j][k].Neighbours.insert(Top);
					}

					if( j > 0 ) //Down
					{
						if( mCube[i][j-1][k].Present )
							mCube[i][j][k].Neighbours.insert(Down);
					}

					if( j < mW - 1 ) //Up
					{
						if( mCube[i][j+1][k].Present )
							mCube[i][j][k].Neighbours.insert(Up);
					}

					if( i > 0 ) //Left
					{
						if( mCube[i-1][j][k].Present )
							mCube[i][j][k].Neighbours.insert(Left);
					}

					if( i < mH - 1 ) //Right
					{
						if( mCube[i+1][j][k].Present )
							mCube[i][j][k].Neighbours.insert(Right);
					}

					mCube[i][j][k].OutsideWalls = 6 - mCube[i][j][k].Neighbours.size();
				}
			}
        }
	}

public:	
	int GetSurface()
	{
		FillCellNeighbours();

		int result = 0;
		for (int i = 0; i < mH; i++)
		{
			for (int j = 0; j < mW; j++) 
			{
				for (int k = 0; k < mZ; k++) 
				{
					if(!mCube[i][j][k].Present)
						break;

					result += mCube[i][j][k].OutsideWalls;
				}
			}
		}
		return result;
	}
};
