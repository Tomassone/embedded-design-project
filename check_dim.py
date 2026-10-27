import trimesh

mesh = trimesh.load("pcb.stl")

print("Minimum:", mesh.bounds[0])
print("Maximum:", mesh.bounds[1])
print("Dimensions:", mesh.extents)
