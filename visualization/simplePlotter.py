# Should be rewritten into SWIG to make it seamless


import matplotlib.pyplot as plt

with open('test.txt','r') as inFile:
    labelNames = inFile.readline().strip().split(' ')
    time, labelNames = labelNames[0], labelNames[1:]
    stateTraces={}
    for labelIndex, label in enumerate(labelNames):
        stateTraces[labelIndex]={'label':label,'trace':[]}
    for line in inFile:
        splitData = line.strip().split(' ')
        time, stateData = splitData[0], splitData[1:]
        for stateIndex, stateCount in enumerate(stateData):
            stateTraces[stateIndex]['trace'].append(int(stateCount))
for stateIndex, dataBundle in stateTraces.items():
    plt.plot([i for i in range(len(stateTraces[0]['trace']))],dataBundle['trace'],label=dataBundle['label'])
plt.title('SEIR Plots for Basic Model')
plt.legend()
plt.show()
        