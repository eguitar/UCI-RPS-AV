import pandas as pd
import matplotlib.pyplot as plt

# Load the Excel file
file_path = 'Rocket_Acc_X.xlsx'
df = pd.read_excel(file_path)

time = df['Time (ms)']
acceleration_x = df['AccelX (m/s^2)']
pressure= df[' Pressure (hPa)']
temp = df[' Temp (C)']
acceleration_y= df['AccelY (m/s^2)']
acceleration_z= df['AccelZ (m/s^2)']
columns= [temp, pressure, acceleration_x,  acceleration_y, acceleration_z]


accel_x = 'AccelX (m/s^2)'
press= ' Pressure (hPa)'
tem = ' Temp (C)'
acc_y= 'AccelY (m/s^2)'
accel_z= 'AccelZ (m/s^2)'
first_row= [press, accel_x,  acceleration_y, acceleration_z]

for i in columns: 
    plt.figure(figsize=(14, 7))
    plt.scatter(time, i, s=1, color='blue', label='Scatter')
    plt.plot(time, i, color='red', linewidth=0.5, label='Line')
    name = str(i)
    plt.title(f'Rocket {name} over Time')
    plt.xlabel('Time (ms)')
    plt.ylabel(f'{name}')
    plt.legend()
    plt.grid(True)
    plt.show()

    # for i in columns: 
    #     for j in first_row: 
    #         plt.figure(figsize=(14, 7))
    #         plt.scatter(time, i, s=1, color='blue', label='Scatter')
    #         plt.plot(time, i, color='red', linewidth=0.5, label='Line')
    #         plt.title(f'Rocket {j} over Time')
    #         plt.xlabel('Time (ms)')
    #         plt.ylabel(f'{j}')
    #     plt.legend()
    #     plt.grid(True)
    #     plt.show()

