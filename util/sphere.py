import numpy

def sphericalToCartesian(ro, theta, phi):
	x = ro * numpy.sin(theta) * numpy.cos(phi)
	y = ro * numpy.cos(theta)
	z = ro * numpy.sin(theta) * numpy.sin(phi)
	if (abs(x) < 0.001): x = 0.0
	if (abs(y) < 0.001): y = 0.0
	if (abs(z) < 0.001): z = 0.0
	#return (x,y,z)
	return "%.3ff, %.3ff, %.3ff" % (x,y,z)
	#return "%.3f, %.3f, %.3f" % (ro, theta, phi)

def genWedge(ro, phi, phiPrev, thetaInc):
	triangles = []

	triangles.append([
		(ro, 0, 0),
		(ro, thetaInc, phiPrev),
		(ro, thetaInc, phi)
	])
	for theta in numpy.arange(thetaInc, numpy.pi-thetaInc, thetaInc):
		triangles.append([
			(ro, theta, phiPrev),
			(ro, theta+thetaInc, phiPrev),
			(ro, theta, phi)
		])
		triangles.append([
			(ro, theta, phi), 
			(ro, theta+thetaInc, phiPrev),
			(ro, theta+thetaInc, phi)
		])
	lastTheta = numpy.pi - thetaInc
	triangles.append([
		(ro, lastTheta, phiPrev),
		(ro, numpy.pi, 0),
		(ro, lastTheta, phi)
	])
	return triangles

def convertTriangles(triangles):
	# Hold the indices, vertices and the mapping between
	# them
	indices = []
	vertices = []
	indexOfVertex = {}

	# Convert the triangle coordinates into a string
	# and add the vertices
	for triangle in triangles:
		for vertex in triangle:
			cart = sphericalToCartesian(vertex[0], vertex[1], vertex[2])
			if cart in indexOfVertex:
				#print("HIT: ", cart)
				indices += [indexOfVertex[cart]]
			else:
				#print("MISS: ", cart)
				indices.append( len(vertices) )
				indexOfVertex[cart] = len(vertices)
				vertices.append(cart)

	return (vertices, indices)

def getUVSphere(radius, numMeridians, numParallels):
	# Holds the spherical triangles
	triangles = []

	# Hold parameters
	phiInc = 2*numpy.pi/(numMeridians)
	thetaInc = numpy.pi/(numParallels+1)

	# Generate trriangles for the sphere
	phiPrev = 0
	for phi in numpy.arange(phiInc, 2*numpy.pi, phiInc):
		triangles += genWedge(radius, phi, phiPrev, thetaInc)
		phiPrev = phi
	triangles += genWedge(radius, 0, phiPrev, thetaInc)

	# Convert Triangles to lists of vertices and indices
	# Note: Input triangles in spherical coordinates, but
	# Output vertices in cartesian coordinates
	return convertTriangles(triangles)

def printArrays(vertices, indices):

	print("GLint indices[] = {")
	indexCount = 0
	idxStr = "    "
	for index in indices:
		idxStr += "%d, " % index
		indexCount += 1
		if indexCount == 15:
			print(idxStr)
			idxStr = "    "
			indexCount = 0
	print(idxStr)
	print("};")

	print("GLfloat vertices[] = {")
	for vertex in vertices:
		print("    %s, 1.0f,  R, G, B, A," % vertex)
	print("};");

if __name__ == '__main__':
	(vertices, indices) = getUVSphere(1, 32, 16)
	#(vertices, indices) = getUVSphere(1, 4, 3)
	printArrays( vertices, indices )
	print("# of indices: ", len(indices))
