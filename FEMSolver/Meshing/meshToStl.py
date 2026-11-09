import numpy
import stl

def _convert(dom_nodes, dom_elements, stl_filename, stl_mode):
    # Create the mesh
    stlMesh = stl.mesh.Mesh(numpy.zeros(dom_elements.shape[0], dtype=stl.mesh.Mesh.dtype))
    vec3d = numpy.array([0, 0, 0], numpy.float)
    for i, f in enumerate(dom_elements):
        for j in range(3):
            vec3d[0:2] = dom_nodes[f[j],:]
            stlMesh.vectors[i][j] = vec3d
    
    # Write the mesh to file "stl_filename.stl", stl_mode=stl.Mode.BINARY or stl.Mode.ASCII
    stlMesh.save( stl_filename, mode=stl_mode )    


# input @pts_filename and @el_filename are input files with point and element description
# output @stl_filename and @stl_mode is the file path and mode for the newly created stl file    
def meshToStl( pts_filename, el_filename, stl_filename, stl_mode=stl.Mode.BINARY ):
    #Read node and element files
    dom_nodes    = numpy.loadtxt( pts_filename, dtype = float )     
    dom_elements = numpy.loadtxt( el_filename, dtype = int ) 
    
    _convert(dom_nodes, dom_elements, stl_filename, stl_mode)
  
# input @mesh_obj is a meshpy.triangle object
# output @stl_filename and @stl_mode is the file path and mode for the newly created stl file
def meshObjToStl( mesh_obj, stl_filename, stl_mode=stl.Mode.BINARY ):
    #Read element and node data
    dom_elements = numpy.array( mesh_obj.elements )
    dom_nodes = numpy.array( mesh_obj.points )    
    
    _convert(dom_nodes, dom_elements, stl_filename, stl_mode) 
    
#meshToStl( "domPointsTri.dat", "domElementsTri.dat", "yoyo.stl", stl.Mode.ASCII )