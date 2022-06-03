import matplotlib.pyplot as plt
#gradient descent example for simple function with
#dynamic graph illustration
xdata = []
ydata = []
 
plt.show()

x_old = 0
x_new = 6

eps = 0.00001
precision = 0.00001
 
axes = plt.gca()
axes.set_xlim(-100, 13000)
axes.set_ylim(-0.0001, 0.0055)
#plt.tight_layout()
line, = axes.plot(xdata, ydata, 'r-')
 

def f_prime(x):
    return 4 * x**3 - 9 * x**2

it = 0
while abs(x_new - x_old) > precision:
    x_old = x_new
    x_new = x_old - eps * f_prime(x_old)
    it = it + 1
    print(x_old, " ",x_new, " ",f_prime(x_old)," ",eps*f_prime(x_old), " ",abs(x_new - x_old))
    
    xdata.append(it)
    ydata.append(abs(x_new - x_old))
    line.set_xdata(xdata)
    line.set_ydata(ydata)
    plt.draw()
    #plt.pause(1e-100)
 
print("local minimum occurs at", x_new ," ", it)
plt.show()
