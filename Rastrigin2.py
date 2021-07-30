# koterin 2021. Feel free to fork

print("\nProj1. Start")
import numpy as np
import matplotlib.pyplot as plt
    
x1 = np.arange(-5.12, 5.12, 0.01)

#making n same dimension as x1
kol = int(5.12 * 2 / 0.01)
#n = np.arange(0, kol, 1)
z1 = np.zeros(kol)

n=1
z1 = 10 * n + (x1 ** 2 - 10 * np.cos(2 * np.pi * x1))

plt.ion()
figure = plt.figure()
figure.canvas.draw()
plt.plot(x1, z1, label = 'n = 1', linewidth=1)

#Plotting the x axis
y = 0 * x1
plt.plot(x1, y, linewidth=1)

plt.legend()

#Next we create an array of random X-points, that might be a minimum
#SETTING THE FIRST POPULATION
n1 = 20 #number of individuals
#random array of X
K = np.random.rand(n1,1)
for i in range(0,n1):
    K[i] = K[i] * np.random.uniform(-5.12, 5.12)
print('\nThe first population\n' ,K)

#The best one
W=np.zeros(1)
#limit loop
limit = 10

for f in range(0,limit):
    
    print('\nPopulation ', f, '\n', K)
    
    plt.ion()
    figure = plt.figure()
    figure.canvas.draw()
    plt.plot(x1, z1, label = 'n = 1', linewidth=1)

    #Plotting the x axis
    y = 0 * x1
    plt.plot(x1, y, linewidth=1)
    
    #array of Y of the chosen X
    Yg=np.zeros(n1)
    #Fitness function
    for i in range(0,n1):
        Yg[i] = 10 * n + (K[i] ** 2 - 10 * np.cos(2 * np.pi * K[i]))
    
    #finding the minimum Y
    Min = Yg[0]
    ind = 0
    for i in range(0,n1):
        if Yg[i] < Min:
            Min = Yg[i]
            ind = i
    plt.plot(K[ind], Min, 'ro', label = 'Min')
    print('\nFound minimum is X = ', K[ind], ' Y = ', Min, ' for cycle ', f, '\n')
    
    #setting Mom and Dad as 2 random elements of the population
    #plus settin their indexes as num and nud
    #MOM
    num = np.random.randint(0, n1-1)
    MOM = K[num]
    Ym = 10 * n + (MOM ** 2 - 10 * np.cos(2 * np.pi * MOM))
    plt.plot(MOM, Ym, 'ro', label = 'Mom', color = '#cc4e4e')

    #DAD
    nud = np.random.randint(0, n1-1)
    DAD = K[nud]
    Yd = 10 * n + (DAD ** 2 - 10 * np.cos(2 * np.pi * DAD))
    plt.plot(DAD, Yd, 'ro', label = 'Dad',  color = '#5867a3')
    

    #crossing over mom and dad    
    KID = np.random.uniform(0, 1) * MOM + np.random.uniform(0, 1) * DAD
    Yk = 10 * n + (KID ** 2 - 10 * np.cos(2 * np.pi * KID))
    print('the kid is X = ', KID, ' Y = ', Yk)
    
    #Replacing the worst element of the population with the kid
    Max = Yg[0]
    nuk = 0
    for i in range (0, n1):
        if Max < Yg[i] :
            Max = Yg[i]
            nuk = i
            
    K[nuk] = KID
    plt.plot(KID, Yk, 'ro', label = 'Kid',  color = '#cd72db')
    plt.legend()
    
print('\nThe global minimum after ', limit, ' cycles is in X = ', K[ind], 
      ' Y = ', Min)














