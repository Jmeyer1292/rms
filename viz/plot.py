import numpy as np
import matplotlib.pyplot as plt

# Generate data...
x = np.random.random(10)
y = np.random.random(10)

# Plot...
plt.scatter(x, y, c=y, s=500)
plt.gray()

plt.show()