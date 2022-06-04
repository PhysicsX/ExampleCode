import matplotlib.pyplot as plt
import numpy as np

xPrimeData = []
yPrimeData = []

xData = []
yData = []

xDataB = []
yDataB = []

f, (ax1, ax2, ax3) = plt.subplots(1, 3) 

x_old = 0
x_new = 6

eps = 0.00009
precision = 0.00000001

ax1.set_xlim(-100, 6000)
ax1.set_ylim(-0.001, 0.050)
line, = ax1.plot(xPrimeData, yPrimeData, 'r-')

ax2.set_xlim(0, 6)
ax2.set_ylim(-10, 600)
line2, = ax2.plot(xData, yData, 'r-')

# maximize the window
manager = plt.get_current_fig_manager()
manager.full_screen_toggle()

# f(x) = x^{4}-3x^{3}
def f(x):
    return x**4 - 3*x**3

ax3.set_xlim(0, 6)
ax3.set_ylim(-10, 600)
xDataB = np.linspace(0,6,1000, endpoint=False)

for a in xDataB:
    yDataB.append(f(a))

line3, = ax3.plot(xDataB, yDataB, linewidth=3, color='red')

def f_prime(x):
    return 4 * x**3 - 9 * x**2 

it = 0
while abs(x_new - x_old) > precision:
    x_old = x_new
    x_new = x_old - eps * f_prime(x_old)
    it = it + 1
    #print(x_old, " ",x_new, " ",f_prime(x_old)," ",eps*f_prime(x_old), " ",abs(x_new - x_old))
    #print(x_new, " ", f(x_new))
    xPrimeData.append(it)
    yPrimeData.append(abs(x_new - x_old))
    line.set_xdata(xPrimeData)
    line.set_ydata(yPrimeData)

    xData.append(x_new)
    yData.append(f(x_new))
    line2.set_xdata(x_new)
    line2.set_ydata(f(x_new))

    ax1.plot(xPrimeData, yPrimeData, linewidth=3, color='red')
    ax1.title.set_text('iteration vs abs(xNew -xOld) \n xNew = xOld - eps * fPrime(xOld) \n cost function')
    ax1.set_xlabel("iteration")
    ax1.set_ylabel("difference - abs(xNew - xOld)")

    ax2.plot(xData, yData, linewidth=3, color='red')
    ax2.title.set_text('Function iteration - x vs y')
    ax2.set_xlabel("x")
    ax2.set_ylabel("y")

    ax3.plot(xData, yData, marker=".", markersize=6 , linestyle='',color='black')
    ax3.title.set_text('Function iteration on the \n drawn function with dots \n f(x) = x^4-3x^3')
    ax3.set_xlabel("x")
    ax3.set_ylabel("y")

    # to see the process in animation uncomment these
    #plt.draw()
    #plt.pause(0.000001) 

print("local minimum occurs at", x_new ," ", it)

plt.show()
