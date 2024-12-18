import numpy as np
import matplotlib.pyplot


from build.Debug.pybind11testwin import *

# q1 = Quat(2,3,4,5)
# q2 = Quat(2,-3,-4,-5)

# print(Quat.conju(q1))
# print(q1.getImag())

# print(q1)
# print(q2)
# print(q1+q2)
# print(q1*q2)

# print(q2.conju())

import matplotlib.pyplot as plt
import numpy as np


img = Grayimage(4,4)


print(img)

print(img.getPixel(1,1))

img = img.binarisation(127)


print(img)

plt.figure()
plt.imshow(img,cmap='gray',vmin=0,vmax=255)
plt.show()

# N=6
# listeVertices = [Quat(0,1,0,i) for i in range(N) ]
# Qvert = np.array(listeVertices)

# angle = np.pi/2
# rotationQuat = Quat(np.cos(angle/2.),0,np.sin(angle/2.),0)

# QvertRotated = [rotationQuat*listeVertices[i]*Quat.conju(rotationQuat) for i in range(N)]

# Qvertprime = np.array(QvertRotated)

# print(Qvertprime)

# # # plot pure quaternions
# ax = plt.figure().add_subplot(projection='3d')
# for i in range(Qvert.shape[0]):
#     veci = Qvert[i].getImag()
#     vecprimei = Qvertprime[i].getImag()
#     ax.plot(veci[0],veci[1],veci[2],'*')
#     ax.plot(vecprimei[0],vecprimei[1],vecprimei[2],'+')
# ax.set_xlim(-5, 5)
# ax.set_ylim(-5, 5)
# plt.show()


# print(build.Debug.pybind11testwin.pow(2,4))
# print(build.Debug.pybind11testwin.add(3,10))