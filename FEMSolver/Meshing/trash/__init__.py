import numpy
from stl import mesh
import meshpy.triangle as triangle

# stl plotting
from mpl_toolkits import mplot3d
from matplotlib import pyplot

def SortPoints(vec, pntList, pointKey): 
    j = 0 # point's counter for saved points
    for el in pntList:
        # go through all saved points
        if( numpy.isclose( vec[i], el ).all() ): # True -> Point has already been saved.
            pointKey[0] = j
            break
        if el is pntList[-1]: # False -> Point is new. Save it.
            pntList.append( ( vec[i][0], vec[i][1], vec[i][2] ) )
            pointKey[0] = len( pntList ) - 1
            break
            
# stl import
your_mesh = mesh.Mesh.from_file( 'C:/Users/AdminT/Desktop/STL/cube.stl' )

#your_mesh = mesh.Mesh.from_file('D:/workspace/WorkPython/pythonPoisson/FEMSolver/ImportinStl/new_stl_file.stl')


# Or creating a new mesh (make sure not to overwrite the `mesh` import by
# naming it `mesh`):

#VERTICE_COUNT = 10
#data = numpy.zeros(VERTICE_COUNT, dtype=mesh.Mesh.dtype)
#xSpace = numpy.linspace( xStart, xEnd, step )
#ySpace = numpy.linspace( yStart, yEnd, step )
#i = 0
#for xIt in xSpace:
#    for yIt in ySpace:
#        data['vectors'][i] = numpy.array( [[xIt, 0, 0], [1, 0, 0], [2, 0, 0]] )
#        i += 1
#print data
#your_mesh = mesh.Mesh(data, remove_empty_areas=False)

# The mesh normals (calculated automatically)

# The mesh vectors
#your_mesh.v0, your_mesh.v1, your_mesh.v2
# Accessing individual points (concatenation of v0, v1 and v2 in triplets)
#assert (your_mesh.points[0][0:3] == your_mesh.v0[0]).all()
#assert (your_mesh.points[0][3:6] == your_mesh.v1[0]).all()
#assert (your_mesh.points[0][6:9] == your_mesh.v2[0]).all()
#assert (your_mesh.points[1][0:3] == your_mesh.v0[1]).all()

#your_mesh.save('new_stl_file.stl')


# stl plotting
# Create a new plot
#===============================================

mesh_info = triangle.MeshInfo()
pntList = []
facetList = []
vecSize = len( your_mesh.v0 )
if vecSize > 0:
    pntList.append( ( your_mesh.v0[0][0], your_mesh.v0[0][1], your_mesh.v0[0][2] ) )
    pntList.append( ( your_mesh.v1[0][0], your_mesh.v1[0][1], your_mesh.v1[0][2] ) )
    pntList.append( ( your_mesh.v2[0][0], your_mesh.v2[0][1], your_mesh.v2[0][2] ) )
    facetList.append( [0, 1] )
    facetList.append( [1, 2] )
    facetList.append( [2, 0] )
else:
    raise ValueError('Triangulation inside stl file is empty!')
    
triA = [0]
triB = [0]
triC = [0]
for i in range(1, vecSize):  
    SortPoints(your_mesh.v0, pntList, triA)
    SortPoints(your_mesh.v1, pntList, triB)
    SortPoints(your_mesh.v2, pntList, triC)
    facetList.append( [triA[0], triB[0]] )
    facetList.append( [triB[0], triC[0]] )
    facetList.append( [triC[0], triA[0]] )    
print pntList
print "===="
print facetList
mesh_info.set_points( pntList )


#mesh_info.set_facets([
#    [0,1],
#    [1,2],
#    [2,3],
#    [3,0],
#    ])

#===============================================

figure = pyplot.figure()
axes = mplot3d.Axes3D(figure)
vecs = your_mesh.vectors
print vecs
#Add the vectors to the plot
axes.add_collection3d(mplot3d.art3d.Poly3DCollection(your_mesh.vectors))

# Auto scale to the mesh size
scale = your_mesh.points.flatten(-1)
axes.auto_scale_xyz(scale, scale, scale)

# Show the plot to the screen
pyplot.show()
